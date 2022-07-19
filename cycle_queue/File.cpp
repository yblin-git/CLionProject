//
// Created by yblin on 2021/6/17.
//

#include "File.h"
#include <cstdio>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <cstring>

namespace common_data {

    const int kPathMax = 255;
    const char* kCurrentFile = ".";
    const char* kParentFile = "..";
    constexpr __mode_t kMode777 = S_IRWXU | S_IRWXG | S_IRWXO;

    File::File() : exists_(false) {
        memset(&st_, 0, sizeof(file_stat));
    }

    File::File(const string& path) : path_(path), exists_(false) {
        path_ = PurifyPath(path);
        CheckStat();
    }

    File::File(const File& parent, const string& name)
            : File(parent.GetPath() + kSeparator + name) {}

    File::File(const string& parent, const string& name)
            : File(PurifyPath(parent) + kSeparator + name) {}

    bool File::CreateFile() {
        std::ofstream fous;
        if(CreateFile(&fous)) {
            fous.close();
            return true;
        }
        return false;
    }

    bool File::CreateFile(std::ofstream* fous,
                          const std::ios::openmode& mode,
                          bool reuse) {
        if (!Exists() || reuse) {
            fous->open(path_, mode);
            if (fous->fail()) {
                error_stream() << "CreateFile Error: " << fous->rdstate()
                               << " "<< strerror(errno) << " path: " << path_;
                return false;
            }
            CheckStat();
            return true;
        }
        error_stream() << "CreateFile Error: Already exists > " << path_;
        return false;
    }

    bool File::CreateFileAndDirectories() {
        // 检查父目录是否存在
        std::ofstream fous;
        if(CreateFileAndDirectories(&fous)) {
            fous.close();
            return true;
        }
        return false;
    }

    bool File::CreateFileAndDirectories(std::ofstream* fous) {
        FilePtr parent = GetParentFile();
        if (parent != nullptr && !parent->Exists() &&
            !parent->CreateDirectories()) {
            return false;
        }
        return CreateFile(fous);
    }

    bool File::CreateDirectory() {
        if (Exists()) {
            if (!IsDirectory()) {
                error_stream() << "CreateDirectory Error: Already exists but not a dir "
                               << path_;
            } else {
                return true;
            }
        }
        if (mkdir(path_.c_str(), kMode777) == 0) {
            // 由于mask的存在，这里需要强行用chmod给予权限
            return Chmod(kMode777);
        }
        error_stream() << "CreateDirectory Error: " << strerror(errno)
                       << " path: " << path_;
        return false;
    }

    bool File::CreateDirectories() {
        if (Exists()) {
            if (!IsDirectory()) {
                error_stream() << "CreateDirectories Error: Already exists but not a dir "
                               << path_;
            } else {
                return true;
            }
        }
        FilePtr file = GetParentFile();
        if (file == nullptr || file->IsDirectory() || file->CreateDirectories()) {
            return CreateDirectory();
        }
        return false;
    }

/**
 *  重命名文件
 */
    bool File::Rename(const string& name) {
        return Move(GetParentPath(path_) + kSeparator + name);
    }

/**
 *  重命名文件
 */
    bool File::Move(const string& path) {
        File file(path);
        if (file.Exists()) {
            error_stream() << "Move Failed: Already exist";
            return false;
        }
        if (rename(path_.c_str(), path.c_str()) == 0) {
            path_ = path;
            CheckStat();
            return true;
        }
        error_stream() << "Move File Error: " << strerror(errno)
                       << " old: " << path_ << " new: " << path;
        return false;
    }

