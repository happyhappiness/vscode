static char *inet_ntop4 (const unsigned char *src, char *dst, size_t size)
{
  char tmp[sizeof "255.255.255.255"];
  size_t len;

  DEBUGASSERT(size >= 16);

  tmp[0] = '\0';
  (void)snprintf(tmp, sizeof(tmp), "%d.%d.%d.%d",
                 ((int)((unsigned char)src[0])) & 0xff,
                 ((int)((unsigned char)src[1])) & 0xff,
                 ((int)((unsigned char)src[2])) & 0xff,
                 ((int)((unsigned char)src[3])) & 0xff);

  len = strlen(tmp);
  if(len == 0 || len >= size) {
    errno = ENOSPC;
    return (NULL);
  }
  strcpy(dst, tmp);
  return dst;
}