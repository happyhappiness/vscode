static ssize_t write_wincon(int fd, const void *buf, size_t count)
{
  HANDLE handle = NULL;
  DWORD mode, wcount = 0;
  BOOL success;

  if(fd == fileno(stdout)) {
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
  }
  else if(fd == fileno(stderr)) {
    handle = GetStdHandle(STD_ERROR_HANDLE);
  }
  else {
    return write(fd, buf, count);
  }

  if(GetConsoleMode(handle, &mode)) {
    success = WriteConsole(handle, buf, curlx_uztoul(count), &wcount, NULL);
  }
  else {
    success = WriteFile(handle, buf, curlx_uztoul(count), &wcount, NULL);
  }
  if(success) {
    return wcount;
  }

  errno = GetLastError();
  return -1;
}