int mutt_search_command (int cur, int op)
{
  int i, j;
  char buf[STRING];
  char temp[LONG_STRING];
  int incr;
  HEADER *h;
  progress_t progress;
  const char* msg = NULL;

  if (!*LastSearch || (op != OP_SEARCH_NEXT && op != OP_SEARCH_OPPOSITE))
  {
    strfcpy (buf, *LastSearch ? LastSearch : "", sizeof (buf));
    if (mutt_get_field ((op == OP_SEARCH || op == OP_SEARCH_NEXT) ?
			_("Search for: ") : _("Reverse search for: "),
			buf, sizeof (buf),
		      MUTT_CLEAR | MUTT_PATTERN) != 0 || !buf[0])
      return (-1);

    if (op == OP_SEARCH || op == OP_SEARCH_NEXT)
      unset_option (OPTSEARCHREVERSE);
    else
      set_option (OPTSEARCHREVERSE);

    /* compare the *expanded* version of the search pattern in case 
       $simple_search has changed while we were searching */
    strfcpy (temp, buf, sizeof (temp));
    mutt_check_simple (temp, sizeof (temp), NONULL (SimpleSearch));

    if (!SearchPattern || mutt_strcmp (temp, LastSearchExpn))
    {
      BUFFER err;
      mutt_buffer_init (&err);
      set_option (OPTSEARCHINVALID);
      strfcpy (LastSearch, buf, sizeof (LastSearch));
      mutt_message _("Compiling search pattern...");
      mutt_pattern_free (&SearchPattern);
      err.dsize = STRING;
      err.data = safe_malloc (err.dsize);
      if ((SearchPattern = mutt_pattern_comp (temp, MUTT_FULL_MSG, &err)) == NULL)
      {
	mutt_error ("%s", err.data);
	FREE (&err.data);
	LastSearch[0] = '\0';
	return (-1);
      }
      mutt_clear_error ();
    }
  }

  if (option (OPTSEARCHINVALID))
  {
    for (i = 0; i < Context->msgcount; i++)
      Context->hdrs[i]->searched = 0;
#ifdef USE_IMAP
    if (Context->magic == MUTT_IMAP && imap_search (Context, SearchPattern) < 0)
      return -1;
#endif
    unset_option (OPTSEARCHINVALID);
  }

  incr = (option (OPTSEARCHREVERSE)) ? -1 : 1;
  if (op == OP_SEARCH_OPPOSITE)
    incr = -incr;

  mutt_progress_init (&progress, _("Searching..."), MUTT_PROGRESS_MSG,
		      ReadInc, Context->vcount);

  for (i = cur + incr, j = 0 ; j != Context->vcount; j++)
  {
    mutt_progress_update (&progress, j, -1);
    if (i > Context->vcount - 1)
    {
      i = 0;
      if (option (OPTWRAPSEARCH))
        msg = _("Search wrapped to top.");
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
        msg = _("Search wrapped to bottom.");
      else 
      {
        mutt_message _("Search hit top without finding match");
	return (-1);
      }
    }

    h = Context->hdrs[Context->v2r[i]];
    if (h->searched)
    {
      /* if we've already evaluated this message, use the cached value */
      if (h->matched)
      {
	mutt_clear_error();
	if (msg && *msg)
	  mutt_message (msg);
	return i;
      }
    }
    else
    {
      /* remember that we've already searched this message */
      h->searched = 1;
      if ((h->matched = (mutt_pattern_exec (SearchPattern, MUTT_MATCH_FULL_ADDRESS, Context, h) > 0)))
      {
	mutt_clear_error();
	if (msg && *msg)
	  mutt_message (msg);
	return i;
      }
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