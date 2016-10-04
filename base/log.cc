#include "log.h"
#include <string.h>
namespace lion
{ 
  std::string  FileName(const char* filename) //得到文件名称，不包含路径名
    { const char *data_=filename;
      const char* slash = strrchr(filename, '/');
      if (slash)
      {
        data_ = slash + 1;
      }
      return data_;
    }
  Log::Log()
  :level_(DEBUG),
  LastRollTime(Timer().now()),
  RollInterval(3600),
  running(true),
  thread_(std::bind(&Log::ThreadFunc, this))
  {
    ChangeFile();
  }
  Log::~Log()
  {  
   while(!finish());
   stop();
   g_flush();
   if(g_file!=NULL)
   fclose(g_file);
  }

  void Log::stop()
  { 
    running= false; 
    LogInfo(__FILE__,__LINE__,__func__,"Log stop");
    //当队列无数据可读的时候，线程就会阻塞在take()函数处
    //因此发送一条信息，才能使得线程读到running的变化
    thread_.join();
  }
  void Log::ThreadFunc()
  {
   while(running) 
  {
   std::string str=StrQue.take();
   //std::cout<<str<<std::endl;
   g_output(str);
  }
  }
    void Log::LogInfo(const char* file,const int line,const char* fun,const std::string msg)
  { 
   char str[1024];
   
   snprintf(str, 1024, "%s-%s-%d-%s-%d-%s\n", Timer().ToStr(),FileName(file).c_str(), line,fun, std::this_thread::get_id(),msg.c_str());
  // std::cout<<str<<std::endl;
 StrQue.put(static_cast<std::string>(str));
  }
  void Log::Out2File(const std::string msg)
{ if ((Timer().now()-LastRollTime)>=RollInterval)
  {   LastRollTime=Timer().now();
      ChangeFile();
      
  }
 
  fwrite(msg.c_str(), 1,  msg.length() ,g_file);
}
void Log::ChangeFile()
{     if(g_file!=NULL)
      fclose(g_file);
      char str[1024]={"log"};
      strcat(strcat(str,Timer().ToStr()),".log");
      g_file = fopen(str, "w");
}
}

















