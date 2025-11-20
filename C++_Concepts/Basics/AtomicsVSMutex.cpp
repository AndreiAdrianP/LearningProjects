#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include <chrono>

// --- Configuration Constants ---
const int NUM_THREADS = 8;
// Use a large number of iterations to ensure observable contention and reliable timing.
const long long TOTAL_ITERATIONS = 100000000; // 100 Million increments
const int ITERATIONS_PER_THREAD = TOTAL_ITERATIONS / NUM_THREADS;



// 1. Lock-Free Approach: Uses std::atomic for safe, thread-level synchronization.
std::atomic<int> atomic_counter(0);

// 2. Lock-Based Approach: Uses std::mutex to protect a standard integer.
int mutex_counter = 0;
std::mutex counter_mutex;


// --- Worker Functions ---

void increment_atomic() {
    for (int i = 0; i < ITERATIONS_PER_THREAD; ++i) {
        atomic_counter++; // Lock-free operation
    }
}

void increment_mutex() {
    for (int i = 0; i < ITERATIONS_PER_THREAD; ++i) {
        // std::lock_guard automatically acquires the lock on construction
        // and releases it on destruction (when it goes out of scope).
        std::lock_guard<std::mutex> lock(counter_mutex);
        mutex_counter++; // Protected operation
    }
}


int main() {
    std::cout << "--- Project 4: Concurrent Counter Performance Test ---" << std::endl;
    std::cout << "Threads: " << NUM_THREADS << ", Total Increments: " << TOTAL_ITERATIONS << std::endl << std::endl;

    // Type alias for cleaner code
    using Clock = std::chrono::high_resolution_clock;

        // 1. LOCK-FREE TEST (std::atomic)
 
    std::vector<std::thread> atomic_threads;
    auto atomic_start = Clock::now();

    for (int i = 0; i < NUM_THREADS; ++i) {
        atomic_threads.emplace_back(increment_atomic);
    }

    for (auto& t : atomic_threads) {
        t.join();
    }

    auto atomic_end = Clock::now();
    auto atomic_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(atomic_end - atomic_start);

    std::cout << "[LOCK-FREE RESULTS]" << std::endl;
    std::cout << "Final Counter Value: " << atomic_counter.load() << " (Expected: " << TOTAL_ITERATIONS << ")" << std::endl;
    std::cout << "Duration: " << atomic_duration_ms.count() << " ms" << std::endl;
    std::cout << "---------------------------------------" << std::endl;


     // 2. LOCK-BASED TEST (std::mutex)
 
    std::vector<std::thread> mutex_threads;
    auto mutex_start = Clock::now();

    for (int i = 0; i < NUM_THREADS; ++i) {
        mutex_threads.emplace_back(increment_mutex);
    }

    for (auto& t : mutex_threads) {
        t.join();
    }

    auto mutex_end = Clock::now();
    auto mutex_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(mutex_end - mutex_start);

    std::cout << "[LOCK-BASED RESULTS]" << std::endl;
    std::cout << "Final Counter Value: " << mutex_counter << " (Expected: " << TOTAL_ITERATIONS << ")" << std::endl;
    std::cout << "Duration: " << mutex_duration_ms.count() << " ms" << std::endl;
    std::cout << "---------------------------------------" << std::endl;    
    
    std::cout << "\n--- Performance Analysis End---" << std::endl;

       
    return 0;
}