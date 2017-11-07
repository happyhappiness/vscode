static void _menu_status_line (char *buf, size_t buflen, size_t col, MUTTMENU *menu, const char *p)
{
  mutt_FormatString (buf, buflen, col, p, status_format_str, (unsigned long) menu, 0);
}