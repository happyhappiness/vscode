void *suck(int *lenptr)
{
  int cursize = 8192;
  unsigned char *buf = NULL;
  int lastread;
  int len = 0;

  do {
    cursize *= 2;
    buf = (unsigned char *)realloc(buf, cursize);
    memset(buf + len, 0, cursize - len);
    lastread = fread(buf + len, 1, cursize - len, stdin);
    len += lastread;
  } while(!feof(stdin));

  lenptr[0] = len;
  return (void *)buf;
}