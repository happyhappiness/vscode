    maxthread = std::max(maxthread / 2, 1);
    nthread_ = std::min(maxthread, nthread);
  }
  virtual ~LibSVMParser() {
    delete source_;
  }
  virtual void BeforeFirst(void) {
    utils::Assert(at_head_, "cannot call BeforeFirst");
  }
  virtual const LibSVMPage &Value(void) const {
    return data_[data_ptr_ - 1];
  }
  virtual bool Next(void) {
    while (true) {
      while (data_ptr_ < data_end_) {
        data_ptr_ += 1;
        if (data_[data_ptr_ - 1].Size() != 0) {
          return true;
        }
      }
      if (!FillData()) break;
      data_ptr_ = 0; data_end_ = data_.size();
    }
    return false;
  }
  inline size_t bytes_read(void) const {
    return bytes_read_;
  }

 protected:
  inline bool FillData() {
    dmlc::InputSplit::Blob chunk;
    if (!source_->NextChunk(&chunk)) return false;
    int nthread;
