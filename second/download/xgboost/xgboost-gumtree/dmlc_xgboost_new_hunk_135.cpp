    if (role == kRequestData) {
      const int pid = recv_link;
      if (selecter.CheckRead(links[pid].sock)) {
        ReturnType ret = links[pid].ReadToArray(sendrecvbuf_, size);
        if (ret != kSuccess) {
          return ReportError(&links[pid], ret);
        }
