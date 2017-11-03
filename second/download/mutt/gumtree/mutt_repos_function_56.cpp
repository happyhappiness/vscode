void mutt_make_help (char *d, size_t dlen, const char *txt, int menu, int op)
{
  char buf[SHORT_STRING];

  if (km_expand_key (buf, sizeof (buf), km_find_func (menu, op)) ||
      km_expand_key (buf, sizeof (buf), km_find_func (MENU_GENERIC, op)))
    snprintf (d, dlen, "%s:%s", buf, txt);
  else
    d[0] = 0;
}