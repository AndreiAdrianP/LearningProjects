#include "RAIIdemo.hpp"



std::unique_ptr<FileHandle> process_data(){
    std::cout<<"[processData] Allocating FileHandle on Heap\n";
    return std::make_unique<FileHandle>(1);
}

void print_status( const FileHandle& resource){
    std::cout<<"Checking for resource with id: "<<resource.get_Id()<<std::endl;
}

int main() {
   
    std::unique_ptr<FileHandle> other_ptr = process_data();
    print_status(*other_ptr);
    
    std::cout<<"\n----Shared ownership-----\n";
    std::shared_ptr<FileHandle> shared_owner = std::make_shared<FileHandle>(2);
    std::cout<<"Initial shared reference count: "<<shared_owner.use_count()<<std::endl;
    {
        std::cout<<"\nInner scope---- \n";
        std::shared_ptr<FileHandle> copy_owner = shared_owner;
        std::cout<<"\tShared reference count(should be 2): "<<shared_owner.use_count()<<std::endl;
        print_status(*shared_owner);


    }
    std::cout<<"\tShared reference count after copy_owner out of scope(should be 1): "<<shared_owner.use_count()<<std::endl;
    std::cout << "\n--- Program Finished ---" << std::endl;
    return 0;
}