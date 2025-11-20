#include <iostream>
#include <vector>
#include <thread>
#include <latch>
#include <barrier>
#include <chrono>
#include <functional> // For std::ref

// Constants
constexpr int NUM_WORKERS = 5;

// Function run by the threads
void worker_task(int id, std::latch& setup_latch, std::barrier<>& phase_barrier) {
    using namespace std::chrono_literals;

    // --- Phase 1: Setup ---
    std::cout << "Worker " << id << " starting setup...\n";

    // Simulate variable setup time (e.g., loading data)
    std::this_thread::sleep_for(std::chrono::milliseconds(20 * (5 - id))); 
    
    // Signal completion
    setup_latch.count_down(); 
    std::cout << "Worker " << id << " finished setup. Latch \n";

    // The worker proceeds immediately to Phase 2, but the main thread waits on the latch.
    
    // --- Phase 2: Work (Worker side) ---
    std::cout << "Worker " << id << " moving to phase 2: Work.\n";
    std::this_thread::sleep_for(100ms);

    // --- Phase 3: Coordination ---
    std::cout << "Worker " << id << " arrived at phase 3 barrier. Waiting...\n";

    // Arrive and wait until all 5 workers reach this point
    phase_barrier.arrive_and_wait();

    std::cout << "Worker " << id << " finished phase 3 and proceeding.\n";
}

int main() {
    // 1. Define Synchronization Primitives
    // Latch: Count is initialized to NUM_WORKERS (5). It's a one-time barrier.
    std::latch setup_latch(NUM_WORKERS); 

    // Barrier: Expected number of threads is NUM_WORKERS (5). It's a reusable barrier.
    // The default completion function is a no-op.
    std::barrier<> phase_barrier(NUM_WORKERS); 

    // 2. Initialize Thread Pool (std::jthread ensures automatic joining)
    std::vector<std::jthread> threads; 
    
    std::cout << "--- Starting Workers ---\n";
    for (int i = 0; i < NUM_WORKERS; ++i) {
        // We use std::ref to ensure the synchronization objects are passed by reference
        threads.emplace_back(worker_task, i, std::ref(setup_latch), std::ref(phase_barrier));
    }

    // --- Main Thread Phase 1: Wait for all workers to complete setup ---
    std::cout << "\nMain Thread: Waiting for all " << NUM_WORKERS << " workers to finish setup...\n";
    
    // This call blocks until the latch count reaches zero (i.e., all workers called count_down)
    setup_latch.wait(); 
    
    std::cout << "Main Thread: All workers are ready! Latch is open.\n";

    // --- Main Thread Phase 2: Perform main work, overlapping with worker's Phase 2 ---
    std::cout << "Main Thread: Beginning its own Phase 2 work.\n\n";
    
    // Since threads is a vector of jthreads, when main() exits, 
    // the jthread destructors will automatically call .join(), 
    // ensuring a clean exit without manual joining.

    return 0;
}