#include <iostream>
#include <stack>
#include <vector>

bool is_balanced(std::string expression) {
    std::stack<char> s;
    for (char c : expression) {
        if (c == '(') s.push(c);
        else if (c == ')') {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

void demo() {
    std::cout << std::boolalpha << is_balanced("(())") << "\n"; // true
    std::cout << std::boolalpha << is_balanced("(()") << "\n";  // false
}

void print_stack(std::stack<int> s){ //Passed by VALUE (makes a copy) because stack is restricted from iteration
    std::cout<<"Stack is:\n";
    std::cout << "[Top] ";
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << "[Bottom]\n";
}

int main() {
    // By default, stack uses std::deque as its "underlying" container
    std::stack<int> st;
    std::cout<<"Create a stack with 10 20 30\n";
    // 1. Push: Add to the top
    st.push(10);
    st.emplace(20);
    st.push(30);
    print_stack(st);
    // 2. Top: Look at the top element (doesn't remove it)
    std::cout << "Top element: " << st.top() << "\n"; // 30

     std::cout<<"\nRemove top element\n";
    // 3. Pop: Remove the top element (returns void!)
    st.pop(); 

    // 4. Size and Empty
    std::cout << "New top: " << st.top() << " | Size: " << st.size() << "\n";

      std::cout<<"\nCheck if string of paranthesis are properly  closed\n";
      std::cout<<"--First set '(())'\n";
      std::cout<<"Result:" << std::boolalpha << is_balanced("(())") << "\n"; // true
      std::cout<<"--Second set '(()'\n";
      std::cout << "Result: "<< std::boolalpha << is_balanced("(()") << "\n";  // false
    
    std::cout<<"\n\n";
    return 0;
}