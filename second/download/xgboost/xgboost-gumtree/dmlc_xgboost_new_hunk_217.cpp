  }
  virtual size_t Read(void *ptr, size_t size) {
    return std::fread(ptr, 1, size, fp_);
  }
  virtual void Write(const void *ptr, size_t size) {
    utils::Error("cannot do write in inputsplit");
  }
