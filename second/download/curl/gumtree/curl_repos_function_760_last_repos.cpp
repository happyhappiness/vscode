static void lograw(unsigned char *buffer, ssize_t len)
{
  char data[120];
  ssize_t i;
  unsigned char *ptr = buffer;
  char *optr = data;
  ssize_t width = 0;
  int left = sizeof(data);

  for(i = 0; i<len; i++) {
    switch(ptr[i]) {
    case '\n':
      snprintf(optr, left, "\\n");
      width += 2;
      optr += 2;
      left -= 2;
      break;
    case '\r':
      snprintf(optr, left, "\\r");
      width += 2;
      optr += 2;
      left -= 2;
      break;
    default:
      snprintf(optr, left, "%c", (ISGRAPH(ptr[i]) ||
                                  ptr[i] == 0x20) ?ptr[i]:'.');
      width++;
      optr++;
      left--;
      break;
    }

    if(width>60) {
      logmsg("'%s'", data);
      width = 0;
      optr = data;
      left = sizeof(data);
    }
  }
  if(width)
    logmsg("'%s'", data);
}