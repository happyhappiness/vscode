void menu_pad_string (char *s, size_t n)
{
  int shift = option (OPTARROWCURSOR) ? 3 : 0;
  int cols = COLS - shift;

  mutt_format_string (s, n, cols, cols, 0, ' ', s, strlen (s), 1);
  s[n - 1] = 0;
}