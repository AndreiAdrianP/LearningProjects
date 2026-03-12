#include "PolymorphismDemo.hpp"



int main() {
   
    std::cout<<"\n Runtime polymorphism-----\n";
    std::vector<std::unique_ptr<Shape>> DrawingVector;
    DrawingVector.push_back(std::make_unique<Circle>());
    DrawingVector.push_back(std::make_unique<Square>());
    DrawingVector.push_back(std::make_unique<Circle>());
    DrawingVector.push_back(std::make_unique<Square>());

    for(auto& ptr : DrawingVector )
    {
        ptr->draw();
    }

    std::cout<<"\n---Compile time polymorphism ----\n";
    std::cout<<"\nNow it's a int: ";
    int a=10;
    print_size(a);

    std::cout<<"\nNow it's a double: ";
    double b=20.0;
    print_size(b);

     std::cout<<"\nNow it's a char: ";
    char c ='a';
    print_size(c);

return 0;
}