#ifndef LOG_H
#define LOG_H
#include <string>
#include <algorithm>
#include<iostream>
#include<string>
#include<thread>
#include<atomic> //bool
#include "BlockingQueue.h"
#include <functional>
/*

该日志类为异步日志类，为单例模式
支持输出位置重定向
动态改变日志输出级别
具体实现方法，类似于生产者-消费者问题的解决方式
将各个线程的日志信息，保存到阻塞队列中，然后一个线程专门负责将队列中的数据写入到具体的
输出流中。
使用方式 
首先调用 LogInit() 函数初始化日志类为全局变量(该函数要在主函数之外使用)
可以通过 SETLOGOUT() 改变日志输出函数
可以通过 SETLEVEL() 改变日志输出级别
通过 LOG_TRACE(string) LOG_DEBUG(string) LOG_INFO(string) 输出相应级别的日志
*/
namespace lion
{  
  typedef std::function<void ()> FuncFlush; //flush函数
  typedef std::function<void (const std::string)> FuncOut;//output函数
 class Log
    {
    public :
    enum LogLevel  //枚举日志级别
    {
    TRACE,
    DEBUG,
    INFO,
    };
    static Log *GetInstance() //单例模式的对象初始化
        {
		static Log m_Instance;
		return &m_Instance;
	}
    LogLevel GetLogLevel(){return level_;}; //得到日志输出级别
     void SetLogLevel(LogLevel level){level_=level;} //设置日志输出级别
     void SetOutput(const FuncOut& out){ g_output=out;}//自定义日志输出函数
     void SetFlush(const FuncFlush& flu){ g_flush=flu;};//自定义日志flush函数
     void DefaultOutput(const std::string msg)//默认的日志输出函数，输出到stdout
    {fwrite(msg.c_str(), 1,  msg.length() , stdout);}
     void DefaultFlush(){ fflush(stdout);}
     void LogInfo(const char* file,const int line,const char* fun,const std::string); //将一条日志信息输出到
   void stop(); //停止日志的输出
   void ThreadFunc();//负责写日志的线程函数
   bool finish(){ return StrQue.empty();};//判断是否可以结束写日志
    private:
    Log();//实现单例模式需要将构造函数声明为私有
     ~Log();
    std::atomic_bool running;//原子bool型数据
    LogLevel level_;//日志级别
    FuncOut g_output=std::bind(&Log::DefaultOutput,this,std::placeholders::_1);//绑定默认输出函数
    FuncFlush g_flush=std::bind(&Log::DefaultFlush,this);//绑定默认flush函数
    std::thread thread_;//负责写日志的线程
    BlockingQueue<std::string> StrQue;//用来保存日志信息的阻塞队列
    
    };
#define LogInit()  Log* A=Log::GetInstance();
#define SETLOGOUT(x) A->SetOutput(x);  
#define SETLEVEL(x)  A->SetLogLevel(x);
#define LOG_TRACE(x) {if (A->GetLogLevel() <= lion::Log::TRACE) \
 A->LogInfo(__FILE__,__LINE__,__func__,x);}
#define LOG_DEBUG(x) {if (A->GetLogLevel() <= lion::Log::DEBUG) \
 A->LogInfo(__FILE__,__LINE__,__func__,x);}
#define LOG_INFO(x) {if (A->GetLogLevel() <= lion::Log::INFO) \
 A->LogInfo(__FILE__,__LINE__,__func__,x);}
}

#endif














