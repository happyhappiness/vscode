void unmap_file(char *buf,off_t len)
{
#ifdef HAVE_MMAP
  if (len > 0 && buf)
    munmap(buf,len);
#endif
  map_fd = -1;
  map_size = 0;
  p_len = 0;
}