int mutt_alias_complete (char *s, size_t buflen)
{
  ALIAS *a = Aliases;
  ALIAS *a_list = NULL, *a_cur = NULL;
  char bestname[HUGE_STRING];
  int i;

#ifndef min
#define min(a,b)        ((a<b)?a:b)
#endif

  if (s[0] != 0) /* avoid empty string as strstr argument */
  {
    memset (bestname, 0, sizeof (bestname));

    while (a)
    {
      if (a->name && strstr (a->name, s) == a->name)
      {
	if (!bestname[0]) /* init */
	  strfcpy (bestname, a->name,
		   min (mutt_strlen (a->name) + 1, sizeof (bestname)));
	else
	{
	  for (i = 0 ; a->name[i] && a->name[i] == bestname[i] ; i++)
	    ;
	  bestname[i] = 0;
	}
      }
      a = a->next;
    }

    if (bestname[0] != 0)
    {
      if (mutt_strcmp (bestname, s) != 0)
      {
	/* we are adding something to the completion */
	strfcpy (s, bestname, mutt_strlen (bestname) + 1);
	return 1;
      }

      /* build alias list and show it */

      a = Aliases;
      while (a)
      {
	if (a->name && (strstr (a->name, s) == a->name))
	{
	  if (!a_list)  /* init */
	    a_cur = a_list = (ALIAS *) safe_malloc (sizeof (ALIAS));
	  else
	  {
	    a_cur->next = (ALIAS *) safe_malloc (sizeof (ALIAS));
	    a_cur = a_cur->next;
	  }
	  memcpy (a_cur, a, sizeof (ALIAS));
	  a_cur->next = NULL;
	}
	a = a->next;
      }
    }
  }

  bestname[0] = 0;
  mutt_alias_menu (bestname, sizeof(bestname), a_list ? a_list : Aliases);
  if (bestname[0] != 0)
    strfcpy (s, bestname, buflen);

  /* free the alias list */
  while (a_list)
  {
    a_cur = a_list;
    a_list = a_list->next;
    FREE (&a_cur);
  }

  /* remove any aliases marked for deletion */
  a_list = NULL;
  for (a_cur = Aliases; a_cur;)
  {
    if (a_cur->del)
    {
      if (a_list)
	a_list->next = a_cur->next;
      else
	Aliases = a_cur->next;
      
      a_cur->next = NULL;
      mutt_free_alias (&a_cur);
      
      if (a_list)
	a_cur = a_list;
      else
	a_cur = Aliases;
    }
    else
    {
      a_list = a_cur;
      a_cur  = a_cur->next;
    }
  }
  
  return 0;
}