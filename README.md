# 项目名称 HyperServer-Framework
## 开发环境
Ubuntu22.04
g++ 11.4.0
cmake 3.22.1

# 项目路径

bin             ---二进制文件
build           ---中间文件路径
cmake           ---cmake函数文件夹
CMakeLists.txt  ---cmake的定义文件
lib             --- 库的输出路径
Makefile
HyperServer     --- 源代码路径
tests           ---测试程序路径

# 日志系统
1）     log4J
    Logger(定义日志类别) ： 用于输出不同日志级别的消息
       |
       |---------Formatter(日志格式) ： 日志格式化器，用于指出日志按照什么格式输出
       |
    Appender (日志输出目标)  ：用于指定日志输出的目的地，如控制台、文件
