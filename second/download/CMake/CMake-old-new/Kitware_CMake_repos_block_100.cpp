{
    char suff[2];
    if(RTMP_LIB_VERSION & 0xff) {
      suff[0] = (RTMP_LIB_VERSION & 0xff) + 'a' - 1;
      suff[1] = '\0';
    }
    else
      suff[0] = '\0';

    snprintf(ptr, left, " librtmp/%d.%d%s",
             RTMP_LIB_VERSION >> 16, (RTMP_LIB_VERSION >> 8) & 0xff,
             suff);
/*
  If another lib version is added below this one, this code would
  also have to do:

    len = what snprintf() returned

    left -= len;
    ptr += len;
*/
  }