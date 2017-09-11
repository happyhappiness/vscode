        ssize_t len = links[parent_index].sock.
            Recv(sendrecvbuf + size_down_in, total_size - size_down_in);
        if (len == 0) {
          links[parent_index].sock.Close();
          return ReportError(&links[parent_index], kRecvZeroLen);
        }
        if (len != -1) {
          size_down_in += static_cast<size_t>(len);
          utils::Assert(size_down_in <= size_up_out,
                        "Allreduce: boundary error");
        } else {
          ReturnType ret = Errno2Return();
          if (ret != kSuccess) {
            return ReportError(&links[parent_index], ret);
          }
