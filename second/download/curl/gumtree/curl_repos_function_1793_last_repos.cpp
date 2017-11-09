ssize_t curlx_write(int fd, const void *buf, size_t count)
{
  return (ssize_t)write(fd, buf, curlx_uztoui(count));
}