    bool File::Delete(bool recursion) {
        if (!Exists()) {
            error_stream() << "Delete File Error: file is not exist" << " " << path_;
            return false;
        }
        if (IsDirectory()) {
            auto childs = GetChildFiles();
            if (!childs.empty()) {
                if (recursion) {
                    for (auto child : childs) {
                        child->Delete(true);
                    }
                } else {
                    error_stream() << "Delete File Error: file is a dir and not empty, "
                                      "please use Delete(true) " << path_;
                    return false;
                }
            }
        }
        if (remove(path_.c_str()) == 0) {
            CheckStat();
        } else {
            error_stream() << "Delete File Error: " << strerror(errno)
                           << " " << path_;
            return false;
        }
        return true;
    }

    bool File::Chmod(__mode_t mode) {
        int result = chmod(path_.c_str(), mode);
        if (result != 0) {
            error_stream() << "Chmod failed: " << result << " " << strerror(result);
            return false;
        }
        CheckStat();
        return true;
    }

    bool File::CanRead() const {
        return access(path_.c_str(), R_OK) == 0;
    }

    bool File::CanWrite() const {
        return access(path_.c_str(), W_OK) == 0;
    }

    bool File::IsDirectory() const {
        return st_.st_mode & S_IFDIR;
    }

    bool File::IsFile() const {
        return st_.st_mode & S_IFREG;
    }

    int64_t File::Size(bool recursion) const {
        if (recursion && IsDirectory()) {
            int64_t total_size = 0;
            for (auto child : GetChildFiles()) {
                total_size += child->Size(true);
            }
            return total_size;
        } else {
            return st_.st_size;
        }
    }

    string File::GetAbsolutePath() const {
        char abs_path[PATH_MAX];
        if (realpath(path_.c_str(), abs_path) != nullptr) {
            return string(abs_path);
        }
        return string();
    }

    string File::GetFileName() const {
        size_t sep_pos = path_.find_last_of(kSeparator);
        if (sep_pos == std::string::npos) {
            return path_;
        }
        return path_.substr(sep_pos + 1, path_.size());
    }

    FilePtr File::GetParentFile() const {
        string path = GetAbsolutePath();
        if (path.empty()) {
            path = path_;
        }
        string parent_path = GetParentPath(path);
        if (parent_path.empty()) {
            return nullptr;
        }
        return std::make_shared<File>(parent_path);
    }

    list<FilePtr> File::GetChildFiles() const {
        list<FilePtr> childs;
        if (!IsDirectory()) {
            error_stream() << "GetChildFileNames Error : not a dir";
            return childs;
        }
        DIR* dir = opendir(GetPath().c_str());
        if (dir == nullptr) {
            error_stream() << "GetChildFileNames Error : opendir failed";
            return childs;
        }
        struct dirent* child = nullptr;
        while(true) {
            child = readdir(dir);
            if (child == nullptr) {
                break;
            }
            if (strcmp(child->d_name, kCurrentFile) == 0 ||
                strcmp(child->d_name, kParentFile) == 0) {
                continue;
            }
            childs.emplace_back(std::make_shared<File>(*this, string(child->d_name)));
        }
        closedir(dir);
        return childs;
    }

    long File::GetLastAccessTime() const {
        return st_.st_atime;
    }

    long File::GetLastModificationTime() const {
        return st_.st_mtime;
    }

    long File::GetLastStatusChangeTime() const {
        return st_.st_ctime;
    }

    void File::Refresh() { CheckStat(); }

    string File::PurifyPath(const string& path) {
        if (path[path.size() - 1] == kSeparator) {
            return path.substr(0, path.size() - 1);
        }
        return path;
    }

    void File::CheckStat() {
        memset(&st_, 0, sizeof(file_stat));
        int result = stat(path_.c_str(), &st_);
        if(result == 0) {
            exists_ = true;
        } else {
            exists_ = false;
            if (errno != ENOENT) {
                error_stream() << "File Error: " << errno;
            }
        }
    }

    string File::GetParentPath(const string& path) {
        size_t sep_pos = path.find_last_of(kSeparator);
        if (sep_pos == string::npos) {
            return string();
        }
        return path.substr(0, sep_pos);
    }

}
