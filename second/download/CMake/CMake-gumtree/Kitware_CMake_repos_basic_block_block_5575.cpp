{
    us_length = htons((short)1);
    memcpy(socksreq+2, &us_length, sizeof(short));
  }