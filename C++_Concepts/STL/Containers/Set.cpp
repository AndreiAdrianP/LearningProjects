#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename T, typename Compare, typename Alloc>
void print_set(const std::set<T, Compare, Alloc>& s) {
    std::cout << "{ ";
    for (const auto& item : s) {
        std::cout << item << " ";
    }
    std::cout << "}\n";
}

int main()
{

    std::cout<<"Init set: 20,5,10,5,1\n";
    std::set<int> numbers = {20,5,10,5,1};
    print_set(numbers);

    std::cout<<"\n1.Insert 15 and 10\n";
    numbers.emplace(15);
    auto [it, success]= numbers.insert(10);
    if(!success){
        std::cout << "10 already exists, insertion failed!\n";
    }
    print_set(numbers);

    std::cout<<"\n2. Check if set contains 15 and 5  \n";
    if (numbers.contains(15)) {
        std::cout << "15 is in the set.\n";
    }

    auto find_it = numbers.find(5);
    if (find_it != numbers.end()) {
        std::cout << "Found: " << *find_it << "\n";
    }


    std::cout<<"\n3. Range construction: dump vector {4 1 2 1 4 3} into a new set  \n";
    std::vector<int> v = {4, 1, 2, 1, 4, 3};
    std::set<int> s(v.begin(), v.end());
    print_set(s);


    std::cout<<"\n4. New set {1 2 3 4 5} sorted in descending order\n";
    std::set<int, std::greater<int>> descending_set = {1, 2, 3, 4, 5};
    print_set(descending_set);

    std::cout<<"\n5. Bulk range insertion, vector { 5 6 7}  \n";
    std::vector<int> extra_data = {5,6,7};
    descending_set.insert(extra_data.begin(), extra_data.end());
    print_set(descending_set);

    std::cout<<"\n6. Merge other_set { 8 9 10} \n";
    std::set<int> other_set{8,9,10};
    std::cout<<"\n Other set size before merging: "<<other_set.size()<<"\n";
    descending_set.merge(other_set);
    print_set(descending_set);
    std::cout<<"\n Other set size after merging: "<<other_set.size()<<"\n";


    std::cout<<"\n7. Range deletion from beginning up to 5 \n";
    descending_set.erase(descending_set.begin(), descending_set.find(5));
     print_set(descending_set);

    std::cout<<"\n8. Set mathematics: intersection of {1,2,3,4} wit {3,4,5,6} \n";
    std::set<int> s1 = {1, 2, 3, 4};
    std::set<int> s2 = {3, 4, 5, 6};
    std::set<int> result;
    // interator insterter works only for set and maps
    std::set_intersection(s1.begin(), s1.end(),
                          s2.begin(), s2.end(),
                          std::inserter(result, result.begin()));

    std::cout<<"\nResult of intersection: ";
    print_set(result);





    std::cout<<"\n\n";
    return 0;
}