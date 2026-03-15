#include <iostream>
#include <list>
#include <iterator> 
#include <vector>
#include <algorithm>
#include <iterator>


void iterator_helper_demo() {
    std::cout<<"Init list:{ 10,20,30,40,50 }\n";
    std::list<int> l = {10, 20, 30, 40, 50};
    auto it = l.begin();

    // 1. std::advance: Moves the iterator 3 steps forward
    std::advance(it, 3); 
    std::cout << "Advanced 3 steps: " << *it << "\n"; // 40

    // 2. std::distance: How many steps between begin and our current it?
    auto dist = std::distance(l.begin(), it);
    std::cout << "Distance from start: " << dist << "\n"; // 3

    // 3. std::next: Returns a NEW iterator 1 step ahead without moving 'it'
    auto next_it = std::next(it);
    std::cout << "Next element: " << *next_it << "\n"; // 50

}


void category_demo() {

    std::cout<<"Init vector:{1, 2, 3, 4, 5}\n";
    std::cout<<"Init list:{1, 2, 3, 4, 5}\n";
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::list<int> l = {1, 2, 3, 4, 5};

    // --- RANDOM ACCESS (Vector) ---
    auto v_it = v.begin();
    v_it += 3; // LEGAL: O(1) jump. Vector is contiguous.
    std::cout << "Vector index 3: " << *v_it << "\n";
    std::cout << "Vector uses []: " << v_it[1] << "\n"; // Also legal!

    // --- BIDIRECTIONAL (List) ---
    auto l_it = l.begin();
    // l_it += 3; // COMPILER ERROR: std::list iterators don't have operator+=
    
    // We must move it manually or use a helper
    std::advance(l_it, 3); // LEGAL: But this is O(n) under the hood!
    std::cout << "List 'index' 3: " << *l_it << "\n";

    // --- COMPARISON ---
    if (v.begin() < v.end()) { /* Legal for Random Access */ }
    // if (l.begin() < l.end()) { /* ERROR: Only == and != work for List */ }
}

void const_reverse_demo() {
    
     std::cout<<"Init list:{ 10,20,30,40,50 }\n";
    std::vector<int> nums = {10, 20, 30, 40, 50};

    // 1. Const Iterator: Protect the data
    std::cout << "Read-only access: ";
    for (auto it = nums.cbegin(); it != nums.cend(); ++it) {
        // *it = 100; // COMPILER ERROR: Cannot modify through const_iterator
        std::cout << *it << " ";
    }

    // 2. Reverse Iterator: Walk backward
    std::cout << "\nBackward access:  ";
    for (auto rit = nums.rbegin(); rit != nums.rend(); ++rit) {
        std::cout << *rit << " "; // Outputs: 50 40 30 20 10
    }

    // 3. Mixing them: const_reverse_iterator
    auto crit = nums.crbegin(); 
    // This is the "Ultimate Safety" — backward and read-only.
}

void inserters_demo() {
     std::cout<<"Init vector:{1, 2, 3, 4, 5}\n";
    std::vector<int> source = {1, 2, 3, 4, 5};

    // --- 1. The back_inserter ---
    std::vector<int> v; 
    // std::copy(source.begin(), source.end(), v.begin()); // CRASH! v is empty.
    
    // back_inserter calls v.push_back() for every element
    std::copy(source.begin(), source.end(), std::back_inserter(v));

    // --- 2. The front_inserter ---
    std::list<int> l;
    // front_inserter calls l.push_front() - note the result will be reversed!
    std::copy(source.begin(), source.end(), std::front_inserter(l));
    // l now contains: {5, 4, 3, 2, 1}

    // --- 3. The general inserter ---
    std::vector<int> v2 = {10, 20, 30};
    auto it = v2.begin();
    std::advance(it, 1); // Pointing at 20

    // Inserts at a specific position
    std::vector<int> extra = {99, 88};
    std::copy(extra.begin(), extra.end(), std::inserter(v2, it));
    // v2 now: {10, 99, 88, 20, 30}
}


void stream_iter_demo() {
    // --- 1. Writing to Console ---
      std::cout<<"Init vector:{1, 2, 3, 4, 5}\n";
    std::vector<int> nums = {1, 2, 3, 4, 5};

    std::cout << "Contents of vector: ";
    // We "copy" from the vector to the console iterator
    std::copy(nums.begin(), nums.end(), 
              std::ostream_iterator<int>(std::cout, " ")); 
    std::cout << "\n";


    // --- 2. Reading from Keyboard ---
    std::cout << "Enter numbers (Ctrl+D to stop): ";
    
    // Create an iterator that listens to cin
    std::istream_iterator<int> cin_it(std::cin);
    // Create a "sentinel" that marks the end of input
    std::istream_iterator<int> sentinel;

    // Fill a vector directly from the keyboard!
    std::vector<int> input_data;
    std::copy(cin_it, sentinel, std::back_inserter(input_data));


    // --- 3. Immediate Processing ---
    std::cout << "You entered: ";
    std::copy(input_data.begin(), input_data.end(), 
              std::ostream_iterator<int>(std::cout, " | "));
}

int main(){

iterator_helper_demo();
category_demo();
const_reverse_demo();
stream_iter_demo();

    return 0;
}