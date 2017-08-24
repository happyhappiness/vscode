(use_pread)
        nread = pread(in_fd, buf, buflen, offset);
      else
        nread = read(in_fd, buf, buflen)