static void _menu_status_line (char *buf, size_t buflen, size_t col, int cols, MUTTMENU *menu, const char *p)
{
  mutt_FormatString (buf, buflen, col, cols, p, status_format_str, (unsigned long) menu, 0);
}