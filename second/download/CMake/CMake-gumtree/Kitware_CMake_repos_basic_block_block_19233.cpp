(process_title) {
    len = strlen(process_title) + 1;

    if (size < len)
      return -ENOBUFS;

    memcpy(buffer, process_title, len);
  } else {
    len = 0;
  }