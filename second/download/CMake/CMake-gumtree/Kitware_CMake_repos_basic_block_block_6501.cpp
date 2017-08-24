{
      cap *= 2;
      data = realloc(data, cap);
      if(!data) {
        close(fd);
        return -1;
      }
    }