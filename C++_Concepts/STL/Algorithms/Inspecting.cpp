#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
   std::cout<<"Init vector level: 1, 2, 3, 4, 5, 10, 15\n";
    std::vector<int> levels = {1, 2, 3, 4, 5, 10, 15};

    // --- 1. Logic Checks ---
    std::cout<<"\nAre all the levels positive?\n";
    bool is_positive = std::all_of(levels.begin(), levels.end(), [](int l) { 
        return l > 0; 
    });
    std:: cout<<std::boolalpha<<is_positive;
    std::cout<<"\nAre there levels >=10?\n";
    bool has_boss_level = std::any_of(levels.begin(), levels.end(), [](int l) { 
        return l >= 10; 
    });
     std::cout<<has_boss_level;

    // --- 2. Counting ---
    std::cout<<"\nHow many levels greater than 5?\n";
    int high_levels = std::count_if(levels.begin(), levels.end(), [](int l) {
        return l > 5;
    });
    std::cout<<high_levels;

    // --- 3. Mismatch (Comparing two sequences) ---
     std::cout<<"\nCheck mismatch with expcted vector: 1,2,3,4,99\n";
    std::vector<int> expected = {1, 2, 3, 4, 99}; // 99 is different from 5
    auto [it1, it2] = std::mismatch(levels.begin(), levels.end(), expected.begin());

    if (it1 != levels.end() && it2 != expected.end()) {
        std::cout << "Mismatch found! Levels has " << *it1 
                  << " but Expected has " << *it2 << "\n";
    }



return 0;
}