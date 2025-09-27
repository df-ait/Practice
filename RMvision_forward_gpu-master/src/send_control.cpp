#include "send_control.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>

int64_t port_num = 11452;   //本地绑定端口
int sockfd; //套接字文件描述符
sockaddr_in serv_addr; //本地地址结构
sockaddr_in addr;   //目标地址结构

enum ROBOT_MODE
{
    ROBOT_NO_FORCE,         //无力模式
    ROBOT_FINISH_INIT,      //初始化完成
    ROBOT_FOLLOW_GIMBAL,    //跟随云台
    ROBOT_SEARCH,           //搜索模式
    ROBOT_IDLE,             //空闲模式
    ROBOT_NOT_FOLLOW        //不跟随云台模式
};

struct Vison_control
{
    /*       导航部分       */
    uint8_t header;
    // 线速度 m/s
    float linear_vx;
    float linear_vy;
    // 旋转角速度 rad/s
    float angular;
    // 欧拉角
    float yaw_set;
    float pitch_set;


    ROBOT_MODE mode = ROBOT_MODE::ROBOT_IDLE;
} __attribute__((packed));

void init_send(std::string ip)
{
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(11451);


    sockfd = socket(AF_INET, SOCK_DGRAM, 0);//创建UDP套接字
    if (sockfd < 0) {
        printf("can't open socket\n");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port_num);


    if (bind(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("can't bind socket fd with port number");
    }
}

void send_control(double yaw_set, double pitch_set)
{
    Vison_control pkg{};

    pkg.header = 0x6A;//用于接收方校验数据包有效性
    pkg.yaw_set = yaw_set;
    pkg.pitch_set = pitch_set;

    //发送数据
    auto n = sendto(
    sockfd,
    (const char *)(&pkg),
    sizeof(pkg),
    MSG_CONFIRM,
    (const struct sockaddr *)&addr,
    sizeof(addr));
}