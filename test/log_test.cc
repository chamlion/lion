#include <lion/base/log.h>
#include <lion/base/base.h>
#include<iostream>
#include <chrono>
#include<thread>
#include<string.h>
#include<memory>
 /*
 输出结果 每行类似于以下格式
 2016-10-04-17:09:49-log_test.cc-14-fun-615790336-hello  every body
 */
using namespace lion;
LogInit();//初始化日志类
void fun()
{
  for (int i=0;i<500000;i++)
  {
 LOG_DEBUG("hello  every body");
  }
}
int main()
{   std::shared_ptr<during> d(new during);
    LOG2FILE();//设置日志输出到文件 
    SETROLLTIME(3);//设置换写日志时间间隔
    std::thread t1(fun);
    std::thread t2(fun);
    std::thread t3(fun);
    std::thread t4(fun);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
 
   /* char str[1024]={"log"};
  strcat(strcat(str,Timer().ToStr()),".log");
     std::cout<<str<<std::endl;
   // g_file = fopen(str, "w");*/
   
 return 0;
}
