static ssize_t read_wincon(int fd, void *buf, size_t count)
{
  HANDLE handle = NULL;
  DWORD mode, rcount = 0;
  BOOL success;

  if(fd == fileno(stdin)) {
    handle = GetStdHandle(STD_INPUT_HANDLE);
  }
  else {
    return read(fd, buf, count);
  }

  if(GetConsoleMode(handle, &mode)) {
    success = ReadConsole(handle, buf, curlx_uztoul(count), &rcount, NULL);
  }
  else {
    success = ReadFile(handle, buf, curlx_uztoul(count), &rcount, NULL);
  }
  if(success) {
    return rcount;
  }

  errno = GetLastError();
  return -1;
}