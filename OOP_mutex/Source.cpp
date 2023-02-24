#include <iostream>
#include <thread>
#include <string>
#include <mutex>
// Потоки, мьютексы

// Main thread

class Logger {
public:
	void log(const std::string& message) {		
		std::lock_guard<std::mutex> lock(_mutex);
		std::cout << "[" << _messageCounter << "] " << message << '\n';
		_messageCounter++;
		// race condition - состояние гонки
	}

private:
	int _messageCounter = 0;
	std::mutex _mutex;
};

int main() {

	Logger logger;
	logger.log("Hello");
	logger.log("Info message");

	std::thread t1 = std::thread([&logger]() {
		std::string threadName = "t1";
		for (size_t i = 0; i < 100; i++) {
			// ... work
			logger.log(threadName + " doing " + std::to_string(i) + " iteration to work\n");
		}
	});

	std::thread t2 = std::thread([&logger]() {		
		std::string threadName = "t2";
		for (size_t i = 0; i < 100; i++) {
			// ... work
			logger.log(threadName + " doing " + std::to_string(i) + " iteration to work\n");
		}
	});

	t1.join();
	t2.join();


}




