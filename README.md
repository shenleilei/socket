# socket
linux系统下常见的socket通信包括客户端与内核和客户端与服务器
需要注意的是linux用户与内核之间的通信需要在内核的头文件的netlink.h和用户的头文件netlink.h中定义一个接口
#define NETLINK_TEST 22
