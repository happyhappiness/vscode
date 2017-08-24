{
      if(x & 0xFF000000)
        return -1;
      y = *(const unsigned char *) beg++;
      x = (x << 7) | (y & 0x7F);
    }