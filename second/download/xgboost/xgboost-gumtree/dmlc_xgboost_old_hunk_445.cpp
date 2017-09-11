      // check if we finished the job of message passing
      size_t nfinished = size_down_in;
      // can pass message down to childs
      for (size_t i = 0; i < childs.size(); ++i) {
        if (selecter.CheckWrite(childs[i].sock)) {
          childs[i].size_write += childs[i].sock
              .Send(sendrecvbuf + childs[i].size_write, size_down_in - childs[i].size_write);
        }
        nfinished = std::min(childs[i].size_write, nfinished);
      }
      // check boundary condition
      if (nfinished >= total_size) {
        utils::Assert(nfinished == total_size, "AllReduce: nfinished check");
        break;
      }
    }
  }
  inline void Bcast(std::string *sendrecv_data, int root) {
    if (parent.size() == 0 && childs.size() == 0) return;
    // message send to parent
    size_t size_up_out = 0;
    // all messages received
    size_t size_in = 0;
    // all headers received so far
    size_t header_in = 0;
    // total size of data
    size_t total_size;
    // input channel, -1 means parent, -2 means unknown yet
    // otherwise its child index
    int in_channel = -2;
    // root already reads all data in
    if (root == rank) {
      in_channel = -3;
      total_size = size_in = sendrecv_data->length();
      header_in = sizeof(total_size);
    }
    // initialize write position
    for (size_t i = 0; i < childs.size(); ++i) {
      childs[i].size_write = 0;
    }
    const int nchilds = static_cast<int>(childs.size());

    while (true) {
      selecter.Select();
      if (selecter.CheckRead(parent[0])) {
        utils::Assert(in_channel == -2 || in_channel == -1, "invalid in channel");
        this->BcastRecvData(parent[0], sendrecv_data,
                            header_in, size_in, total_size);
        if (header_in != 0) in_channel = -1;
      }
      for (int i = 0; i < nchilds; ++i) {
        if (selecter.CheckRead(childs[i].sock)) {
          utils::Assert(in_channel == -2 || in_channel == i, "invalid in channel");
          this->BcastRecvData(parent[0], sendrecv_data,
                              header_in, size_in, total_size);
          if (header_in != 0) in_channel = i;
        }
      }
      if (in_channel == -2) continue;
      if (in_channel != -1) {
        if (selecter.CheckWrite(parent[0])) {
          size_t nsend = size_in - size_up_out;
          if (nsend != 0) {
            size_up_out += parent[0].Send(&(*sendrecv_data)[0] + size_up_out, nsend);
          }
        }
      } else {
        size_up_out = size_in;
      }
      size_t nfinished = size_up_out;
      for (int i = 0; i < nchilds; ++i) {
        if (in_channel != i) {
          if (selecter.CheckWrite(childs[i].sock)) {
            size_t nsend = size_in - childs[i].size_write;
            if (nsend != 0) {
              childs[i].size_write += childs[i].sock
                  .Send(&(*sendrecv_data)[0] + childs[i].size_write, nsend);
            }
          }
          nfinished = std::min(nfinished, childs[i].size_write);
        }
      }
      // check boundary condition
      if (nfinished >= total_size) {
        utils::Assert(nfinished == total_size, "Bcast: nfinished check");
        break;
      }
    }
  }

 private:
  inline void BcastRecvData(utils::TCPSocket &sock,
                            std::string *sendrecv_data,   
                            size_t &header_in,
                            size_t &size_in,
                            size_t &total_size) {
    if (header_in < sizeof(total_size)) {
      char *p = reinterpret_cast<char*>(&total_size);
      header_in += sock.Recv(p + size_in, sizeof(total_size) - header_in);
      if (header_in == sizeof(total_size)) {
        sendrecv_data->resize(total_size);
      }
    } else {
      size_t nread  = total_size - size_in;
      if (nread != 0) {
        size_in += sock
            .Recv(&(*sendrecv_data)[0] + size_in, nread);
      }
    }
  }
  
  // 128 MB
  const static size_t kBufferSize = 128;
  // an independent child record
  struct ChildRecord {
   public:
    // socket to get data from child
    utils::TCPSocket sock;
    // size of data readed from child
    size_t size_read;
    // size of data write into child
    size_t size_write;
    // pointer to buffer head
    char *buffer_head;
    // buffer size, in bytes
    size_t buffer_size;
    // initialize buffer
    inline void Init(size_t type_nbytes, size_t count) {
      utils::Assert(type_nbytes < kBufferSize, "too large type_nbytes");
      size_t n = (type_nbytes * count + 7)/ 8;
      buffer_.resize(std::min(kBufferSize, n));
      // make sure align to type_nbytes
      buffer_size = buffer_.size() * sizeof(uint64_t) / type_nbytes * type_nbytes;
      // set buffer head
      buffer_head = reinterpret_cast<char*>(BeginPtr(buffer_));
      // set write head
      size_write = size_read = 0;
    }
    // maximum number of bytes we are able to read
    // currently without corrupt the data
    inline void Read(size_t size_up_out) {
      size_t ngap = size_read - size_up_out;
      utils::Assert(ngap <= buffer_size, "AllReduce: boundary check");
      size_t offset = size_read % buffer_size;      
      size_t nmax = std::min(ngap, buffer_size - offset);
      size_t len = sock.Recv(buffer_head + offset, nmax);
      size_read += len;
    }

   private:
