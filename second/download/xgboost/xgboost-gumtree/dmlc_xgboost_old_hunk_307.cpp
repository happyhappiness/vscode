    // read data from childs
    for (int i = 0; i < nlink; ++i) {
      if (i != parent_index && selecter.CheckRead(links[i].sock)) {
        ReturnType ret = links[i].ReadToRingBuffer(size_up_out);
        if (ret != kSuccess) {
          return ReportError(&links[i], ret);
        }
