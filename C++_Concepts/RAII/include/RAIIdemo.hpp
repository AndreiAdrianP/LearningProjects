#include <iostream>
#include <memory>
#include <vector>

class FileHandle {
    private:
    int id_;
    public:
        FileHandle(int resource_id) : id_(resource_id){
            std::cout<<"--->Resource "<< id_ <<" aquired.\n";
        }
        ~FileHandle()
        {
            std::cout<<"\t\t\t<----Resource "<<id_<<" released.\n";
        }
        int get_Id() const
        {return id_;}

};

std::unique_ptr<FileHandle> process_data();
void print_status( const FileHandle& resource);
