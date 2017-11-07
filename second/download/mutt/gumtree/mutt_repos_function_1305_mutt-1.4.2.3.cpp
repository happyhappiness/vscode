int imap_make_msg_set (IMAP_DATA* idata, BUFFER* buf, int flag, int changed)
{
  HEADER** hdrs;	/* sorted local copy */
  int count = 0;	/* number of messages in message set */
  int match = 0;	/* whether current message matches flag condition */
  unsigned int setstart = 0;	/* start of current message range */
  int n;
  short oldsort;	/* we clobber reverse, must restore it */
  /* assuming 32-bit UIDs */
  char uid[12];
  int started = 0;

  /* make copy of header pointers to sort in natural order */
  hdrs = safe_calloc (idata->ctx->msgcount, sizeof (HEADER*));
  memcpy (hdrs, idata->ctx->hdrs, idata->ctx->msgcount * sizeof (HEADER*));

  if (Sort != SORT_ORDER)
  {
    oldsort = Sort;
    Sort = SORT_ORDER;
    qsort ((void*) hdrs, idata->ctx->msgcount, sizeof (HEADER*),
      mutt_get_sort_func (SORT_ORDER));
    Sort = oldsort;
  }
  
  for (n = 0; n < idata->ctx->msgcount; n++)
  {
    match = 0;
    /* don't include pending expunged messages */
    if (hdrs[n]->active)
      switch (flag)
      {
        case M_DELETE:
	  if (hdrs[n]->deleted)
	    match = 1;
	  break;
        case M_TAG:
	  if (hdrs[n]->tagged)
	    match = 1;
	  break;
      }

    if (match && (!changed || hdrs[n]->changed))
    {
      count++;
      if (setstart == 0)
      {
        setstart = HEADER_DATA (hdrs[n])->uid;
        if (started == 0)
	{
	  snprintf (uid, sizeof (uid), "%u", HEADER_DATA (hdrs[n])->uid);
	  mutt_buffer_addstr (buf, uid);
	  started = 1;
	}
        else
        {
	  snprintf (uid, sizeof (uid), ",%u", HEADER_DATA (hdrs[n])->uid);
	  mutt_buffer_addstr (buf, uid);
        }
      }
      /* tie up if the last message also matches */
      else if (n == idata->ctx->msgcount-1)
      {
	snprintf (uid, sizeof (uid), ":%u", HEADER_DATA (hdrs[n])->uid);
	mutt_buffer_addstr (buf, uid);
      }
    }
    /* this message is not expunged and doesn't match. End current set. */
    else if (setstart && hdrs[n]->active)
    {
      if (HEADER_DATA (hdrs[n-1])->uid > setstart)
      {
	snprintf (uid, sizeof (uid), ":%u", HEADER_DATA (hdrs[n-1])->uid);
	mutt_buffer_addstr (buf, uid);
      }
      setstart = 0;
    }
  }

  safe_free ((void**) &hdrs);

  return count;
}