#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <chrono>

void queue_basics() {
    std::queue<std::string> q;

    // 1. push: Add to the back of the line
    q.push("Customer 1");
    q.push("Customer 2");
    q.emplace("Customer 3");

    // 2. front: Look at the next person to be served
    std::cout << "Next up: " << q.front() << "\n"; // Customer 1

    // 3. back: Look at the person who just joined
    std::cout << "Last in line: " << q.back() << "\n"; // Customer 3

    std::cout<<"Remove the person at the front\n";
    // 4. pop: Remove the person at the front
    q.pop(); 

    std::cout << "Now serving: " << q.front() << "\n"; // Customer 2
}

struct Command {
    int id;
    std::string action;    

    Command(int i, std::string a) : id(i), action(a) {
        std::cout << "Creating Command " << id << "\n";
    }
};

void process_commands() {
    std::queue<Command> cmd_queue;

    // 1. Using emplace to construct objects directly in the queue
    cmd_queue.emplace(101, "RELOAD_ASSETS");
    cmd_queue.emplace(102, "CLEAN_CACHE");
    cmd_queue.emplace(103, "UPDATE_UI");

    std::cout << "\n--- Starting Processing ---\n";

    while (!cmd_queue.empty()) {
        // Get a reference to the front to avoid a copy
        const Command& current = cmd_queue.front();

        std::cout << "Executing [" << current.id << "]: " << current.action << "..." << std::endl;
        
        // Simulate "work"
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Remove the command after it is done
        cmd_queue.pop();
    }
    
    std::cout << "All commands cleared.\n";
}
int main()
{
    queue_basics();
    std::cout<<"\n-Processor command simulation\n";
    std::cout<<"creating a queue with some commands and simulate work\n";
    process_commands();


    return 0;
}