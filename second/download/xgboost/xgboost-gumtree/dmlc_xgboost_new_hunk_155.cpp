        if (len != -1) {
          size_up_out += static_cast<size_t>(len);
        } else {
          ReturnType ret = Errno2Return();
          if (ret != kSuccess) {
            return ReportError(&links[parent_index], ret);
          }
