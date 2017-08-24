{
    if (errno == EAGAIN)
      return -EAGAIN;
    abort();
  }