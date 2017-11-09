static void menu_pad_string (MUTTMENU *menu, char *s, size_t n)
{
  char *scratch = safe_strdup (s);
  int shift = option (OPTARROWCURSOR) ? 3 : 0;
  int cols = menu->indexwin->cols - shift;

  mutt_format_string (s, n, cols, cols, FMT_LEFT, ' ', scratch, mutt_strlen (scratch), 1);
  s[n - 1] = 0;
  FREE (&scratch);
}