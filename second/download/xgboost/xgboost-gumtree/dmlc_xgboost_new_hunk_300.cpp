};

/*! \brief line split from normal file system */
class FileProvider : public LineSplitter::IFileProvider {
 public:
  explicit FileProvider(const char *uri) {
    LineSplitter::SplitNames(&fnames_, uri, "#");
    std::vector<size_t> fsize;
    for (size_t  i = 0; i < fnames_.size(); ++i) {
      if (!std::strncmp(fnames_[i].c_str(), "file://", 7)) {
        std::string tmp = fnames_[i].c_str() + 7;
        fnames_[i] = tmp;        
      }
      size_t fz = GetFileSize(fnames_[i].c_str());
      if (fz != 0) {
        fsize_.push_back(fz);
      }
    }
  }
  // destrucor
  virtual ~FileProvider(void) {}  
  virtual utils::ISeekStream *Open(size_t file_index) {
    utils::Assert(file_index < fnames_.size(), "file index exceed bound"); 
    return new FileStream(fnames_[file_index].c_str(), "rb");
  }
  virtual const std::vector<size_t> &FileSize(void) const {
    return fsize_;
  }
 private:
  // file sizes
  std::vector<size_t> fsize_;
  // file names
  std::vector<std::string> fnames_;
  // get file size
  inline static size_t GetFileSize(const char *fname) {
    std::FILE *fp = utils::FopenCheck(fname, "rb");
