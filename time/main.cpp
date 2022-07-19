#include <iostream>
#include <ctime>
#include <unistd.h>

using namespace std;
constexpr uint8_t kCloudReadHour = 13;  //每天16点开始启动可以录制
constexpr uint8_t kOneDayHour = 24;  //每天16点开始启动可以录制
constexpr uint64_t kIntervalRecordTime = 28800;  // s 间隔8小时后开始启动可以录制

time_t CalRecordLimitTime() {
    time_t now = time(0);
    cout << "1970 到目前经过秒数:" << now;
    tm* ltm = localtime(&now);
    cout << 1900 + ltm->tm_year << "年" << 1 + ltm->tm_mon << "月"
              << ltm->tm_mday << "日" << ltm->tm_hour << ":" << ltm->tm_min << ":"
              << ltm->tm_sec;
    if (ltm->tm_hour < kCloudReadHour) {
        return (now + (((kCloudReadHour - ltm->tm_hour) * 60 * 60) -
                       (ltm->tm_min * 60) - (ltm->tm_sec)));
    } else {
        return (now + ((kOneDayHour + kCloudReadHour - ltm->tm_hour) * 60 * 60) -
                (ltm->tm_min * 60) - (ltm->tm_sec));
    }
}
int main( )
{
    // 基于当前系统的当前日期/时间
    time_t now = time(0);
    auto milli_seconds =  CalRecordLimitTime();

    cout <<"\n"<< "time:" << milli_seconds<<" hour: "<<(int)((milli_seconds-now)/3600)<<" minute: "<< (int)((milli_seconds-now)%3600/60)<< endl;

    time_t now1 = time(0);
    tm* ltm1 = localtime(&now1);
    cout << 1900 + ltm1->tm_year << "年" << 1 + ltm1->tm_mon << "月"
         << ltm1->tm_mday << "日" << ltm1->tm_hour << ":" << ltm1->tm_min << ":"
         << ltm1->tm_sec<< endl;
    now1+=kIntervalRecordTime;
    ltm1 = localtime(&now1);
    cout << 1900 + ltm1->tm_year << "年" << 1 + ltm1->tm_mon << "月"
         << ltm1->tm_mday << "日" << ltm1->tm_hour << ":" << ltm1->tm_min << ":"
         << ltm1->tm_sec<< endl;
}