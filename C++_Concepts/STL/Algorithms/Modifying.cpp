#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

template <typename T>
void print_vector(const T& data) {
    std::cout << "\nVector: "; 
    for (const auto& item : data) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}
void modifying_demo() {
    std::cout<<"Init vector: 0,0,0,0,0\n";
    std::vector<int> nums(5); 

     std::cout<<"\nFill the vector with indices:\n";  
    std::iota(nums.begin(), nums.end(), 1);
    print_vector(nums);

    std::cout<<"\nTransform (In-place): Square every number:\n";    
    std::transform(nums.begin(), nums.end(), nums.begin(), [](int n) {
        return n * n;
    }); 
     print_vector(nums);

    std::cout<<"\nTransform (Out-of-place): Convert to strings Val:[number]\n";      
    std::vector<std::string> labels;
    std::transform(nums.begin(), nums.end(), std::back_inserter(labels), [](int n) {
        return "Val: " + std::to_string(n);
    });
    print_vector(labels);

     std::cout<<"\nReplace squares > 10 with 0:\n";    
    std::replace_if(nums.begin(), nums.end(), [](int n) { return n > 10; }, 0);
    print_vector(nums);

      std::cout<<"\n Delete all numbers less than 3:\n";   
    nums.erase(std::remove_if(nums.begin(), nums.end(), [](int n) {
        return n < 3;
    }), nums.end());
    print_vector(nums);

}

void moving_demo() {
     std::cout<<"\n-------\nInit vector for cpoy/move: \n";
    std::vector<std::string> source = {"Alpha", "Beta", "Gamma", "Delta"};
     print_vector(source);

    std::cout<<"\n Basic Copy (To a pre-sized vector:\n";    
    std::vector<std::string> copy_dest(source.size());
    std::copy(source.begin(), source.end(), copy_dest.begin());
    std::cout<<"\n Destination vector is:\n";    
    print_vector(copy_dest);

    std::cout<<"\n Only copy strings longer than 4 characters:\n";    
    std::vector<std::string> filtered;
    std::copy_if(source.begin(), source.end(), 
                 std::back_inserter(filtered), 
                 [](const std::string& s) { return s.size() > 4; });
    std::cout<<"\n Destination vector is:\n";    
    print_vector(filtered);

    std::cout<<"\n Move vector:\n";   
    
    std::vector<std::string> moved_dest;
    std::move(source.begin(), source.end(), std::back_inserter(moved_dest));
    std::cout<<"\n Destination vector is:\n";    
    print_vector(moved_dest);
    std::cout << "\nSource AFTER MOVE:\n";
    // 1. The vector still has 3 "slots"...
    std::cout << "Source vector size: " << source.size() << "\n";

    // 2. ...but those slots now contain empty strings!
    for (size_t i = 0; i < source.size(); ++i) {
        std::cout << "Source[" << i << "] is: '" << source[i] << "' (Length: " 
                  << source[i].length() << ")\n";
    }

}

int main()
{
    modifying_demo();
    moving_demo();

    return 0;
}