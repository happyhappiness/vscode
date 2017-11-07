int mutt_search_command (int cur, int op)
{
  int i, j;
  char buf[STRING];
  char temp[LONG_STRING];
  char error[STRING];
  BUFFER err;
  int incr;
  HEADER *h;
  
  if (op != OP_SEARCH_NEXT && op != OP_SEARCH_OPPOSITE)
  {
    strfcpy (buf, LastSearch, sizeof (buf));
    if (mutt_get_field ((op == OP_SEARCH) ? _("Search for: ") :
		      _("Reverse search for: "), buf, sizeof (buf),
		      M_CLEAR | M_PATTERN) != 0 || !buf[0])
      return (-1);

    if (op == OP_SEARCH)
      unset_option (OPTSEARCHREVERSE);
    else
      set_option (OPTSEARCHREVERSE);

    /* compare the *expanded* version of the search pattern in case 
       $simple_search has changed while we were searching */
    strfcpy (temp, buf, sizeof (temp));
    mutt_check_simple (temp, sizeof (temp), NONULL (SimpleSearch));

    if (!SearchPattern || mutt_strcmp (temp, LastSearchExpn))
    {
      set_option (OPTSEARCHINVALID);
      strfcpy (LastSearch, buf, sizeof (LastSearch));
      mutt_message _("Compiling search pattern...");
      mutt_pattern_free (&SearchPattern);
      err.data = error;
      err.dsize = sizeof (error);
      if ((SearchPattern = mutt_pattern_comp (temp, M_FULL_MSG, &err)) == NULL)
      {
	mutt_error ("%s", error);
	return (-1);
      }
      mutt_clear_error ();
    }
  }
  else if (!SearchPattern)
  {
    mutt_error _("No search pattern.");
    return (-1);
  }

  if (option (OPTSEARCHINVALID))
  {
    for (i = 0; i < Context->msgcount; i++)
      Context->hdrs[i]->searched = 0;
    unset_option (OPTSEARCHINVALID);
  }

  incr = (option (OPTSEARCHREVERSE)) ? -1 : 1;
  if (op == OP_SEARCH_OPPOSITE)
    incr = -incr;

  for (i = cur + incr, j = 0 ; j != Context->vcount; j++)
  {
    if (i > Context->vcount - 1)
    {
      i = 0;
      if (option (OPTWRAPSEARCH))
        mutt_message _("Search wrapped to top.");
      else 
      {
        mutt_message _("Search hit bottom without finding match");
	return (-1);
      }
    }
    else if (i < 0)
    {
      i = Context->vcount - 1;
      if (option (OPTWRAPSEARCH))
        mutt_message _("Search wrapped to bottom.");
      else 
      {
        mutt_message _("Search hit top without finding match");
	return (-1);
      }
    }

    h = Context->hdrs[Context->v2r[i]];
    if (h->searched)
    {
      /* if we've already evaulated this message, use the cached value */
      if (h->matched)
	return i;
    }
    else
    {
      /* remember that we've already searched this message */
      h->searched = 1;
      if ((h->matched = (mutt_pattern_exec (SearchPattern, M_MATCH_FULL_ADDRESS, Context, h) > 0)))
	return i;
    }

    if (SigInt)
    {
      mutt_error _("Search interrupted.");
      SigInt = 0;
      return (-1);
    }

    i += incr;
  }

  mutt_error _("Not found.");
  return (-1);
}