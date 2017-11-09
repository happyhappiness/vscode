int tool_ftruncate64(int fd, curl_off_t where)
{
  if(_lseeki64(fd, where, SEEK_SET) < 0)
    return -1;

  if(!SetEndOfFile((HANDLE)_get_osfhandle(fd)))
    return -1;

  return 0;
}