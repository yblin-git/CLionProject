#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

std::string DoubleToStringByStringStream(double value) {
    std::ostringstream stream;
    stream << value;
    return stream.str();
}
template<typename T>
std::string to_string1(
        const T value, int width,
        typename std::enable_if<std::is_integral<T>::value ||
                                std::is_floating_point<T>::value>::type* = 0) {
    std::ostringstream out;
    out << std::setfill('0') << std::setw(width) << value;
    return out.str();
}
std::string DoubleToString(const double value, unsigned int precisionAfterPoint = 6)
{
    std::ostringstream out;
    // 清除默认精度
    out.precision(std::numeric_limits<double>::digits10);
    out << value;

    std::string res = std::move(out.str());
    auto pos = res.find('.');
    if (pos == std::string::npos)
        return res;

    auto splitLen = pos + 1 + precisionAfterPoint;
    if (res.size() <= splitLen)
        return res;

    return res.substr(0, splitLen);
}
std::string to_String2(int n) {
    int m = n;
    char s[128];
    char ss[128];
    int i = 0, j = 0;
    if (n < 0)  // 处理负数
    {
        m = 0 - m;
        j = 1;
        ss[0] = '-';
    }
    while (m > 0) {
        s[i++] = m % 10 + '0';
        m /= 10;
    }
    s[i] = '\0';
    i = i - 1;
    while (i >= 0){
        ss[j++] = s[i--];
    }
    ss[j] = '\0';
    return ss;
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    std::ofstream file;
    file<<"1 ";
    file<<"2 ";
    file.open("/tmp/test.txt");
    file<<"3 ";
    file<<"4 ";
    file<<"5 ";
    file<<"6 ";
    file<<"7 ";
    file.close();
    std::ifstream  in("test.txt");


    char value =0;

    uint8_t value1=250;

    value = value1;

    printf("value %d\n",value);
//    std::cout << "value:" <<value<< std::endl;
    int8_t value2= value;
    printf("value2 %d\n",value2);
//    std::cout << "value:" <<value2<< std::endl;
    printf("value %d\n",(int8_t)value);

    printf("value %d\n",(uint8_t)value);

//    std::cout << "value:" <<(int8_t)value<< std::endl;
    double s1= 12345678.12233;
   auto s2=  DoubleToStringByStringStream(s1);
    std::cout << "s2: " << s2<<std::endl;
    double timestamp = std::atof(s2.c_str());
    std::cout << "timestamp: " << timestamp<<std::endl;
    printf("timestamp %lf\n",timestamp);
    auto s3 = std::to_string(s1);
    std::cout << "s3: " << s3<<std::endl;
    double timestamp1 = std::atof(s3.c_str());
    std::cout << "timestamp1: " << timestamp1<<std::endl;
    printf("timestamp1 %lf\n",timestamp1);


    std::cout << "size: " << sizeof (s1)<<std::endl;
   auto s4= to_String2(s1);
    std::cout << "s4: " << s4<<std::endl;

    double timestamp2 = std::atof(s4.c_str());
    std::cout << "timestamp2: " << timestamp2<<std::endl;
    printf("timestamp2 %lf\n",timestamp2);


   auto s5 =  DoubleToString(s1);
    std::cout << "s5: " << s5<<std::endl;
    double timestamp3 = std::atof(s5.c_str());
    std::cout << "timestamp3: " << timestamp3<<std::endl;
    printf("timestamp3 %lf\n",timestamp2);
    return 0;
}
