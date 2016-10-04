#ifndef BASE_H
#define BASE_H
#include <sys/time.h>   
 #include <unistd.h>
 #include <time.h>
namespace lion
{
  /*
noncopyable源码来源于boost库，核心思想：使基类的拷贝赋值构造函数private。
他的派生类是没有访问权限的。也就无法通过拷贝以及赋值来构造新对象。
*/
class noncopyable
  {
   protected:
      noncopyable() {}
      ~noncopyable() {}
   private:  // emphasize the following members are private
      noncopyable( const noncopyable& );
      const noncopyable& operator=( const noncopyable& );
  };
  /*Timer非线程安全
    可以返回秒数，也可以返回格式化的时间字符串
  */
  class Timer : noncopyable  
     {  
        public:
       time_t now()
       {
       gettimeofday(&now_tv, NULL); //1970年到现在的秒数
       seconds = now_tv.tv_sec;
       return seconds;
       }
       char* ToStr()
       { 
        now();
        localtime_r(&seconds, &t); //线程安全
        snprintf(TmStr, sizeof TmStr,
        "%04d-%02d-%02d-%02d:%02d:%02d",
        t.tm_year + 1900,
        t.tm_mon + 1,
        t.tm_mday,
        t.tm_hour,
        t.tm_min,
        t.tm_sec);
       // static_cast<int>(now_tv.tv_usec));
        return TmStr;
       }
       private :
       time_t seconds;
       struct timeval now_tv;
       struct tm t;
       char TmStr[1024];
     };
     class during : noncopyable  //结合shared_ptr显示程序运行时间
{ public :
  during()
  :start(Timer().now())
  {}
  ~during()
  {
   std::cout<<Timer().now()-start<<std::endl;
  }
  private :
  time_t start;
};
}
#endif
