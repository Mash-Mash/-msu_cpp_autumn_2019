#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <queue>


class ThreadPool {
public:
	using Function = std::function<void()>;

	void loop_function(ThreadPool& pool)
	{
		while (true)
		{
			Function task;
			{
				std::unique_lock<std::mutex> lock(pool.d_mutex);
				pool.d_condition.wait(lock, [&pool] { return pool.d_stop || !pool.d_tasks.empty(); });
				if (pool.d_stop && pool.d_tasks.empty())
				{
					return;
				}
				task = pool.d_tasks.front();
				pool.d_tasks.pop();
			}
			task();
		}
	}

	explicit ThreadPool(size_t poolSize = std::thread::hardware_concurrency()) : d_stop(false)
	{
		for (size_t i = 0; i < poolSize; ++i)
		{
			d_pool.emplace_back([this](){ return loop_function(*this); });
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
			d_tasks.push([task]() { (*task)(); });
		}
		d_condition.notify_one();

		return res;
	}

	~ThreadPool()
	{
		{
			d_stop = true;
		}
		d_condition.notify_all();
		for (std::thread& thread : d_pool)
		{
			thread.join();
		}
	}
private:
	std::vector<std::thread> d_pool;
	std::queue<Function> d_tasks;

	std::mutex d_mutex;
	std::condition_variable d_condition;
	std::atomic<bool> d_stop;
};