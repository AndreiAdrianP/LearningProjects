#include <iostream>
#include <unordered_map>
#include <string>

template <typename K, typename V>
void print_unordered_map(const std::unordered_map<K, V>& umap) {
    if (umap.empty()) {
        std::cout << "[Empty Unordered Map]\n";
        return;
    }
    
    std::cout << "{ \n";
    for (const auto& [key, value] : umap) {
        std::cout << "  [" << key << "] : " << value << "\n";
    }
    std::cout << "}\n";
}

struct Point {
    int x, y;

    // 1. Equality Operator: Needed to handle collisions in a bucket
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// 2. Hash Function: We create a "Functor" (a struct with operator())
struct PointHasher {
    std::size_t operator()(const Point& p) const {
        // A common technique is to hash the individual members 
        // and combine them using bit-shifting or XOR.
        std::size_t h1 = std::hash<int>{}(p.x);
        std::size_t h2 = std::hash<int>{}(p.y);
        
        // Simple combination logic (XOR and bit-shift)
        return h1 ^ (h2 << 1); 
    }
};

void custom_key_demo() {
    // We pass our PointHasher as the 3rd template argument
    std::unordered_map<Point, std::string, PointHasher> grid_labels;

    grid_labels[{10, 20}] = "Treasure";
    grid_labels[{0, 0}]   = "Start";

    std::cout << "Location {10, 20}: " << grid_labels[{10, 20}] << "\n";
    std::cout << "Map Contents ---\n";
    for (const auto& [point, label] : grid_labels) {
        std::cout << "Point(" << point.x << "," << point.y << ") -> " << label << "\n";
    }

    // 3. Performance Metrics
    std::cout << "\nPerformance Stats ---\n";
    std::cout << "Bucket Count: " << grid_labels.bucket_count() << "\n";
    std::cout << "Load Factor:   " << grid_labels.load_factor() << "\n";
    std::cout << "Max Load Fact: " << grid_labels.max_load_factor() << "\n";
}


int main(){

    std::cout<<"Init unordered map elements:\n";
    std::unordered_map<std::string, std::string> ip_addresses = {
        {"localhost", "127.0.0.1"},
        {"google", "8.8.8.8"},
        {"gateway", "192.168.1.1"}
    };
    print_unordered_map(ip_addresses);

    // 2.Lookup
    //std::cout << "Google IP: " << ip_addresses["google"] << "\n";
    
    std::cout<<"\n1a. Bucket information:\n";
    // 3. Bucket Information (The "Under the Hood" stuff)
    std::cout << "Bucket count: " << ip_addresses.bucket_count() << "\n"; //how many slots exist
    std::cout << "Load factor: " << ip_addresses.load_factor() << "\n"; // average no of elements (size/ bucket_count), if exceeds usually 1 then rehash is needed 
    
    std::cout<<"\n1b.Bucket information after reserving space to avoid re-hashing :\n";
    ip_addresses.reserve(100);
    std::cout << "Bucket count: " << ip_addresses.bucket_count() << "\n";
    std::cout << "Load factor: " << ip_addresses.load_factor() << "\n";

    std::cout<<"\n2. Find where key google is stored:\n";
    std::string key = "google";
    size_t bucket = ip_addresses.bucket(key);
    std::cout << "Key '" << key << "' is in bucket #" << bucket << "\n";

    std::cout<<"\n3. Insert or assign {gateway, 192.168.0.1}\n";
    auto[it, inserted] = ip_addresses.insert_or_assign("gateway","192.168.0.1");
    if (inserted) 
      {  std::cout << "New location discovered!\n";
    }

    else 
       { std::cout << "Location updated.\n";
    }
    print_unordered_map(ip_addresses);


    std::cout<<"\n4. Custom key and hash demo---\n";
    custom_key_demo();

    std::cout<<"\n\n";
    return 0;
}