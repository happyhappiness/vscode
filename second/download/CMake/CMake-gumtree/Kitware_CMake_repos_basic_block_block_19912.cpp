{
  struct winsize ws;
  int err;

  do
    err = ioctl(uv__stream_fd(tty), TIOCGWINSZ, &ws);
  while (err == -1 && errno == EINTR);

  if (err == -1)
    return -errno;

  *width = ws.ws_col;
  *height = ws.ws_row;

  return 0;
}