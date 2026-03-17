#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


struct Product {
    std::string name;
    double price;
    int priority;

    // Helper to make the output look clean
    void print() const {
        std::cout << std::left << name 
                  << " | Price: $"  << price 
                  << " | Priority: " << priority << "\n";
    }
};

void print_helper(const std::vector<Product>& shop)
{
for( const auto& it : shop)
    {
        it.print();
    }
}

void ordering_demo() {
    std::vector<Product> shop = {
        {"Laptop",  999.99, 1},
        {"Mouse",   25.50,  3},
        {"Monitor", 299.00, 3},
        {"Keyboard", 75.00,  3},
        {"Cable",   10.00,  2},
        {"Desk",    150.00, 1}
    };
    std::cout<<"Init products vector:\n";
    print_helper(shop);
    
    

  std::cout<<"\n Standard Sort alphabetically:\n";
    
    std::sort(shop.begin(), shop.end(), [](const Product& a, const Product& b) {
        return a.name < b.name;
    });
    print_helper(shop);


    std::cout<<"\n Find the 3 cheapest items and put them at the very beginning:\n";
    std::partial_sort(shop.begin(), shop.begin() + 3, shop.end(), 
        [](const Product& a, const Product& b) {
            return a.price < b.price;
    });
     print_helper(shop);


       std::cout<<"\n F Find the product with the middle price without sorting everything:\n";
  
    auto mid_it = shop.begin() + shop.size() / 2;
    std::nth_element(shop.begin(), mid_it, shop.end(), 
        [](const Product& a, const Product& b) {
            return a.price < b.price;
    });
   
    mid_it->print();
    

    std::cout<<"\n Sort by Priority, but KEEP the alphabetical name order for items with the same priority:\n";
    // --- 5. Stable Sort (O(n log n)) ---
    // Goal: Sort by Priority, but KEEP the alphabetical name order for items with the same priority.
    // If we used std::sort here, the names might get jumbled within the priority groups.
    std::stable_sort(shop.begin(), shop.end(), [](const Product& a, const Product& b) {
        return a.priority < b.priority;
    });
    print_helper(shop);

    

    
}

template <typename T>
void print_vector(const T& data) {
    std::cout << "\nVector: "; 
    for (const auto& item : data) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void partitioning_demo() {
    std::cout<<"\n-----PARTITIONING DEMO---\n";
    std::cout<<"\nInit vector: 1, 10, 2, 9, 3, 8, 4, 7, 5, 6\n";
    std::vector<int> nums = {1, 10, 2, 9, 3, 8, 4, 7, 5, 6};

    std::cout<<"\nPut all numbers >= 6 on the left:\n";
 
    auto pivot = std::partition(nums.begin(), nums.end(), [](int n) {
        return n >= 6;
    });
   

    // 1. Print only the "Passed" numbers (6 and above)
    std::cout << "Accepted: ";
    for (auto it = nums.begin(); it != pivot; ++it) {
    std::cout << *it << " ";
    }

    // 2. Print only the "Failed" numbers (below 6)
    std::cout << "\nRejected: ";
    for (auto it = pivot; it != nums.end(); ++it) {
    std::cout << *it << " ";
    }
    std::cout<<"\nResulted vector: ";
    print_vector(nums);

     std::cout<<"\n\nInit vector: 1, 2, 3, 4, 5, 6, 7, 8, 9\n";
    std::cout<<"\nPut evens first, keep their relative order\n";
    
    std::vector<int> vals = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // Put evens first, keep their relative order (2 stays before 4, etc.)
    std::stable_partition(vals.begin(), vals.end(), [](int n) {
        return n % 2 == 0;
    });
    print_vector(vals);

std::cout<<"\nPartition point (first odd number) on the partitioned vector\n";
    // --- 3. std::partition_point ---
    // If a range is already partitioned, you can find the split instantly.
    auto split = std::partition_point(vals.begin(), vals.end(), [](int n) {
        return n % 2 == 0;
    });
    std::cout << "\nFirst odd number: " << *split << "\n";
}


int main()
{
    ordering_demo();
    partitioning_demo();


    return 0;
}