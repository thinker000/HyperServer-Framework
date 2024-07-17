#ifndef __HyperServer_LOG_H_
#define __HyperServer_LOG_H_

#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>

namespace HyperServer
{
    // 日志事件
    class LogEvent
    {
    public:
        using ptr = std::shared_ptr<LogEvent>;
        //typedef std::shared_ptr<LogEvent> ptr;
        LogEvent();
    private:
        const char* m_file = nullptr;   //文件名
        int32_t m_line;                 //行号
        uint32_t m_threadId;            //线程id
        uint32_t m_fiberId;             //协程id
        uint32_t m_elapse;              //程序启动开始到当前的毫秒数
        uint64_t m_time;                //时间戳
        std::string m_content;    
    };

    // 日志级别
    class LogLevel{
    public:
        enum Level{
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };
    };

    // 日志格式
    class LogFormatter
    {
        public:
            using ptr = std::shared_ptr<LogFormatter>;
            std::string format(LogEvent::ptr event);
        private:
    };

    // 日志输出目标
    class LogAppender
    {
        public:
            using ptr = std::shared_ptr<LogAppender>;
            virtual ~LogAppender(){}
            virtual void log(LogLevel::Level level,LogEvent::ptr event)=0;
            void setFormatter(LogFormatter::ptr val);
            LogFormatter::ptr getFormatt() const;
        protected:
            LogLevel::Level m_level; 
            LogFormatter::ptr m_formatter;
    };

    //日志器
    class Logger
    {
        public:
            using ptr = std::shared_ptr<Logger>;
            Logger(const std::string& name = "root");
            void log(LogLevel::Level level,LogEvent::ptr event);

            void debug(LogEvent::ptr event);
            void info(LogEvent::ptr event);
            void warn(LogEvent::ptr event);
            void error(LogEvent::ptr event);
            void fatal(LogEvent::ptr event);

            void addAppender(LogAppender::ptr appender);
            void delAppender(LogAppender::ptr appender);

            LogLevel::Level getLevel() const;
            void setLevel(LogLevel::Level val);

        
        private:
            std::string m_anme;         //日志名称
            LogLevel::Level m_level;    //日志级别
            std::list<LogAppender::ptr> m_appender;//Appender集合
    };



    //输出到控制台的Appender
    class StdoutLogAppender:public LogAppender{
        public:
            using ptr = std::shared_ptr<StdoutLogAppender>;
            virtual void log(LogLevel::Level level,LogEvent::ptr event) override;

        private:
    };

    //输出到文件的Appender
    class FileLogAppender:public LogAppender{
        public:
            using ptr = std::shared_ptr<FileLogAppender>;
            FileLogAppender(const std::string& fileName);
            virtual void log(LogLevel::Level level,LogEvent::ptr event) override;
            bool reOpen();  //重新打开文件
        private:
        std::string m_fileName;
        std::ofstream m_fileStream;
    };


}

#endif