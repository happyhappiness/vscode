{
    buf = malloc(3 * n + 1);
    if(buf)
      for(n = 0; beg < end; n += 3)
        snprintf(buf + n, 4, "%02x:", *(const unsigned char *) beg++);
  }