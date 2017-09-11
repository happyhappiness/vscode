  }
  virtual ~MemoryFixSizeBuffer(void) {}
  virtual size_t Read(void *ptr, size_t size) {
    utils::Assert(curr_ptr_ <= buffer_size_,
                  "read can not have position excceed buffer length");
    size_t nread = std::min(buffer_size_ - curr_ptr_, size);
    if (nread != 0) memcpy(ptr, p_buffer_ + curr_ptr_, nread);
