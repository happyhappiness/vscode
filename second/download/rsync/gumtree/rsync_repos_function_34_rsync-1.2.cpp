void unmap_file(char *buf,off_t len)
{
  if (len > 0 && buf)
    munmap(buf,len);
}