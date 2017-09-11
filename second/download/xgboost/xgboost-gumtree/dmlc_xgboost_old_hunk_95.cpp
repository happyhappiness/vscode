          if (len != -1) {
            links[i].size_write += len;
          } else {
            ReturnType ret = Errno2Return(errno);
            if (ret != kSuccess) return ReportError(&links[i], ret);
          }
        }
