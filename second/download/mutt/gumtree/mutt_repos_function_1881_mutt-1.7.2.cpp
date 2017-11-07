int imap_read_headers (IMAP_DATA* idata, int msgbegin, int msgend)
{
  CONTEXT* ctx;
  char *hdrreq = NULL;
  FILE *fp;
  char tempfile[_POSIX_PATH_MAX];
  int msgno, idx = msgbegin - 1;
  IMAP_HEADER h;
  IMAP_STATUS* status;
  int rc, mfhrc, oldmsgcount;
  int fetchlast = 0;
  int maxuid = 0;
  static const char * const want_headers = "DATE FROM SUBJECT TO CC MESSAGE-ID REFERENCES CONTENT-TYPE CONTENT-DESCRIPTION IN-REPLY-TO REPLY-TO LINES LIST-POST X-LABEL";
  progress_t progress;
  int retval = -1;

#if USE_HCACHE
  char buf[LONG_STRING];
  unsigned int *uid_validity = NULL;
  unsigned int *puidnext = NULL;
  unsigned int uidnext = 0;
  int evalhc = 0;
#endif /* USE_HCACHE */

  ctx = idata->ctx;

  if (mutt_bit_isset (idata->capabilities,IMAP4REV1))
  {
    safe_asprintf (&hdrreq, "BODY.PEEK[HEADER.FIELDS (%s%s%s)]",
                           want_headers, ImapHeaders ? " " : "", NONULL (ImapHeaders));
  }
  else if (mutt_bit_isset (idata->capabilities,IMAP4))
  {
    safe_asprintf (&hdrreq, "RFC822.HEADER.LINES (%s%s%s)",
                           want_headers, ImapHeaders ? " " : "", NONULL (ImapHeaders));
  }
  else
  {	/* Unable to fetch headers for lower versions */
    mutt_error _("Unable to fetch headers from this IMAP server version.");
    mutt_sleep (2);	/* pause a moment to let the user see the error */
    goto error_out_0;
  }

  /* instead of downloading all headers and then parsing them, we parse them
   * as they come in. */
  mutt_mktemp (tempfile, sizeof (tempfile));
  if (!(fp = safe_fopen (tempfile, "w+")))
  {
    mutt_error (_("Could not create temporary file %s"), tempfile);
    mutt_sleep (2);
    goto error_out_0;
  }
  unlink (tempfile);

  /* make sure context has room to hold the mailbox */
  while ((msgend) >= idata->ctx->hdrmax)
    mx_alloc_memory (idata->ctx);

  oldmsgcount = ctx->msgcount;
  idata->reopen &= ~(IMAP_REOPEN_ALLOW|IMAP_NEWMAIL_PENDING);
  idata->newMailCount = 0;

#if USE_HCACHE
  idata->hcache = imap_hcache_open (idata, NULL);

  if (idata->hcache && !msgbegin)
  {
    uid_validity = mutt_hcache_fetch_raw (idata->hcache, "/UIDVALIDITY", imap_hcache_keylen);
    puidnext = mutt_hcache_fetch_raw (idata->hcache, "/UIDNEXT", imap_hcache_keylen);
    if (puidnext)
    {
      uidnext = *puidnext;
      FREE (&puidnext);
    }
    if (uid_validity && uidnext && *uid_validity == idata->uid_validity)
      evalhc = 1;
    FREE (&uid_validity);
  }
  if (evalhc)
  {
    /* L10N:
       Comparing the cached data with the IMAP server's data */
    mutt_progress_init (&progress, _("Evaluating cache..."),
			MUTT_PROGRESS_MSG, ReadInc, msgend + 1);

    snprintf (buf, sizeof (buf),
      "UID FETCH 1:%u (UID FLAGS)", uidnext - 1);

    imap_cmd_start (idata, buf);

    rc = IMAP_CMD_CONTINUE;
    for (msgno = msgbegin; rc == IMAP_CMD_CONTINUE; msgno++)
    {
      mutt_progress_update (&progress, msgno + 1, -1);

      memset (&h, 0, sizeof (h));
      h.data = safe_calloc (1, sizeof (IMAP_HEADER_DATA));
      do
      {
        mfhrc = 0;

        rc = imap_cmd_step (idata);
        if (rc != IMAP_CMD_CONTINUE)
	{
	  imap_free_header_data (&h.data);
          break;
	}

        /* hole in the header cache */
        if (!evalhc)
          continue;

        if ((mfhrc = msg_fetch_header (ctx, &h, idata->buf, NULL)) == -1)
          continue;
        else if (mfhrc < 0)
	{
	  imap_free_header_data (&h.data);
          break;
	}

        if (!h.data->uid)
        {
          dprint (2, (debugfile, "imap_read_headers: skipping hcache FETCH "
                      "response for unknown message number %d\n", h.sid));
          mfhrc = -1;
          continue;
        }

        idx++;
        ctx->hdrs[idx] = imap_hcache_get (idata, h.data->uid);
        if (ctx->hdrs[idx])
        {
  	  ctx->hdrs[idx]->index = idx;
  	  /* messages which have not been expunged are ACTIVE (borrowed from mh
  	   * folders) */
  	  ctx->hdrs[idx]->active = 1;
          ctx->hdrs[idx]->read = h.data->read;
          ctx->hdrs[idx]->old = h.data->old;
          ctx->hdrs[idx]->deleted = h.data->deleted;
          ctx->hdrs[idx]->flagged = h.data->flagged;
          ctx->hdrs[idx]->replied = h.data->replied;
          ctx->hdrs[idx]->changed = h.data->changed;
          /*  ctx->hdrs[msgno]->received is restored from mutt_hcache_restore */
          ctx->hdrs[idx]->data = (void *) (h.data);

          ctx->msgcount++;
          ctx->size += ctx->hdrs[idx]->content->length;
        }
	else
        {
	  /* bad header in the cache, we'll have to refetch. */
          dprint (3, (debugfile, "bad cache entry at %d, giving up\n", h.sid - 1));
          imap_free_header_data(&h.data);
          evalhc = 0;
          idx--;
        }
      }
      while (rc != IMAP_CMD_OK && mfhrc == -1);
      if (rc == IMAP_CMD_OK)
        break;
      if ((mfhrc < -1) || ((rc != IMAP_CMD_CONTINUE) && (rc != IMAP_CMD_OK)))
      {
        imap_free_header_data (&h.data);
        imap_hcache_close (idata);
	goto error_out_1;
      }
    }
    /* could also look for first null header in case hcache is holey */
    msgbegin = ctx->msgcount;
  }
#endif /* USE_HCACHE */

  mutt_progress_init (&progress, _("Fetching message headers..."),
		      MUTT_PROGRESS_MSG, ReadInc, msgend + 1);

  for (msgno = msgbegin; msgno <= msgend ; msgno++)
  {
    mutt_progress_update (&progress, msgno + 1, -1);

    /* we may get notification of new mail while fetching headers */
    if (msgno + 1 > fetchlast)
    {
      char *cmd;

      fetchlast = msgend + 1;
      safe_asprintf (&cmd, "FETCH %d:%d (UID FLAGS INTERNALDATE RFC822.SIZE %s)",
                     msgno + 1, fetchlast, hdrreq);
      imap_cmd_start (idata, cmd);
      FREE (&cmd);
    }

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

      if ((mfhrc = msg_fetch_header (ctx, &h, idata->buf, fp)) == -1)
	continue;
      else if (mfhrc < 0)
	break;

      if (!ftello (fp))
      {
        dprint (2, (debugfile, "msg_fetch_header: ignoring fetch response with no body\n"));
        mfhrc = -1;
        msgend--;
        continue;
      }

      /* make sure we don't get remnants from older larger message headers */
      fputs ("\n\n", fp);

      idx++;
      if (idx > msgend)
      {
        dprint (1, (debugfile, "imap_read_headers: skipping FETCH response for "
                    "unknown message number %d\n", h.sid));
        mfhrc = -1;
        idx--;
        continue;
      }
      /* May receive FLAGS updates in a separate untagged response (#2935) */
      if (idx < ctx->msgcount)
      {
	dprint (2, (debugfile, "imap_read_headers: message %d is not new\n",
		    h.sid));
        idx--;
	continue;
      }

      ctx->hdrs[idx] = mutt_new_header ();

      ctx->hdrs[idx]->index = h.sid - 1;
      /* messages which have not been expunged are ACTIVE (borrowed from mh
       * folders) */
      ctx->hdrs[idx]->active = 1;
      ctx->hdrs[idx]->read = h.data->read;
      ctx->hdrs[idx]->old = h.data->old;
      ctx->hdrs[idx]->deleted = h.data->deleted;
      ctx->hdrs[idx]->flagged = h.data->flagged;
      ctx->hdrs[idx]->replied = h.data->replied;
      ctx->hdrs[idx]->changed = h.data->changed;
      ctx->hdrs[idx]->received = h.received;
      ctx->hdrs[idx]->data = (void *) (h.data);

      if (maxuid < h.data->uid)
        maxuid = h.data->uid;

      rewind (fp);
      /* NOTE: if Date: header is missing, mutt_read_rfc822_header depends
       *   on h.received being set */
      ctx->hdrs[idx]->env = mutt_read_rfc822_header (fp, ctx->hdrs[idx],
        0, 0);
      /* content built as a side-effect of mutt_read_rfc822_header */
      ctx->hdrs[idx]->content->length = h.content_length;
      ctx->size += h.content_length;

#if USE_HCACHE
      imap_hcache_put (idata, ctx->hdrs[idx]);
#endif /* USE_HCACHE */

      ctx->msgcount++;
    }
    while ((rc != IMAP_CMD_OK) && ((mfhrc == -1) ||
      ((msgno + 1) >= fetchlast)));

    if ((mfhrc < -1) || ((rc != IMAP_CMD_CONTINUE) && (rc != IMAP_CMD_OK)))
    {
      imap_free_header_data (&h.data);
#if USE_HCACHE
      imap_hcache_close (idata);
#endif
      goto error_out_1;
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

  if (maxuid && (status = imap_mboxcache_get (idata, idata->mailbox, 0)) &&
      (status->uidnext < maxuid + 1))
    status->uidnext = maxuid + 1;

#if USE_HCACHE
  mutt_hcache_store_raw (idata->hcache, "/UIDVALIDITY", &idata->uid_validity,
                         sizeof (idata->uid_validity), imap_hcache_keylen);
  if (maxuid && idata->uidnext < maxuid + 1)
  {
    dprint (2, (debugfile, "Overriding UIDNEXT: %u -> %u\n", idata->uidnext, maxuid + 1));
    idata->uidnext = maxuid + 1;
  }
  if (idata->uidnext > 1)
    mutt_hcache_store_raw (idata->hcache, "/UIDNEXT", &idata->uidnext,
			   sizeof (idata->uidnext), imap_hcache_keylen);

  imap_hcache_close (idata);
#endif /* USE_HCACHE */

  if (ctx->msgcount > oldmsgcount)
  {
    mx_alloc_memory(ctx);
    mx_update_context (ctx, ctx->msgcount - oldmsgcount);
  }

  idata->reopen |= IMAP_REOPEN_ALLOW;

  retval = msgend;

error_out_1:
  safe_fclose (&fp);

error_out_0:
  FREE (&hdrreq);

  return retval;
}