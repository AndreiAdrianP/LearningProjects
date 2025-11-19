#include <iostream>
#include <memory>
#include <vector>

class Shape{
public:
    virtual void draw()=0;
    virtual ~Shape() = default;
};

class Circle : public Shape{
    public:
      void draw() override{
        std::cout<<"\n Drawing a circle \n";

    }
};

class Square : public Shape{
    public:
      void draw() override{
        std::cout<<"\n Drawing a square \n";

    }
};

template<typename T>
void print_size(T& a)
{
        std::cout<<"I'm a size "<<sizeof(a)<<std::endl;
};