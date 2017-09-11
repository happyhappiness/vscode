                        size_t type_nbytes,
                        size_t count,
                        ReduceHandle::ReduceFunction reducer) {
    if (links.size() == 0) return;
    // total size of message
    const size_t total_size = type_nbytes * count;
    // number of links
    const int nlink = static_cast<int>(links.size());
    // send recv buffer
    char *sendrecvbuf = reinterpret_cast<char*>(sendrecvbuf_);
    // size of space that we already performs reduce in up pass
    size_t size_up_reduce = 0;
    // size of space that we have already passed to parent
    size_t size_up_out = 0;
    // size of message we received, and send in the down pass
    size_t size_down_in = 0;    

    // initialize the link ring-buffer and pointer
    for (int i = 0; i < nlink; ++i) {
      if (i != parent_index) links[i].InitBuffer(type_nbytes, count);
      links[i].ResetSize();
    }
    // if no childs, no need to reduce
    if (nlink == static_cast<int>(parent_index != -1)) {
      size_up_reduce = total_size;
    }
    
    // while we have not passed the messages out
    while(true) {
      selecter.Select();
      // read data from childs
      for (int i = 0; i < nlink; ++i) {
        if (i != parent_index && selecter.CheckRead(links[i].sock)) {
          links[i].ReadToRingBuffer(size_up_out);
        }
      }
      // this node have childs, peform reduce
      if (nlink > static_cast<int>(parent_index != -1)) {
        size_t buffer_size = 0;
        // do upstream reduce
        size_t max_reduce = total_size;
        for (int i = 0; i < nlink; ++i) {
          if (i != parent_index) {
            max_reduce= std::min(max_reduce, links[i].size_read);
            utils::Assert(buffer_size == 0 || buffer_size == links[i].buffer_size,
                          "buffer size inconsistent");
            buffer_size = links[i].buffer_size;
          }
        }
        utils::Assert(buffer_size != 0, "must assign buffer_size");
        // round to type_n4bytes
        max_reduce = (max_reduce / type_nbytes * type_nbytes);
        // peform reduce, can be at most two rounds
        while (size_up_reduce < max_reduce) {
          // start position
          size_t start = size_up_reduce % buffer_size;
          // peform read till end of buffer
          size_t nread = std::min(buffer_size - start, max_reduce - size_up_reduce);          
          utils::Assert(nread % type_nbytes == 0, "AllReduce: size check");
          for (int i = 0; i < nlink; ++i) {
            if (i != parent_index) {
              reducer(links[i].buffer_head + start,
                      sendrecvbuf + size_up_reduce,
                      nread / type_nbytes,
                      MPI::Datatype(type_nbytes));
            }
          }
          size_up_reduce += nread;
        }
      }
      if (parent_index != -1) {
        // pass message up to parent, can pass data that are already been reduced
        if (selecter.CheckWrite(links[parent_index].sock)) {
          size_up_out += links[parent_index].sock.
              Send(sendrecvbuf + size_up_out, size_up_reduce - size_up_out);
        }
        // read data from parent
        if (selecter.CheckRead(links[parent_index].sock)) {
          size_down_in +=  links[parent_index].sock.
              Recv(sendrecvbuf + size_down_in, total_size - size_down_in);
          utils::Assert(size_down_in <= size_up_out, "AllReduce: boundary error");
        }
      } else {
