(r == 0 || r >= cwd_len) {
      err = GetLastError();
      goto done;
    }