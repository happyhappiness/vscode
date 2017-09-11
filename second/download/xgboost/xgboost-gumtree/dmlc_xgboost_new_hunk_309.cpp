     * \brief read data into ring-buffer, with care not to existing useful override data
     *  position after protect_start
     * \param protect_start all data start from protect_start is still needed in buffer
     *                      read shall not override this
     * \param max_size_read maximum logical amount we can read, size_read cannot exceed this value
     * \return the type of reading
     */
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
