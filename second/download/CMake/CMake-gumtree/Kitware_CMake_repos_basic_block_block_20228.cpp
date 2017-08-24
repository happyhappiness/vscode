{
      n = _read(fd_in, buf, length < buf_size ? length : buf_size);
      if (n == 0) {
        break;
      } else if (n == -1) {
        result = -1;
        break;
      }

      length -= n;

      n = _write(fd_out, buf, n);
      if (n == -1) {
        result = -1;
        break;
      }

      result += n;
    }