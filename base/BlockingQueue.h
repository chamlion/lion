#ifndef BlockingQueue_H
#define BlockingQueue_H
/*这里有借鉴 陈硕muduo库中BlockingQueue的实现
这里的条件变量 互斥量没有自己封装 而是直接采用了stl库中的实现
time 2016.9.6 21:51
author:张洲
mail: chamlionchina@gmail.com
队列为空的时候会一直阻塞的等待数据到来，不提供使得队列停止等待的接口
由用户自己实现，推荐结束等待方法，发送一个数据进去即可。
*/
#include <deque>
#include <mutex>
#include <condition_variable> 
namespace lion
{  
  template<typename T>
  class BlockingQueue //: public num::noncopyable
  {
     public:
      BlockingQueue():
      mutex_(),queue_()
      {
      }
     T take()
    {
  std::unique_lock<std::mutex> lock(mutex_);
   while (empty())
  {
    not_empty.wait(lock);
  }
   T front(queue_.front());
    queue_.pop_front();
    return front;
     }
     void  put(const T x)
   {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push_back(x);
   not_empty.notify_one();
 
   }
     size_t  size() //const
   {
      std::lock_guard<std::mutex> lock(mutex_);
      return queue_.size();
   }
     bool empty() const
    {   
        
        return queue_.empty();
     }
     private :
     std::mutex mutex_; 
     std::deque<T>     queue_;
     std::condition_variable  not_empty;

  };
}
#endif
