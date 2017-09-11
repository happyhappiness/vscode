  virtual void Write(const void *ptr, size_t size) {
    utils::Error("cannot do write in inputsplit");
  }
  virtual void BeforeFirst(void) {
    std::fseek(fp_, 0, SEEK_SET);
  }
  virtual bool NextRecord(Blob *out_rec) {
    if (chunk_begin_ == chunk_end_) {
      if (!LoadChunk()) return false;
