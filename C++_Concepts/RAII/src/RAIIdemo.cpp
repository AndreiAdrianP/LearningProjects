#include "RAIIdemo.hpp"

void unique_ptr_demo() {
    std::cout << "\n--- Unique Pointer Demo (Exclusive RAII) ---" << std::endl;
    
    
    std::unique_ptr<Resource> ptr1 = std::make_unique<Resource>(1);

    ptr1->operate();    
    std::cout << "Unique pointer scope is about to end..." << std::endl;
    
} 


void shared_ptr_demo() {
    std::cout << "\n--- Shared Pointer Demo (Reference Counted RAII) ---" << std::endl;
    
    
    std::shared_ptr<Resource> shared_ptr_owner = std::make_shared<Resource>(2);

    std::cout << "Ref count (Owner): " << shared_ptr_owner.use_count() << std::endl;

    { // Inner scope: Creation of temporary shared references
        std::shared_ptr<Resource> shared_ptr_ref1 = shared_ptr_owner;
        std::shared_ptr<Resource> shared_ptr_ref2 = shared_ptr_ref1;

        std::cout << "Ref count (Inner scope): " << shared_ptr_owner.use_count() << std::endl;
        shared_ptr_ref2->operate();
        
    } 
      

    std::cout << "Ref count (Owner after inner scope): " << shared_ptr_owner.use_count() << std::endl;      
    std::cout << "Shared pointer owner scope is about to end..." << std::endl;
    
} 


int main() {
    unique_ptr_demo();
    shared_ptr_demo();
    
    std::cout << "\n--- Program Finished ---" << std::endl;
    return 0;
}