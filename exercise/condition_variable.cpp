#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex              mtx;
std::condition_variable cv;
bool                    ready = false;

void myFunction()
{
    std::unique_lock<std::mutex> lock(mtx);
    {
        cv.wait(lock);
    }
    std::cout << "Hello from thread!" << std::endl;
}

int main()
{
    std::thread t(myFunction);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one();

    t.join();
    return 0;
}
