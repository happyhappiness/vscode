static int parse_unalias (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  ALIAS *tmp, *last = NULL;

  do
  {
    mutt_extract_token (buf, s, 0);

    if (mutt_strcmp ("*", buf->data) == 0)
    {
      if (CurrentMenu == MENU_ALIAS)
      {
	for (tmp = Aliases; tmp ; tmp = tmp->next) 
	  tmp->del = 1;
	set_option (OPTFORCEREDRAWINDEX);
      }
      else
	mutt_free_alias (&Aliases);
      break;
    }
    else
      for (tmp = Aliases; tmp; tmp = tmp->next)
      {
	if (mutt_strcasecmp (buf->data, tmp->name) == 0)
	{
	  if (CurrentMenu == MENU_ALIAS)
	  {
	    tmp->del = 1;
	    set_option (OPTFORCEREDRAWINDEX);
	    break;
	  }

	  if (last)
	    last->next = tmp->next;
	  else
	    Aliases = tmp->next;
	  tmp->next = NULL;
	  mutt_free_alias (&tmp);
	  break;
	}
	last = tmp;
      }
  }
  while (MoreArgs (s));
  return 0;
}