      if (len != -1) {
        read_ptr += static_cast<size_t>(len);
      } else {
        ReturnType ret = Errno2Return(errno);
        if (ret != kSuccess) return ReportError(&next, ret);
      }
    }
