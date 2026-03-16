#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Product {
    int id;
    std::string name;
};

void searching_demo() {
    std::cout<<"Init vector: 5,3,9,1,7,2\n";
    std::vector<int> nums = {5, 3, 9, 1, 7, 2};

    // --- 1. std::find ---
    std::cout<<"\nFind 9\n";
    auto it = std::find(nums.begin(), nums.end(), 9);
    
    if (it != nums.end()) {
        std::cout << "Found " << *it << " at index " << std::distance(nums.begin(), it) << "\n";
    }

    // --- 2. std::find_if (The Lambda Powerhouse) ---
     std::cout<<"\n Find the first even number\n";
    // Find the first even number
    auto even_it = std::find_if(nums.begin(), nums.end(), [](int n) {
        return n % 2 == 0;
    });

    if (even_it != nums.end()) {
        std::cout << "First even number: " << *even_it << "\n";
    }
    std::cout<<"\n Binary search if 5 exists\n";
    // --- 3. std::binary_search (Fast but limited) ---
    std::vector<int> sorted_nums = {1, 2, 3, 5, 7, 9}; // Must be sorted!
    bool exists = std::binary_search(sorted_nums.begin(), sorted_nums.end(), 5);
    std::cout << "Does 5 exist? " << (exists ? "Yes" : "No") << "\n";

    std::cout<<"\n Find the firt pair of duplicates in 1, 2, 2, 3, 4, 5, 5, 6\n";
    std::vector<int> stream = {1, 2, 2, 3, 4, 5, 5, 6};
    auto dup = std::adjacent_find(stream.begin(), stream.end());
    std::cout<<*dup;
    std::cout<<"\n\n";
}


int main(){

searching_demo();
    return 0;
}