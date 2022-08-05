#include <iostream>
#include <thread>
#include "monitor.h"
#include "logger.h"

// Automatically do stuff - plus waiting between operations
void doStuff( fs::path directory ) {
    std::cout << "doing stuff...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds{250});
    fs::create_directory(directory / "1");
    std::this_thread::sleep_for(std::chrono::milliseconds{250});
    fs::create_directory(directory / "1/1");
    std::this_thread::sleep_for(std::chrono::milliseconds{250});
    fs::create_directories(directory / "2/1");
    std::this_thread::sleep_for(std::chrono::milliseconds{250});
    fs::create_directories(directory / "1/2/1/1");
    std::this_thread::sleep_for(std::chrono::milliseconds{250});
    fs::remove_all(directory / "1");
    std::this_thread::sleep_for(std::chrono::milliseconds{250});
    fs::create_directories(directory / "3/1/2/3");
    std::this_thread::sleep_for(std::chrono::milliseconds{250});
    fs::create_directory(directory / "3/1/2/2");
    std::this_thread::sleep_for(std::chrono::milliseconds{250});
    fs::create_directory(directory / "3/1/1");
    std::this_thread::sleep_for(std::chrono::milliseconds{250});
    fs::remove_all(directory / "3/1");
}

int main() {
    auto directory = fs::current_path();
    directory /= "sandbox";

    if (!fs::exists( directory )){
        fs::create_directory(directory);
    } else {
        fs::remove_all(directory);
        fs::create_directory(directory);
    }
    FileMonitor monitor{"./sandbox/", std::chrono::milliseconds{1000} };

    // Do stuff in the directory on a secondary thread!
    std::thread t1(doStuff, directory);

    std::cout << "Monitor has been started...\n";
    monitor.start(std::chrono::seconds{10});

    // Wait for secondary thread
    t1.join();

    return 0;
}
