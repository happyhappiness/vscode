static void lograw(unsigned char *buffer, int len)
{
  char data[120];
  int i;
  unsigned char *ptr = buffer;
  char *optr = data;
  int width=0;

  for(i=0; i<len; i++) {
    sprintf(optr, "%c",
            (isgraph(ptr[i]) || ptr[i]==0x20) ?ptr[i]:'.');
    optr += 1;
    width += 1;

    if(width>60) {
      logmsg("RAW: '%s'", data);
      width = 0;
      optr = data;
    }
  }
  if(width)
    logmsg("RAW: '%s'", data);
}