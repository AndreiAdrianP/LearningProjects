#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <format>

struct User{
int id;
std::string name;

User(int i, std::string n) : id(i), name(std::move(n)){
    std::cout<<std::format(" > Constructing User: {}\n", name);
}
};

void demonstrate_vector_features(){
   

    // allocate space upfront to avoid multiple reallocations as it grows
    std::vector<User> users;
    users.reserve(5);

    User u1{1, "Alice"};
    users.push_back(u1); // push_back copies an existing object

    //emplace_back constructs the object directly in the vector's memory
    users.emplace_back(2,"Bob");

    try {
        // .at() provides bounds checking, unlike operator[]
        User& secondUser = users.at(1); 
        std::cout << "Accessed: " << secondUser.name << "\n";
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of bounds!\n";
    }
/*-------------------------------------------------------------------*/
  
 //initializer list
    std::vector<int> numbers{5,2,9,1,5, 7,9,10,7,11};
    std::cout << "\nVector numbers: \n";
    for (const auto& n : numbers) {
        std::cout << n << " ";
    }
 std::cout<<"\nRemove the first occurance of number 7 from the int vector \n";
   // USE CASE: Remove ONLY the first instance
if (auto it = std::find(numbers.begin(), numbers.end(), 7); it != numbers.end()) {
    numbers.erase(it);
}

std::cout << "\nVector numbers after erase: \n";
    for (const auto& n : numbers) {
        std::cout << n << " ";
    }
// 5. The "Erase-Remove" Idiom (Pre-C++20) vs std::erase (C++20)
    // Goal: Remove all numbers equal to 5.
    std::cout<<"\nRemove all the numbers equal to 5 from the int vector \n";
    // The  C++11/17 way:
     numbers.erase(std::remove(numbers.begin(), numbers.end(), 5), numbers.end());

    // The Modern C++20 way (Simplified):
   // std::erase(numbers, 5); 


    // 6. Modern Iteration (C++11 Range-based for)
    std::cout << "\nRemaining numbers: ";
    for (const auto& n : numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    std::cout << "--- Before Shrink ---" << "\n";
    std::cout << std::format("Size: {} | Capacity: {}\n", numbers.size(), numbers.capacity());
    
    // This releases unused memory back to the system.
    numbers.shrink_to_fit();

    std::cout << "--- After Shrink ---" << "\n";
    std::cout << std::format("Size: {} | Capacity: {}\n", numbers.size(), numbers.capacity());
};

int main() {
    demonstrate_vector_features();
    return 0;
}