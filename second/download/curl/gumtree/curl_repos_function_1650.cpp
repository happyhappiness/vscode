ssize_t curlx_read(int fd, void *buf, size_t count)
{
  return (ssize_t)read(fd, buf, curlx_uztoui(count));
}