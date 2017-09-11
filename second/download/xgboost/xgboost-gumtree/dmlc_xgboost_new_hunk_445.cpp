      // check if we finished the job of message passing
      size_t nfinished = size_down_in;
      // can pass message down to childs
      for (int i = 0; i < nlink; ++i) {
        if (i != parent_index && selecter.CheckWrite(links[i].sock)) {
          links[i].WriteFromArray(sendrecvbuf, size_down_in);
          nfinished = std::min(links[i].size_write, nfinished);
        }
      }
      // check boundary condition
      if (nfinished >= total_size) break;
    }
  }
  /*!
   * \brief broadcast data from root to all nodes
   * \param sendrecvbuf_ buffer for both sending and recving data
   * \param type_n4bytes the unit number of bytes the type have
   * \param count number of elements to be reduced
   * \param reducer reduce function
   */  
  inline void Bcast(void *sendrecvbuf_,
                    size_t total_size,
                    int root) {
    if (links.size() == 0) return;
    // number of links
    const int nlink = static_cast<int>(links.size());
    // size of space already read from data
    size_t size_in = 0;
    // input link, -2 means unknown yet, -1 means this is root
    int in_link = -2;

    // initialize the link statistics
    for (int i = 0; i < nlink; ++i) {
      links[i].ResetSize();
    }
    // root have all the data
    if (this->rank == root) {
      size_in = total_size;
      in_link = -1;
    }
    
    // while we have not passed the messages out
    while(true) {
      selecter.Select();
      if (in_link == -2) {
        // probe in-link
        for (int i = 0; i < nlink; ++i) {
          if (selecter.CheckRead(links[i].sock)) {
            links[i].ReadToArray(sendrecvbuf_, total_size);
            size_in = links[i].size_read;
            if (size_in != 0) {
              in_link = i; break;
            }
          }
        }
      } else {
        // read from in link
        if (in_link >= 0 && selecter.CheckRead(links[in_link].sock)) {
          links[in_link].ReadToArray(sendrecvbuf_, total_size);
          size_in = links[in_link].size_read;
        }
      }
      size_t nfinished = total_size;
      // send data to all out-link
      for (int i = 0; i < nlink; ++i) {
        if (i != in_link && selecter.CheckWrite(links[i].sock)) {
          links[i].WriteFromArray(sendrecvbuf_, size_in);
          nfinished = std::min(nfinished, links[i].size_write);
        }
      }
      // check boundary condition
      if (nfinished >= total_size) break;
    }
  }
 private:  
  // 128 MB
  const static size_t kBufferSize = 128;
  // an independent child record
  struct LinkRecord {
   public:
    // socket to get data from/to link
    utils::TCPSocket sock;
    // size of data readed from link
    size_t size_read;
    // size of data sent to the link
    size_t size_write;
    // pointer to buffer head
    char *buffer_head;
    // buffer size, in bytes
    size_t buffer_size;
    // initialize buffer
    inline void InitBuffer(size_t type_nbytes, size_t count) {
      utils::Assert(type_nbytes < kBufferSize, "too large type_nbytes");
      size_t n = (type_nbytes * count + 7)/ 8;
      buffer_.resize(std::min(kBufferSize, n));
      // make sure align to type_nbytes
      buffer_size = buffer_.size() * sizeof(uint64_t) / type_nbytes * type_nbytes;
      // set buffer head
      buffer_head = reinterpret_cast<char*>(BeginPtr(buffer_));
    }
    // reset the recv and sent size
    inline void ResetSize(void) {
      size_write = size_read = 0;
    }
    /*! 
     * \brief read data into ring-buffer, with care not to existing useful override data
     *  position after protect_start
     * \param protect_start all data start from protect_start is still needed in buffer
     *                      read shall not override this 
     */
    inline void ReadToRingBuffer(size_t protect_start) {
      size_t ngap = size_read - protect_start;
      utils::Assert(ngap <= buffer_size, "AllReduce: boundary check");
      size_t offset = size_read % buffer_size;
      size_t nmax = std::min(buffer_size - ngap, buffer_size - offset);
      size_read += sock.Recv(buffer_head + offset, nmax);
    }
    /*!
     * \brief read data into array,
     * this function can not be used together with ReadToRingBuffer
     * a link can either read into the ring buffer, or existing array
     * \param max_size maximum size of array
     */
    inline void ReadToArray(void *recvbuf_, size_t max_size) {
      char *p = static_cast<char*>(recvbuf_);
      size_read += sock.Recv(p + size_read, max_size - size_read);
    }
    /*!
     * \brief write data in array to sock
     * \param sendbuf_ head of array
     * \param max_size maximum size of array
     */
    inline void WriteFromArray(const void *sendbuf_, size_t max_size) {
      const char *p = static_cast<const char*>(sendbuf_);
      size_write += sock.Send(p + size_write, max_size - size_write);
    }

   private:
