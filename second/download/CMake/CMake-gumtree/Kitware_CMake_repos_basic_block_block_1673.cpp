(fgets(buf, bufSize, file) == 0) {
      if (ferror(file) && (errno == EINTR)) {
        clearerr(file);
      }
      continue;
    }