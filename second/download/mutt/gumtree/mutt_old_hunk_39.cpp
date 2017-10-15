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

int imap_fetch_message (MESSAGE *msg, CONTEXT *ctx, int msgno)
{
  IMAP_DATA* idata;
  HEADER* h;
  char buf[LONG_STRING];
  char path[_POSIX_PATH_MAX];
  char *pc;
  long bytes;
  int uid;
  int cacheno;
  IMAP_CACHE *cache;
  int read;
  int rc;
  /* Sam's weird courier server returns an OK response even when FETCH
   * fails. Thanks Sam. */
  short fetched = 0;

  idata = (IMAP_DATA*) ctx->data;
  h = ctx->hdrs[msgno];

  /* see if we already have the message in our cache */
  cacheno = HEADER_DATA(h)->uid % IMAP_CACHE_LEN;
  cache = &idata->cache[cacheno];

  if (cache->path)
  {
    if (cache->uid == HEADER_DATA(h)->uid)
    {
      /* yes, so just return a pointer to the message */
      if (!(msg->fp = fopen (cache->path, "r")))
      {
	mutt_perror (cache->path);
	return (-1);
      }
      return 0;
    }
    else
    {
      /* clear the previous entry */
      unlink (cache->path);
      FREE (&cache->path);
    }
  }

  if (!isendwin())
    mutt_message _("Fetching message...");

  cache->uid = HEADER_DATA(h)->uid;
  mutt_mktemp (path);
  cache->path = safe_strdup (path);
  if (!(msg->fp = safe_fopen (path, "w+")))
  {
    safe_free ((void**) &cache->path);
    return -1;
  }

  /* mark this header as currently inactive so the command handler won't
   * also try to update it. HACK until all this code can be moved into the
   * command handler */
  h->active = 0;
  
  snprintf (buf, sizeof (buf), "UID FETCH %d %s", HEADER_DATA(h)->uid,
	    (mutt_bit_isset (idata->capabilities, IMAP4REV1) ?
	     (option (OPTIMAPPEEK) ? "BODY.PEEK[]" : "BODY[]") :
	     "RFC822"));

  imap_cmd_start (idata, buf);
  do
  {
    if ((rc = imap_cmd_step (idata)) != IMAP_CMD_CONTINUE)
      break;

    pc = idata->cmd.buf;
    pc = imap_next_word (pc);
    pc = imap_next_word (pc);

    if (!ascii_strncasecmp ("FETCH", pc, 5))
    {
      while (*pc)
