#include <cstdlib>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

static const int kItemRepositorySize = 3; // Item buffer size.
static const int kItemsToProduce = 100;   // How many items we plan to produce.
std::mutex mutex;

namespace MM
{
	struct ItemRepository
	{
		int item_buffer[kItemRepositorySize];
		size_t read_position;
		size_t write_position;
		size_t produced_item_counter;
		size_t consumed_item_counter;
		std::mutex mtx;
		std::mutex produced_item_counter_mtx;
		std::mutex consumed_item_counter_mtx;
		std::condition_variable repo_not_full;
		std::condition_variable repo_not_empty;
	} gItemRepository;

	typedef struct ItemRepository ItemRepository;

	void ProduceItem(ItemRepository *ir, int item)
	{
		std::unique_lock<std::mutex> lock(ir->mtx);
		while (((ir->write_position + 1) % kItemRepositorySize) == ir->read_position)
		{
			// item buffer is full, just wait here.
			{
				std::lock_guard<std::mutex> lock(mutex);
				std::cout << "���������������ߵȴ���\n";
			}
			(ir->repo_not_full).wait(lock);
		}

		(ir->item_buffer)[ir->write_position] = item;
		(ir->write_position)++;

		if (ir->write_position == kItemRepositorySize)
			ir->write_position = 0;

		(ir->repo_not_empty).notify_all();
		lock.unlock();
	}

	int ConsumeItem(ItemRepository *ir)
	{
		int data;
		std::unique_lock<std::mutex> lock(ir->mtx);
		// item buffer is empty, just wait here.
		while (ir->write_position == ir->read_position)
		{
			{
				std::lock_guard<std::mutex> lock(mutex);
				std::cout << "�������գ������ߵȴ���\n";
			}
			(ir->repo_not_empty).wait(lock);
		}

		data = (ir->item_buffer)[ir->read_position];
		(ir->read_position)++;

		if (ir->read_position >= kItemRepositorySize)
			ir->read_position = 0;

		(ir->repo_not_full).notify_all();
		lock.unlock();

		return data;
	}

	void ProducerTask()
	{
		bool ready_to_exit = false;
		while (1)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::unique_lock<std::mutex> lock(gItemRepository.produced_item_counter_mtx);
			if (gItemRepository.produced_item_counter < kItemsToProduce)
			{
				++(gItemRepository.produced_item_counter);
				ProduceItem(&gItemRepository, gItemRepository.produced_item_counter);
				{
					std::lock_guard<std::mutex> lock(mutex);
					std::cout << "������" << std::this_thread::get_id()
						<< "����������" << gItemRepository.produced_item_counter
						<< "����Ʒ" << std::endl;
				}
			}
			else
			{
				ready_to_exit = true;
			}

			lock.unlock();
			if (ready_to_exit == true)
			{
				break;
			}
		}
		{
			std::lock_guard<std::mutex> lock(mutex);
			std::cout << "������" << std::this_thread::get_id()
				<< "�˳�" << std::endl;
		}
	}

	void ConsumerTask()
	{
		bool ready_to_exit = false;
		while (1)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::unique_lock<std::mutex> lock(gItemRepository.consumed_item_counter_mtx);
			if (gItemRepository.consumed_item_counter < kItemsToProduce)
			{
				int item = ConsumeItem(&gItemRepository);
				++(gItemRepository.consumed_item_counter);
				{
					std::lock_guard<std::mutex> lock(mutex);
					std::cout << "������" << std::this_thread::get_id()
						<< "�������ѵ�" << item << "����Ʒ" << std::endl;
				}
			}
			else
			{
				ready_to_exit = true;
			}
			lock.unlock();
			if (ready_to_exit == true)
			{
				break;
			}
		}
		{
			std::lock_guard<std::mutex> lock(mutex);
			std::cout << "������" << std::this_thread::get_id()
				<< "�˳�" << std::endl;
		}
	}

	void InitItemRepository(ItemRepository *ir)
	{
		ir->write_position = 0;
		ir->read_position = 0;
		ir->produced_item_counter = 0;
		ir->consumed_item_counter = 0;
	}

	void test()
	{
		InitItemRepository(&gItemRepository);
		std::thread producer1(ProducerTask);
		std::thread producer2(ProducerTask);
		std::thread producer3(ProducerTask);
		std::thread producer4(ProducerTask);

		std::thread consumer1(ConsumerTask);
		std::thread consumer2(ConsumerTask);
		std::thread consumer3(ConsumerTask);
		std::thread consumer4(ConsumerTask);

		producer1.join();
		producer2.join();
		producer3.join();
		producer4.join();

		consumer1.join();
		consumer2.join();
		consumer3.join();
		consumer4.join();
	}
}

int main()
{
	MM::test();
	system("pause");
	return 0;
}