#include <iostream>
#include <memory>
#include <vector>

class Resource {
    private:
    int id_;
    public:
        Resource(int resource_id) : id_(resource_id){
            std::cout<<"--->Resource "<< id_ <<" aquired.\n";
        }
        ~Resource()
        {
            std::cout<<"\t\t\t<----Resource "<<id_<<" released.\n";
        }
        void operate(){
            std::cout<<"\t [ Resource: "<<id_<<" ] Operating.";
        }

};

void unique_ptr_demo();
void shared_ptr_demo();