#include <iostream>
#include <list>
#include <algorithm>
#include <string>

void print_list(const std::list<std::string>& words){
std::cout<<"\n---List: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    };
    std::cout<<std::endl;
};
int main() {
    std::cout<<"Demonstration of list capabilities. \nInit list:";

    std::list<std::string> words = {"apple", "banana", "cherry"};
    print_list(words);

    std::cout<<"\n1.Insert apricot at first element and date at last element\n";
    words.push_front("apricot"); 
    words.push_back("date");
    print_list(words);

std::cout<<"\n2. Remove cherry from list";
words.remove("cherry"); // by value, it does the search
print_list(words);

std::cout<<"\n3. Remove banana from list";
if (auto it = std::find(words.begin(), words.end(), "banana"); it != words.end()) {
        words.erase(it); 
    }
print_list(words);

std::cout<<"\n4. Splicing: moving list:{elderberry,fig} to our list\n";
std::list<std::string> other_words = {"elderberry", "fig"};
std::cout<<"The other_list size is: "<<other_words.size()<<std::endl;;
auto it_insertion = std::find(words.begin(), words.end(), "date");
    words.splice(it_insertion, other_words);
print_list(words);
std::cout<<"The other_list size is after splicing: "<<other_words.size()<<std::endl;
    return 0;
}