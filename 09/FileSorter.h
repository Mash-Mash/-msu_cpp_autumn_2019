#pragma once

#include <algorithm>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

namespace fs = std::experimental::filesystem;

class FileSorter
{
public:
	using ElementType = uint64_t;

	FileSorter(size_t bufferSizeInBytes) : d_bufferSize(bufferSizeInBytes / sizeof(ElementType) / 2), d_finished(false)
	{
		d_buffers[0].resize(d_bufferSize);
		d_buffers[1].resize(d_bufferSize);
	}

	void run(const std::string& filePath, const std::string& savePath)
	{
		std::thread readWriteThread([this, &filePath]() { this->readWriteLoop(filePath); });
		std::thread sortThread([this]() { this->sortLoop(); });

		readWriteThread.join();
		sortThread.join();
		
		mergeFiles(savePath);
	}

private:
	class SortedFile
	{
	public:
		SortedFile(const std::string& filePath) : d_file(std::make_shared<std::ifstream>(filePath, std::ios::in | std::ios::binary)), d_filePath(filePath)
		{
			d_file->read(reinterpret_cast<char*>(&d_elem), sizeof(d_elem));
		}

		bool operator<(const SortedFile& file) const
		{
			return d_elem > file.d_elem;
		}

		void deleteFile()
		{
			d_file->close();
			std::error_code error;
			fs::remove(fs::path(d_filePath), error);
		}

		ElementType d_elem;
		std::shared_ptr<std::ifstream> d_file;
		std::string d_filePath;
	};

	void readWriteLoop(const std::string& filePath)
	{
		std::ifstream inputFile(filePath, std::ios::binary);
		if (!inputFile.is_open())
			throw std::runtime_error("Cannot open the file: " + filePath);

		auto readToBuffer = [this](std::ifstream& file, std::vector<ElementType>& buffer)
		{
			size_t elementsRead = 0;
			while (elementsRead < buffer.size() && file.read(reinterpret_cast<char*>(buffer.data() + elementsRead), sizeof(ElementType)))
				++elementsRead;

			bool finished = elementsRead != buffer.size();
			if (finished)
				buffer.resize(elementsRead);

			{
				std::lock_guard<std::mutex> lock(d_queueMutex);
				d_sortQueue.push(&buffer);
			}

			d_cond.notify_one();

			return finished;
		};

		auto writeFile = [this, &filePath](size_t fileIndex)
		{
			std::unique_lock<std::mutex> lock(d_condMutex);
			d_cond.wait(lock, [this]() { return !d_writeQueue.empty(); });

			std::vector<ElementType>* sortedBuffer = nullptr;
			{
				std::lock_guard<std::mutex> lock(d_queueMutex);
				sortedBuffer = d_writeQueue.front();
				d_writeQueue.pop();
			}

			if (!sortedBuffer->empty())
			{
				auto savePath = fs::path(filePath).parent_path() / fs::path("tmp_" + std::to_string(fileIndex));
				std::ofstream tmpFile(savePath, std::ios::binary | std::ios::out);
				if (!tmpFile.is_open())
					throw std::runtime_error("Cannot open the file: " + savePath.string());

				tmpFile.write(reinterpret_cast<const char*>(sortedBuffer->data()), sortedBuffer->size() * sizeof(ElementType));
				tmpFile.close();

				d_sortedFiles.push(SortedFile(savePath.string()));
			}
		};

		auto* readBuffer = &d_buffers[0];
		auto* sortBuffer = &d_buffers[1];
		
		d_finished = readToBuffer(inputFile, *readBuffer);
		std::swap(readBuffer, sortBuffer);

		size_t filesProcessed = 1;
		while(!d_finished)
		{
			d_finished = readToBuffer(inputFile, *readBuffer);
			std::swap(readBuffer, sortBuffer);

			writeFile(filesProcessed);
			++filesProcessed;
		}

		writeFile(filesProcessed);
	}

	void sortLoop()
	{
		while (!d_finished || !d_sortQueue.empty())
		{
			std::unique_lock<std::mutex> lock(d_condMutex);
			d_cond.wait(lock, [this]() {return !d_sortQueue.empty(); });

			std::vector<ElementType>* buffer = nullptr;
			{
				std::lock_guard<std::mutex> lock(d_queueMutex);
				buffer = d_sortQueue.front();
				d_sortQueue.pop();
			}

			std::sort(buffer->begin(), buffer->end());

			{
				std::lock_guard<std::mutex> lock(d_queueMutex);
				d_writeQueue.push(buffer);
			}
		
			lock.unlock();
			d_cond.notify_one();
		}
	}

	void mergeFiles(const std::string& savePath)
	{
		std::ofstream result(savePath, std::ios::binary | std::ios::out);
		while (!d_sortedFiles.empty())
		{
			auto elem = d_sortedFiles.top();
			d_sortedFiles.pop();

			result.write(reinterpret_cast<char*>(&elem.d_elem), sizeof(elem.d_elem));

			if (elem.d_file->read(reinterpret_cast<char*>(&elem.d_elem), sizeof(uint64_t)))
			{
				d_sortedFiles.push(elem);
			}
			else
			{
				elem.deleteFile();
			}
		}
	}

private:
	size_t d_bufferSize;
	std::vector<ElementType> d_buffers[2];
	std::queue<std::vector<ElementType>*> d_sortQueue;
	std::queue<std::vector<ElementType>*> d_writeQueue;
	std::mutex d_queueMutex;

	std::priority_queue<SortedFile> d_sortedFiles;
	
	std::mutex d_condMutex;
	std::condition_variable d_cond;
	bool d_finished;
};