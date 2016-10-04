# lion
 ``` c++
  看了一些网络库的源码(muduo,handy)，打算自己实现一个简洁的基于reactor模式的网络库
	author  chamlion 
	mail    chamlionchina@gmail.com
	2016.10.03
文件结构 ：(已经实现的部分)
|
|-----build.sh 
|-----CmakeLists.txt
|-----README.md
|-----base
|      |-----CmakeLists.txt
|      |-----BlockingQueue.h            实现无锁队列模板类
|      |-----log.(cc,h)                 实现单例模式的异步日志类，可自定义日志输出位置，日志输出级别 
|------test                               测试文件
|      |-----CmakeLists.txt
|      |-----log_test.cc                   

开发环境 ：
系统           ubuntu 15.04
编译器         g++ 5.2.1
调试器         gdb  7.10
编译方法       在build.sh 目录下 执行 sudo ./build.sh  则会生成相应的静态库 及测试文件	
``` 
	


 
