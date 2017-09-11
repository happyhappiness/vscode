                        size_t type_nbytes,
                        size_t count,
                        ReduceHandle::ReduceFunction reducer) {
    if (parent.size() == 0 && childs.size() == 0) return;
    char *sendrecvbuf = reinterpret_cast<char*>(sendrecvbuf_);
    // total size of message
    const size_t total_size = type_nbytes * count;
    // size of space that we already performs reduce in up pass
    size_t size_up_reduce = 0;
    // size of space that we have already passed to parent
    size_t size_up_out = 0;
    // size of message we received, and send in the down pass
    size_t size_down_in = 0;
    // initialize the send buffer
    for (size_t i = 0; i < childs.size(); ++i) {
      childs[i].Init(type_nbytes, count);
    }
    // if no childs, no need to reduce
    if (childs.size() == 0) size_up_reduce = total_size;    
    // while we have not passed the messages out
    while(true) {
      selecter.Select();
      // read data from childs
      for (size_t i = 0; i < childs.size(); ++i) {
        if (selecter.CheckRead(childs[i].sock)) {
          childs[i].Read(size_up_out);
        }
      }
      // peform reduce
      if (childs.size() != 0) {
        const size_t buffer_size = childs[0].buffer_size;
        // do upstream reduce
        size_t min_read = childs[0].size_read;
        for (size_t i = 1; i < childs.size(); ++i) {
          min_read = std::min(min_read, childs[i].size_read);
        }
        // align to type_nbytes
        min_read = (min_read / type_nbytes * type_nbytes);
        // start position
        size_t start = size_up_reduce % buffer_size;
        // peform read till end of buffer
        if (start + min_read - size_up_reduce > buffer_size) {
          const size_t nread = buffer_size - start;
          utils::Assert(nread % type_nbytes == 0, "AllReduce: size check");
          for (size_t i = 0; i < childs.size(); ++i) {
            reducer(childs[i].buffer_head + start,
                    sendrecvbuf + size_up_reduce,
                    nread / type_nbytes,
                    MPI::Datatype(type_nbytes));
          }
          size_up_reduce += nread;
          start = 0;
        }
        // peform second phase of reduce
        const size_t nread = min_read - size_up_reduce;
        if (nread != 0) {
          utils::Assert(nread % type_nbytes == 0, "AllReduce: size check");
          for (size_t i = 0; i < childs.size(); ++i) {
            reducer(childs[i].buffer_head + start,
                    sendrecvbuf + size_up_reduce,
                    nread / type_nbytes,
                    MPI::Datatype(type_nbytes));
          }
        }
        size_up_reduce += nread;
      }
      if (parent.size() != 0) {
        // can pass message up to parent
        if (selecter.CheckWrite(parent[0])) {
          size_up_out += parent[0]
              .Send(sendrecvbuf + size_up_out, size_up_reduce - size_up_out);
        }
        // read data from parent
        if (selecter.CheckRead(parent[0])) {
          size_down_in +=  parent[0]
              .Recv(sendrecvbuf + size_down_in, total_size - size_down_in);
          utils::Assert(size_down_in <= size_up_out, "AllReduce: boundary error");
        }
      } else {
