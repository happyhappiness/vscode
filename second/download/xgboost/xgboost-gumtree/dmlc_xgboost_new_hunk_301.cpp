    }
  }  
  
  inline static std::string GetNameNode(void) {
    const char *nn = getenv("rabit_hdfs_namenode");
    if (nn == NULL) {
      return std::string("default");
    } else {
      return std::string(nn);
    }
  }
 private:
  hdfsFS fs_;
  hdfsFile fp_;
  bool at_end_;
  bool disconnect_when_done_;
};

/*! \brief line split from normal file system */
class HDFSProvider : public LineSplitter::IFileProvider {
 public:
  explicit HDFSProvider(const char *uri) {
    fs_ = hdfsConnect(HDFSStream::GetNameNode().c_str(), 0);
    utils::Check(fs_ != NULL, "error when connecting to default HDFS");
    std::vector<std::string> paths;
    LineSplitter::SplitNames(&paths, uri, "#");
    // get the files
    for (size_t  i = 0; i < paths.size(); ++i) {
      hdfsFileInfo *info = hdfsGetPathInfo(fs_, paths[i].c_str());
      utils::Check(info != NULL, "path %s do not exist", paths[i].c_str());
      if (info->mKind == 'D') {
        int nentry;
        hdfsFileInfo *files = hdfsListDirectory(fs_, info->mName, &nentry);
        utils::Check(files != NULL, "error when ListDirectory %s", info->mName);
        for (int i = 0; i < nentry; ++i) {
          if (files[i].mKind == 'F' && files[i].mSize != 0) {
            fsize_.push_back(files[i].mSize);            
            fnames_.push_back(std::string(files[i].mName));
          }
        }
        hdfsFreeFileInfo(files, nentry);
      } else {
        if (info->mSize != 0) {
          fsize_.push_back(info->mSize);
          fnames_.push_back(std::string(info->mName));
        }
      }
      hdfsFreeFileInfo(info, 1);
    }
  }
  virtual ~HDFSProvider(void) {
    utils::Check(hdfsDisconnect(fs_) == 0, "hdfsDisconnect error");
  }  
  virtual const std::vector<size_t> &FileSize(void) const {
    return fsize_;
  }
  virtual ISeekStream *Open(size_t file_index) {
    utils::Assert(file_index < fnames_.size(), "file index exceed bound"); 
    return new HDFSStream(fs_, fnames_[file_index].c_str(), "r", false);
  }
  
 private:
  // hdfs handle
  hdfsFS fs_;
  // file sizes
  std::vector<size_t> fsize_;
  // file names
  std::vector<std::string> fnames_;
};
