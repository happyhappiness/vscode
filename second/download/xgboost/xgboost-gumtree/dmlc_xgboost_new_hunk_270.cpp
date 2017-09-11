    maxthread = std::max(maxthread / 2, 1);
    nthread_ = std::min(maxthread, nthread);
  }
  inline void SetParam(const char *name, const char *val) {}
  inline bool LoadNext(std::vector<LibSVMPage> *data) {
    return FillData(data);
  }
  inline void FreeSpace(std::vector<LibSVMPage> *a) {
    delete a;
  }
  inline std::vector<LibSVMPage> *Create(void) {
    return new std::vector<LibSVMPage>();
  }
  inline void BeforeFirst(void) {
    utils::Assert(at_head_, "cannot call beforefirst");
  }
  inline void Destroy(void) {
    delete source_;
  }
  inline size_t bytes_read(void) const {
    return bytes_read_;
  }

 protected:
  inline bool FillData(std::vector<LibSVMPage> *data) {
    dmlc::InputSplit::Blob chunk;
    if (!source_->NextChunk(&chunk)) return false;
    int nthread;
