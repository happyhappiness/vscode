inline ReturnType ReadToRingBuffer(size_t protect_start, size_t max_size_read) {
      utils::Assert(buffer_head != NULL, "ReadToRingBuffer: buffer not allocated");
      utils::Assert(size_read <= max_size_read, "ReadToRingBuffer: max_size_read check");
      size_t ngap = size_read - protect_start;
      utils::Assert(ngap <= buffer_size, "Allreduce: boundary check");
      size_t offset = size_read % buffer_size;
      size_t nmax = max_size_read - size_read;
      nmax = std::min(nmax, buffer_size - ngap);
      nmax = std::min(nmax, buffer_size - offset);
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