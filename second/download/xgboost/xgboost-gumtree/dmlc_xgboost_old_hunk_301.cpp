    }
  }  
  
 private:
  hdfsFS fs_;
  hdfsFile fp_;
  bool at_end_;
};

/*! \brief line split from normal file system */
class HDFSSplit : public LineSplitBase {
 public:
  explicit HDFSSplit(const char *uri, unsigned rank, unsigned nsplit) {
    fs_ = hdfsConnect("default", 0);
    std::vector<std::string> paths;
    LineSplitBase::SplitNames(&paths, uri, "#");
    // get the files
    std::vector<size_t> fsize;
    for (size_t  i = 0; i < paths.size(); ++i) {
      hdfsFileInfo *info = hdfsGetPathInfo(fs_, paths[i].c_str());
      if (info->mKind == 'D') {
        int nentry;
        hdfsFileInfo *files = hdfsListDirectory(fs_, info->mName, &nentry);
        for (int i = 0; i < nentry; ++i) {
          if (files[i].mKind == 'F') {
            fsize.push_back(files[i].mSize);
            fnames_.push_back(std::string(files[i].mName));
          }
        }
        hdfsFreeFileInfo(files, nentry);
      } else {
        fsize.push_back(info->mSize);
        fnames_.push_back(std::string(info->mName));
      }
      hdfsFreeFileInfo(info, 1);
    }
    LineSplitBase::Init(fsize, rank, nsplit);
  }
  virtual ~HDFSSplit(void) {}
  
 protected:
  virtual utils::ISeekStream *GetFile(size_t file_index) {
    utils::Assert(file_index < fnames_.size(), "file index exceed bound"); 
    return new HDFSStream(fs_, fnames_[file_index].c_str(), "r");
  }

 private:
  // hdfs handle
  hdfsFS fs_;
  // file names
  std::vector<std::string> fnames_;
};
