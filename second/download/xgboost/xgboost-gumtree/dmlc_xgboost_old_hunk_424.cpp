      buffer_.resize(std::min(reduce_buffer_size, n));
      // make sure align to type_nbytes
      buffer_size = buffer_.size() * sizeof(uint64_t) / type_nbytes * type_nbytes;
      utils::Assert(type_nbytes < buffer_size, "too large type_nbytes=%lu, buffer_size", type_nbytes, buffer_size);
      // set buffer head
      buffer_head = reinterpret_cast<char*>(BeginPtr(buffer_));
    }
