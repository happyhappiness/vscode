};

/*! \brief line split from normal file system */
class FileSplit : public LineSplitBase {
 public:
  explicit FileSplit(const char *uri, unsigned rank, unsigned nsplit) {
    LineSplitBase::SplitNames(&fnames_, uri, "#");
    std::vector<size_t> fsize;
    for (size_t  i = 0; i < fnames_.size(); ++i) {
      if (!std::strncmp(fnames_[i].c_str(), "file://", 7)) {
        std::string tmp = fnames_[i].c_str() + 7;
        fnames_[i] = tmp;        
      }
      fsize.push_back(GetFileSize(fnames_[i].c_str()));
    }
    LineSplitBase::Init(fsize, rank, nsplit);
  }
  virtual ~FileSplit(void) {}
  
 protected:
  virtual utils::ISeekStream *GetFile(size_t file_index) {
    utils::Assert(file_index < fnames_.size(), "file index exceed bound"); 
    return new FileStream(fnames_[file_index].c_str(), "rb");
  }
  // get file size
  inline static size_t GetFileSize(const char *fname) {
    std::FILE *fp = utils::FopenCheck(fname, "rb");
