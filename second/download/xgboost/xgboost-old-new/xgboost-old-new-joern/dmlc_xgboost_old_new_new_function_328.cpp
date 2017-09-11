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