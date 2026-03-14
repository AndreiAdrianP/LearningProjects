#include <iostream>
#include <map>
#include <string>

void print_map(const std::map<std::string, int>& ref_map) {
    
    for (const auto& [name, score] : ref_map) {
        std::cout << name << ": " << score << "\n";
    }
}

int main(){

    std::cout<<"Populating map\n";
    std::map<std::string, int> scores;

    scores["Bob"] = 15;
    scores["Alice"]=10;
    scores.insert({"Charlie",20});
    scores.insert({"Carmen",20});    
    scores.try_emplace("Alice",15);
    scores.try_emplace("Blake",17);
    print_map(scores);

 std::cout<<"\n0. Simple searches for David and Alice\n";   
// simple search with if-with-initialiser
    if(auto it = scores.find("David"); it!= scores.end())
    {   
        std::cout << "Found David: " << it->second << "\n";
    }
    //Another version with contains
    if( scores.contains("Alice")){
 std::cout << "Found Alice \n";
    }

std::cout<<"\n1. Query first user that starts with 'C'\n";
if(auto it = scores.lower_bound("C"); it!= scores.end())
    {   
        std::cout << "First entry: " << it->first << "\n";
    }
std::cout<<"\n2. Query all users that starts with 'B'\n";
    auto start = scores.lower_bound("B");
    auto end = scores.lower_bound("C");
    for(auto it = start; it != end; ++it)
    {
        std::cout<<"Found entry: "<< it->first<<"\n";
    }

std::cout<<"\n3. Node extraction: change a key: change Bob with Marley \n";
    auto node = scores.extract("Bob");
    if(!node.empty()){
        node.key() = "Marley";
        scores.insert(std::move(node));
    };
 print_map(scores);
    std::cout<<std::endl;
    return 0;
}