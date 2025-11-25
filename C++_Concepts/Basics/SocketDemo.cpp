#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <unistd.h>      // close()
#include <sys/socket.h>  // socket, bind, listen, accept
#include <netinet/in.h>  // sockaddr_in
#include <arpa/inet.h>   // htons, htonl
#include <chrono>

// Function to handle a single client connection in its own thread
void handle_client(int client_socket) {
    std::cout << "[Client Handler] Thread started for socket: " << client_socket << std::endl;
    
    const char* message = "Hello from the C++ POSIX server! Closing connection.\n";
    send(client_socket, message, strlen(message), 0);
    
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "[Client Handler] Closing socket: " << client_socket << std::endl;
    close(client_socket); // POSIX function to close the socket
}

int main() {
    std::cout << "--- Simple Multi-Threaded TCP Server (POSIX) ---\n";
    std::cout<<"----!Note!---Running continously, manually interrupt the program!---\n";
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int port = 8080;
    
    // 1. Create socket file descriptor
    // AF_INET for IPv4, SOCK_STREAM for TCP
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return 1;
    }
    
    // Set socket options to reuse address/port (prevents 'Address already in use' errors)
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        return 1;
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Bind to all interfaces (0.0.0.0)
    address.sin_port = htons(port);       // Convert port number to network byte order
    
    // 2. Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 1;
    }
    
    // 3. Listen for incoming connections (max 10 pending connections)
    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        return 1;
    }
    
    std::cout << "Server listening on port " << port << "...\n";
    std::cout << "To test: Run 'telnet 127.0.0.1 8080' in another terminal.\n";

    // 4. Accept connections in a loop
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        
        // Block until a new client connects
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue; 
        }
        
        std::cout << "Connection accepted. Socket FD: " << new_socket << std::endl;

        // 5. Spawn a new thread to handle the client
        std::thread client_thread(handle_client, new_socket);

        // Detach the thread. Note: This means the main thread won't wait for it.
        // In a real app, you would manage and join these threads better.
        client_thread.detach(); 
    }
    
    close(server_fd); 
    return 0;
}