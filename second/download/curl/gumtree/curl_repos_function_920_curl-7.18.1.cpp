static int
block_write(int fd, const void *buf, size_t len)
{
  const unsigned char *p = buf;
  int b;
  while(len) {
    b = write(fd, p, len);
    if(b < 0 && (errno == EINTR || errno == EAGAIN))
      continue;
    else if(b < 0)
      return -1;
    len -= b;
    p += b;
  }
  return p - (unsigned char*)buf;
}