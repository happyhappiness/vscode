int mutt_pattern_func (int op, char *prompt)
{
  pattern_t *pat;
  char buf[LONG_STRING] = "", *simple;
  BUFFER err;
  int i;
  progress_t progress;

  strfcpy (buf, NONULL (Context->pattern), sizeof (buf));
  if (mutt_get_field (prompt, buf, sizeof (buf), MUTT_PATTERN | MUTT_CLEAR) != 0 || !buf[0])
    return (-1);

  mutt_message _("Compiling search pattern...");
  
  simple = safe_strdup (buf);
  mutt_check_simple (buf, sizeof (buf), NONULL (SimpleSearch));

  mutt_buffer_init (&err);
  err.dsize = STRING;
  err.data = safe_malloc(err.dsize);
  if ((pat = mutt_pattern_comp (buf, MUTT_FULL_MSG, &err)) == NULL)
  {
    FREE (&simple);
    mutt_error ("%s", err.data);
    FREE (&err.data);
    return (-1);
  }

#ifdef USE_IMAP
  if (Context->magic == MUTT_IMAP && imap_search (Context, pat) < 0)
    return -1;
#endif

  mutt_progress_init (&progress, _("Executing command on matching messages..."),
		      MUTT_PROGRESS_MSG, ReadInc,
		      (op == MUTT_LIMIT) ? Context->msgcount : Context->vcount);

#define THIS_BODY Context->hdrs[i]->content

  if (op == MUTT_LIMIT)
  {
    Context->vcount    = 0;
    Context->vsize     = 0;
    Context->collapsed = 0;

    for (i = 0; i < Context->msgcount; i++)
    {
      mutt_progress_update (&progress, i, -1);
      /* new limit pattern implicitly uncollapses all threads */
      Context->hdrs[i]->virtual = -1;
      Context->hdrs[i]->limited = 0;
      Context->hdrs[i]->collapsed = 0;
      Context->hdrs[i]->num_hidden = 0;
      if (mutt_pattern_exec (pat, MUTT_MATCH_FULL_ADDRESS, Context, Context->hdrs[i], NULL))
      {
	Context->hdrs[i]->virtual = Context->vcount;
	Context->hdrs[i]->limited = 1;
	Context->v2r[Context->vcount] = i;
	Context->vcount++;
	Context->vsize+=THIS_BODY->length + THIS_BODY->offset -
	  THIS_BODY->hdr_offset;
      }
    }
  }
  else
  {
    for (i = 0; i < Context->vcount; i++)
    {
      mutt_progress_update (&progress, i, -1);
      if (mutt_pattern_exec (pat, MUTT_MATCH_FULL_ADDRESS, Context, Context->hdrs[Context->v2r[i]], NULL))
      {
	switch (op)
	{
          case MUTT_UNDELETE:
            mutt_set_flag (Context, Context->hdrs[Context->v2r[i]], MUTT_PURGE,
                           0);
	  case MUTT_DELETE:
	    mutt_set_flag (Context, Context->hdrs[Context->v2r[i]], MUTT_DELETE, 
			  (op == MUTT_DELETE));
	    break;
	  case MUTT_TAG:
	  case MUTT_UNTAG:
	    mutt_set_flag (Context, Context->hdrs[Context->v2r[i]], MUTT_TAG, 
			   (op == MUTT_TAG));
	    break;
	}
      }
    }
  }

#undef THIS_BODY

  mutt_clear_error ();

  if (op == MUTT_LIMIT)
  {
    /* drop previous limit pattern */
    FREE (&Context->pattern);
    if (Context->limit_pattern)
      mutt_pattern_free (&Context->limit_pattern);

    if (Context->msgcount && !Context->vcount)
      mutt_error _("No messages matched criteria.");

    /* record new limit pattern, unless match all */
    if (mutt_strcmp (buf, "~A") != 0)
    {
      Context->pattern = simple;
      simple = NULL; /* don't clobber it */
      Context->limit_pattern = mutt_pattern_comp (buf, MUTT_FULL_MSG, &err);
    }
  }
  FREE (&simple);
  mutt_pattern_free (&pat);
  FREE (&err.data);

  return 0;
}