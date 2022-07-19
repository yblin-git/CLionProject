#ifndef COMMON_DATA_IO_FILE_H_
#define COMMON_DATA_IO_FILE_H_

#include <string>
#include <sys/stat.h>
#include <memory>
#include <fstream>
#include <sstream>
#include <list>

namespace common_data {

    using std::string;
    using std::shared_ptr;
    using std::list;

    class File;
    typedef shared_ptr<File> FilePtr;

    class File {

    public:
        static const char kSeparator = '/';

        File();

        explicit File(const string& path);

        File(const File& parent, const string& name);

        File(const string& parent, const string& name);

        /**
         *  以当前路径创建文件
         */
        bool CreateFile();


        inline bool CreateFile(std::ofstream* fous, bool reuse = false) {
            return CreateFile(fous, std::ios::out, reuse);
        }

        /**
         *  使用给定的输出流以当前路径创建文件
         *  创建成功后输出流为打开状态
         */
        bool CreateFile(std::ofstream* fous,
                        const std::ios::openmode& mode,
                        bool reuse = false);

        /**
         *  用当前路径创建文件并且自动补全其缺少的父目录
         */
        bool CreateFileAndDirectories();

        /**
         *  用当前路径创建文件并且自动补全其缺少的父目录
         */
        bool CreateFileAndDirectories(std::ofstream* fous);

        /**
         *  用当前路径创建目录
         */
        bool CreateDirectory();

        /**
         *  用当前路径创建目录并且自动补全其缺少的父目录
         */
        bool CreateDirectories();

        /**
         *  重命名文件
         */
        bool Rename(const string& name);

        /**
         *  重命名文件
         */
        bool Move(const string& path);

        /**
         *  删除当前文件
         */
        bool Delete(bool recursion = false);

        bool Chmod(__mode_t mode);

        bool CanRead() const;

        bool CanWrite() const;

        bool IsDirectory() const;

        bool IsFile() const;

        int64_t Size(bool recursion = false) const;

        string GetAbsolutePath() const;

        string GetFileName() const;

        FilePtr GetParentFile() const;

        list<FilePtr> GetChildFiles() const;

        /**
         *  返回最后一次访问文件的时间 (seconds from 1970)
         */
        long GetLastAccessTime() const;

        /**
         *  返回最后一次修改文件的时间 (seconds from 1970)
         */
        long GetLastModificationTime() const;

        /**
         *  返回最后一次文件状态改变的时间 (seconds from 1970)
         */
        long GetLastStatusChangeTime() const;
        /**
         *  刷新
         */
        void Refresh();
        /**
         *  返回路径
         */
        inline const string& GetPath() const { return path_; }

        inline bool Exists() const {
            return exists_;
        }

        static inline bool Exists(const string& path) {
            file_stat st;
            return stat(PurifyPath(path).c_str(), &st) == 0;
        }

        string error_str() const {
            if (error_ss_ == nullptr) {
                return "";
            }
            return error_ss_->str();
        }

        static string PurifyPath(const string& path);

    private:
        typedef struct stat file_stat;

        void CheckStat();

        std::stringstream& error_stream() const {
            if (error_ss_ == nullptr) {
                error_ss_ = std::make_shared<std::stringstream>();
            } else {
                error_ss_->str("");
            }
            return *error_ss_;
        }

        static string GetParentPath(const string& path);

        string path_;
        file_stat st_;
        bool exists_;
        mutable std::shared_ptr<std::stringstream> error_ss_;
    };

}

#endif
