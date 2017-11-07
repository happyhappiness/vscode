static int menu_search (MUTTMENU *menu, int op)
{
  int r, wrap = 0;
  int searchDir;
  regex_t re;
  char buf[SHORT_STRING];
  char* searchBuf = menu->menu >= 0 && menu->menu < MENU_MAX ?
                    SearchBuffers[menu->menu] : NULL;

  if (!(searchBuf && *searchBuf) ||
      (op != OP_SEARCH_NEXT && op != OP_SEARCH_OPPOSITE))
  {
    strfcpy (buf, searchBuf && *searchBuf ? searchBuf : "", sizeof (buf));
    if (mutt_get_field ((op == OP_SEARCH || op == OP_SEARCH_NEXT)
			? _("Search for: ") : _("Reverse search for: "),
			buf, sizeof (buf), MUTT_CLEAR) != 0 || !buf[0])
      return (-1);
    if (menu->menu >= 0 && menu->menu < MENU_MAX)
    {
      mutt_str_replace (&SearchBuffers[menu->menu], buf);
      searchBuf = SearchBuffers[menu->menu];
    }
    menu->searchDir = (op == OP_SEARCH || op == OP_SEARCH_NEXT) ?
		       MUTT_SEARCH_DOWN : MUTT_SEARCH_UP;
  }

  searchDir = (menu->searchDir == MUTT_SEARCH_UP) ? -1 : 1;
  if (op == OP_SEARCH_OPPOSITE)
    searchDir = -searchDir;

  if ((r = REGCOMP (&re, searchBuf, REG_NOSUB | mutt_which_case (searchBuf))) != 0)
  {
    regerror (r, &re, buf, sizeof (buf));
    mutt_error ("%s", buf);
    return (-1);
  }

  r = menu->current + searchDir;
search_next:
  if (wrap)
    mutt_message (_("Search wrapped to top."));
  while (r >= 0 && r < menu->max)
  {
    if (menu->search (menu, &re, r) == 0)
    {
      regfree (&re);
      return r;
    }

    r += searchDir;
  }

  if (option (OPTWRAPSEARCH) && wrap++ == 0)
  {
    r = searchDir == 1 ? 0 : menu->max - 1;
    goto search_next;
  }
  regfree (&re);
  mutt_error _("Not found.");
  return (-1);
}