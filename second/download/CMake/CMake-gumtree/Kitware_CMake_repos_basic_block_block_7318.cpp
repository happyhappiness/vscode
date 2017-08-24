{
    if(i < n)
      buf[i] = '.';
    i++;
    x = 0;
    do {
      if(x & 0xFF000000)
        return -1;
      y = *(const unsigned char *) beg++;
      x = (x << 7) | (y & 0x7F);
    } while(y & 0x80);
    i += encodeUint(buf + i, n - i, x);
  }