static int menu_search_generic (MUTTMENU *m, regex_t *re, int n)
{
  char buf[LONG_STRING];

  menu_make_entry (buf, sizeof (buf), m, n);
  return (regexec (re, buf, 0, NULL, 0));
}