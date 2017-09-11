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