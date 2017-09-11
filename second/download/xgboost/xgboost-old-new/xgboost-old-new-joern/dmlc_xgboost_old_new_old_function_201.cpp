inline ReturnType ReadToRingBuffer(size_t protect_start) {
      utils::Assert(buffer_head != NULL, "ReadToRingBuffer: buffer not allocated");
      size_t ngap = size_read - protect_start;
      utils::Assert(ngap <= buffer_size, "Allreduce: boundary check");
      size_t offset = size_read % buffer_size;
      size_t nmax = std::min(buffer_size - ngap, buffer_size - offset);
      if (nmax == 0) return kSuccess;
      ssize_t len = sock.Recv(buffer_head + offset, nmax);
      // length equals 0, remote disconnected
      if (len == 0) {
        sock.Close(); return kRecvZeroLen;
      }
      if (len == -1) return Errno2Return(errno);
      size_read += static_cast<size_t>(len);
      return kSuccess;
    }