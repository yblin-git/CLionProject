#include <iostream>

class service{
public:
    std::unique_ptr<common_data::Epoll> recv_epoll_;
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
