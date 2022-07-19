#include <iostream>
#include <fstream>
#include <regex>
using namespace  std;

inline vector<string> StringSplit(const string& in, const string& delim) {
    vector<string> args;
    if (in.empty()) {
        return args;
    }
    try {
        regex re{delim};
        return std::vector<string>{
                std::sregex_token_iterator(in.begin(), in.end(), re, -1),
                std::sregex_token_iterator()
        };
    } catch(const std::exception& e) {
        std::cout << "StringSplit with exception:" << e.what();
    }
    return args;
}

int setLoraSting(std::string &str){
    str = "112345";
}
constexpr int kBitGyro = (1 << 0);
constexpr int kBitLaser = (1 << 1);
constexpr int kBitOdom = (1 << 2);
constexpr int kBitMonoImage = (1 << 3);
constexpr int kBitDepthImage = (1 << 4);
constexpr int kBitIrImage = (1 << 5);
constexpr int kBitTopIrImage = (1 << 6);
constexpr int kBitBinoLeftImage = (1 << 7);
constexpr int kBitLaserDataImage = (1 << 8);
int main(int argc,char* argv[])
{
//    std::string filename = argv[1];
//    std::map<std::string,int>name_times_;
//    std::ifstream in_;
//    in_.open(filename);
//    if (!in_.is_open()) {
//       std::cout << "open time file error: " << filename;
//        return -1;
//    }
//    char str[512] = {0};
//    while(in_.getline(str, sizeof(str), '\n')){
//        std::string str1 = str;
//        auto str_vector = StringSplit(str1, "=>");
//        std::cout << "str: " << str << " frame_num: " << str_vector[0]<<endl;
//        auto item  = name_times_.find(str_vector[0]);
//        if(item!=name_times_.end()){
//            item->second++;
//        }else{
//            name_times_[str_vector[0]]=1;
//        }
//    }
//    map<string,int>::iterator iter;//定义一个迭代指针iter
//      for(iter=name_times_.begin(); iter!=name_times_.end(); iter++)
//      {
//          if(iter->second>90&&iter->second<110)
//              cout<<iter->first <<"->"<<iter->second<<endl;
//      }
//    std::cout <<  "tcsetattr error: " << std::strerror((int)1);
    std::string str;
    setLoraSting(str);

    std::cout <<  "str: " << str<<std::endl;

    int result = 0;
    result|=kBitGyro;
    std::cout <<  "result: " << result<<std::endl;
    result|=kBitLaser;
    std::cout <<  "result: " << result<<std::endl;
    int* fd_ptr_ {nullptr};
    fd_ptr_ = new int[30];
    fd_ptr_[0] = 12;
    int fd2 = fd_ptr_[0];
    std::cout <<  "fd2: " << fd2<<std::endl;

}