    utils::Assert(curr_ptr_ + size <= buffer_size_,
                  "read can not have position excceed buffer length");
    size_t nread = std::min(buffer_size_ - curr_ptr_, size);
    if (nread != 0) memcpy(ptr, p_buffer_ + curr_ptr_, nread);
    curr_ptr_ += nread;
    return nread;
  }
  virtual void Write(const void *ptr, size_t size) {
    if (size == 0) return;
    utils::Assert(curr_ptr_ + size <=  buffer_size_, 
                  "write position exceed fixed buffer size");
    memcpy(p_buffer_ + curr_ptr_, ptr, size);
    curr_ptr_ += size;
  }
  virtual void Seek(size_t pos) {
