#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>


class ThreadPool {
public:
	using Function = std::function<void()>;

	void loop_function(ThreadPool* pool)
	{
		while (true)
		{
			Function task;
			{
				std::unique_lock<std::mutex> lock(pool->d_mutex);
				pool->condition.wait(lock, [pool] { return pool->stop || !pool->d_tasks.empty(); });
				if (pool->stop && pool->d_tasks.empty())
				{
					return;
				}
				task = pool->d_tasks.front();
				pool->d_tasks.erase(d_tasks.begin());
			}
			task();
		}
	}

	explicit ThreadPool(size_t poolSize = std::thread::hardware_concurrency()) : stop(false)
	{
		for (size_t i = 0; i < poolSize; ++i)
		{
			d_pool.emplace_back([this](){ return loop_function(this); });
		}
	}

	template <class Func, class... Args>
	auto exec(Func func, Args... args)->std::future<decltype(func(args...))>
	{
		using packed_task = std::packaged_task<decltype(func(args...))()>;

		auto task = std::make_shared<packed_task>(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
		auto res = task->get_future();

		{
			std::unique_lock<std::mutex> lock(d_mutex);
			d_tasks.emplace_back([task]() { (*task)(); });
		}
		condition.notify_one();

		return res;
	}

	~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock(d_mutex);
			stop = true;
		}
		condition.notify_all();
		for (std::thread& thread : d_pool)
		{
			thread.join();
		}
	}
private:
	std::vector<std::thread> d_pool;
	std::vector<Function> d_tasks;

	std::mutex d_mutex;
	std::condition_variable condition;
	std::atomic<bool> stop;
};
