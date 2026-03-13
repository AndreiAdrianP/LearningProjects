#include <iostream>
#include <deque>
#include <algorithm>
#include <vector>

void print_deque(std::deque<int>& nums){

    std::cout<<"\n---Deque contains: ";
    for(const auto& it : nums)
    {   std::cout << it << " ";
        };
    std::cout<<std::endl;
};

void sliding_window_ex(std::deque<int>& nums){
     std::vector<int> numbers{5,2,9,1,5, 7,9,10,7,11};
    std::cout<<"\nInit numbers:";
 
     for(const auto& it : numbers)
     {   std::cout << it << " ";
        };
std::cout<<std::endl;
   print_deque(nums);
        for(const auto& it : numbers)
     {   
        nums.push_back(it);
        if(nums.size()>3){
            nums.pop_front();
        }
        print_deque(nums);
        };



    
};

int main()
{
    std::cout<<"Deque initialisation:";

    std::deque<int> nums = {10,20,30};
    print_deque(nums);

     std::cout<<"\n1.Add '5' at the beginning and '10' at end";
     nums.push_front(5);
     nums.emplace_back(10);
     print_deque(nums);

     std::cout<<"\n2.Add '7' at index 3";
     auto it = nums.begin()+3;
     nums.insert(it, 7);
     print_deque(nums);

     std::cout<<"\n3.Removing from both ends and shrink size";
     std::cout<<"Size before removing and shrinking: "<<nums.size();

     nums.pop_front();
     nums.pop_back();
     print_deque(nums);
     nums.shrink_to_fit();
    std::cout<<"Size after removing and shrinking: "<<nums.size();
    std::cout<<std::endl;

    std::cout<<"\n4.Sliding window of 3 on an 10 elem input";
    nums.resize(3);
    nums.assign(3,0);
    
    sliding_window_ex(nums);
    
    
    return 0;
}