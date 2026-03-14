#include <iostream>
#include <queue>
#include <vector>

void priority_basics() {
    std::priority_queue<int> pq;

    pq.push(10);
    pq.push(30);
    pq.push(20);
    pq.push(5);

    // Unlike queue (front()), priority_queue uses top()
    while (!pq.empty()) {
        std::cout << pq.top() << " "; 
        pq.pop();
    }
}
struct Command {
    int id;
    int priority;
    std::string description;

    Command(int i, int p, std::string d) : id(i), priority(p), description(d) {}
};

// We need a Functor to tell the queue how to compare two Commands
struct CommandCompare {
    bool operator()(const Command& a, const Command& b) {
        // Returns true if 'a' has lower priority than 'b'
        // (This makes it a Max-Heap for priority)
        return a.priority < b.priority;
    }
};

void custom_priority_demo() {
    std::priority_queue<Command, std::vector<Command>, CommandCompare> tasks;

    tasks.emplace(1, 10, "Low Priority Task");
    tasks.emplace(2, 99, "CRITICAL BUG FIX");
    tasks.emplace(3, 50, "Medium Priority Task");

    std::cout << "Executing: " << tasks.top().description << "\n"; 
    std::cout << "\nRemaining tasks ordered by priority:\n";
    while (!tasks.empty()) {
        std::cout << tasks.top().description << " \n"; 
        tasks.pop();
    }
}
int main()
{
    priority_basics();
    std::cout<<"\nStructs with priority example\n";
    custom_priority_demo();
    

    return 0;
}