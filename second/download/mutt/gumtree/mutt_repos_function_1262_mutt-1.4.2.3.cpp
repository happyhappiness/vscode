int imap_read_headers (IMAP_DATA* idata, int msgbegin, int msgend)
{
  CONTEXT* ctx;
  char buf[LONG_STRING];
  char hdrreq[STRING];
  FILE *fp;
  char tempfile[_POSIX_PATH_MAX];
  int msgno;
  IMAP_HEADER h;
  int rc, mfhrc, oldmsgcount;
  int fetchlast = 0;
  const char *want_headers = "DATE FROM SUBJECT TO CC MESSAGE-ID REFERENCES CONTENT-TYPE IN-REPLY-TO REPLY-TO LINES X-LABEL";

  ctx = idata->ctx;

  if (mutt_bit_isset (idata->capabilities,IMAP4REV1))
  {
    snprintf (hdrreq, sizeof (hdrreq), "BODY.PEEK[HEADER.FIELDS (%s)]", 
      want_headers); 
  } 
  else if (mutt_bit_isset (idata->capabilities,IMAP4))
  {
    snprintf (hdrreq, sizeof (hdrreq), "RFC822.HEADER.LINES (%s)", 
      want_headers);
  }
  else
  {	/* Unable to fetch headers for lower versions */
    mutt_error _("Unable to fetch headers from this IMAP server version.");
    mutt_sleep (2);	/* pause a moment to let the user see the error */
    return -1;
  }

  /* instead of downloading all headers and then parsing them, we parse them
   * as they come in. */
  mutt_mktemp (tempfile);
  if (!(fp = safe_fopen (tempfile, "w+")))
  {
    mutt_error (_("Could not create temporary file %s"), tempfile);
    mutt_sleep (2);
    return -1;
  }
  unlink (tempfile);

  /* make sure context has room to hold the mailbox */
  while ((msgend) >= idata->ctx->hdrmax)
    mx_alloc_memory (idata->ctx);

  oldmsgcount = ctx->msgcount;
  idata->reopen &= ~IMAP_NEWMAIL_PENDING;
  idata->newMailCount = 0;

  for (msgno = msgbegin; msgno <= msgend ; msgno++)
  {
    if (ReadInc && (!msgno || ((msgno+1) % ReadInc == 0)))
      mutt_message (_("Fetching message headers... [%d/%d]"), msgno + 1,
        msgend + 1);

    if (msgno + 1 > fetchlast)
    {
      /*
       * Make one request for everything. This makes fetching headers an
       * order of magnitude faster if you have a large mailbox.
       *
       * If we get more messages while doing this, we make another
       * request for all the new messages.
       */
      snprintf (buf, sizeof (buf),
        "FETCH %d:%d (UID FLAGS INTERNALDATE RFC822.SIZE %s)", msgno + 1,
        msgend + 1, hdrreq);

      imap_cmd_start (idata, buf);

      fetchlast = msgend + 1;
    }

    /* freshen fp, h */
    rewind (fp);
    memset (&h, 0, sizeof (h));
    h.data = safe_calloc (1, sizeof (IMAP_HEADER_DATA));

    /* this DO loop does two things:
     * 1. handles untagged messages, so we can try again on the same msg
     * 2. fetches the tagged response at the end of the last message.
     */
    do
    {
      mfhrc = 0;

      rc = imap_cmd_step (idata);
      if (rc != IMAP_CMD_CONTINUE)
	break;

      if ((mfhrc = msg_fetch_header (idata->ctx, &h, idata->cmd.buf, fp)) == -1)
	continue;
      else if (mfhrc < 0)
	break;

      /* make sure we don't get remnants from older larger message headers */
      fputs ("\n\n", fp);

      /* update context with message header */
      ctx->hdrs[msgno] = mutt_new_header ();

      ctx->hdrs[msgno]->index = h.sid - 1;
      if (h.sid != ctx->msgcount + 1)
	dprint (1, (debugfile, "imap_read_headers: msgcount and sequence ID are inconsistent!"));
      /* messages which have not been expunged are ACTIVE (borrowed from mh 
       * folders) */
      ctx->hdrs[msgno]->active = 1;
      ctx->hdrs[msgno]->read = h.read;
      ctx->hdrs[msgno]->old = h.old;
      ctx->hdrs[msgno]->deleted = h.deleted;
      ctx->hdrs[msgno]->flagged = h.flagged;
      ctx->hdrs[msgno]->replied = h.replied;
      ctx->hdrs[msgno]->changed = h.changed;
      ctx->hdrs[msgno]->received = h.received;
      ctx->hdrs[msgno]->data = (void *) (h.data);

      rewind (fp);
      /* NOTE: if Date: header is missing, mutt_read_rfc822_header depends
       *   on h.received being set */
      ctx->hdrs[msgno]->env = mutt_read_rfc822_header (fp, ctx->hdrs[msgno],
        0, 0);
      /* content built as a side-effect of mutt_read_rfc822_header */
      ctx->hdrs[msgno]->content->length = h.content_length;

      ctx->msgcount++;
    }
    while ((rc != IMAP_CMD_OK) && ((mfhrc == -1) ||
      ((msgno + 1) >= fetchlast)));

    if ((mfhrc < -1) || ((rc != IMAP_CMD_CONTINUE) && (rc != IMAP_CMD_OK)))
    {
      imap_free_header_data ((void**) &h.data);
      fclose (fp);

      return -1;
    }
	
    /* in case we get new mail while fetching the headers */
    if (idata->reopen & IMAP_NEWMAIL_PENDING)
    {
      msgend = idata->newMailCount - 1;
      while ((msgend) >= ctx->hdrmax)
	mx_alloc_memory (ctx);
      idata->reopen &= ~IMAP_NEWMAIL_PENDING;
      idata->newMailCount = 0;
    }
  }

  fclose(fp);

  if (ctx->msgcount > oldmsgcount)
    mx_update_context (ctx, ctx->msgcount - oldmsgcount);

  return msgend;
}