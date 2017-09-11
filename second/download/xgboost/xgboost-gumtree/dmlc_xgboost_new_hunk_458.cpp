  virtual size_t Tell(void) = 0;
};

/*! \brief fixed size memory buffer */
struct MemoryFixSizeBuffer : public ISeekStream {
 public:
  MemoryFixSizeBuffer(void *p_buffer, size_t buffer_size) 
      : p_buffer_(reinterpret_cast<char*>(p_buffer)), buffer_size_(buffer_size) {
    curr_ptr_ = 0;
  }
  virtual ~MemoryFixSizeBuffer(void) {}
  virtual size_t Read(void *ptr, size_t size) {
    utils::Assert(curr_ptr_ <= buffer_size_,
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
    curr_ptr_ = static_cast<size_t>(pos);
  }
  virtual size_t Tell(void) {
    return curr_ptr_;
  }

 private:
  /*! \brief in memory buffer */
  char *p_buffer_;
  /*! \brief current pointer */
  size_t buffer_size_;
  /*! \brief current pointer */
  size_t curr_ptr_;
}; // class MemoryFixSizeBuffer

/*! \brief a in memory buffer that can be read and write as stream interface */
struct MemoryBufferStream : public ISeekStream {
 public:
