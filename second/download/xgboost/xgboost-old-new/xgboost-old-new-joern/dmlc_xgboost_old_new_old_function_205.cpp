virtual void Write(const void *ptr, size_t size) {
    if (size == 0) return;
    utils::Assert(curr_ptr_ + size <=  buffer_size_, 
                  "write position exceed fixed buffer size");
    std::memcpy(p_buffer_ + curr_ptr_, ptr, size);
    curr_ptr_ += size;
  }