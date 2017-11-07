void menu_status_line (char *buf, size_t buflen, MUTTMENU *menu, const char *p)
{
  mutt_FormatString (buf, buflen, 0, p, status_format_str, (unsigned long) menu, 0);
}