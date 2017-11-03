std::pair<int, int>
Canvas::term_size() {
  struct winsize ws;

  if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == 0)
    return std::pair<int, int>(ws.ws_col, ws.ws_row);
  else
    return std::pair<int, int>(80, 24);
}