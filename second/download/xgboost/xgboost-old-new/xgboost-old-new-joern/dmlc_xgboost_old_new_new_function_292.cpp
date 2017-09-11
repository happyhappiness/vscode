inline void InitBuffer(size_t type_nbytes, size_t count, size_t reduce_buffer_size) {
      utils::Assert(type_nbytes < reduce_buffer_size, "too large type_nbytes");
      size_t n = (type_nbytes * count + 7)/ 8;
      buffer_.resize(std::min(reduce_buffer_size, n));
      // make sure align to type_nbytes
      buffer_size = buffer_.size() * sizeof(uint64_t) / type_nbytes * type_nbytes;
      // set buffer head
      buffer_head = reinterpret_cast<char*>(BeginPtr(buffer_));
    }