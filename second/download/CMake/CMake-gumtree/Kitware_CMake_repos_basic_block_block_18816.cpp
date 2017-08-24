{
    len = strlen(buf);

    if (len >= *size) {
      *size = len + 1;
      return -ENOBUFS;
    }

    memcpy(buffer, buf, len + 1);
    *size = len;

    return 0;
  }