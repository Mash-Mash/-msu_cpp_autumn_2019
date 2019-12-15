#include <iostream>
#include "FileSorter.h"

constexpr auto BufferSize = 8 << 20;

void createBinaryFile(const std::string& path)
{
	std::vector<uint64_t> elements = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	std::ofstream file(path, std::ios::binary | std::ios::trunc);
	for (auto& elem : elements)
		file.write(reinterpret_cast<char*>(&elem), sizeof(elem));
}

int main(int argc, char* argv[])
{
	std::string inputFile = "input.txt";

	if (argc == 2 && std::string(argv[1]) == "-test")
	{
		createBinaryFile(inputFile);
	}
	else if (argc == 2)
	{
		inputFile = std::string(argv[1]);
	}
	else
	{
		std::cout << "Please, enter the name of file or key -test" << std::endl;
		return 1;
	}

	auto path = fs::path(inputFile);
	auto savePath = path.parent_path() / fs::path(path.stem().string() + "_out" + path.extension().string());
	
	FileSorter sorter(BufferSize);
	sorter.run(path.string(), savePath.string());

	return 0;
}