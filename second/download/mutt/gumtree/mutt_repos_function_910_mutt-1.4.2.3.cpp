static int menu_search (MUTTMENU *menu, int op)
{
  int r;
  int searchDir;
  regex_t re;
  char buf[SHORT_STRING];

  if (op != OP_SEARCH_NEXT && op != OP_SEARCH_OPPOSITE)
  {
    strfcpy (buf, menu->searchBuf ? menu->searchBuf : "", sizeof (buf));
    if (mutt_get_field ((op == OP_SEARCH) ? _("Search for: ") : 
                                            _("Reverse search for: "),
			 buf, sizeof (buf), M_CLEAR) != 0 || !buf[0])
      return (-1);
    mutt_str_replace (&menu->searchBuf, buf);
    menu->searchDir = (op == OP_SEARCH) ? M_SEARCH_DOWN : M_SEARCH_UP;
  }
  else 
  {
    if (!menu->searchBuf)
    {
      mutt_error _("No search pattern.");
      return (-1);
    }
  }

  searchDir = (menu->searchDir == M_SEARCH_UP) ? -1 : 1;
  if (op == OP_SEARCH_OPPOSITE)
    searchDir = -searchDir;

  if ((r = REGCOMP (&re, menu->searchBuf, REG_NOSUB | mutt_which_case (menu->searchBuf))) != 0)
  {
    regerror (r, &re, buf, sizeof (buf));
    regfree (&re);
    mutt_error ("%s", buf);
    return (-1);
  }

  r = menu->current + searchDir;
  while (r >= 0 && r < menu->max)
  {
    if (menu->search (menu, &re, r) == 0)
    {
      regfree (&re);
      return r;
    }

    r += searchDir;
  }

  regfree (&re);
  mutt_error _("Not found.");
  return (-1);
}