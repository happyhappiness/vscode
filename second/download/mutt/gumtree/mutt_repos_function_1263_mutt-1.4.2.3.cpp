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
      {
	pc = imap_next_word (pc);
	if (pc[0] == '(')
	  pc++;
	if (ascii_strncasecmp ("UID", pc, 3) == 0)
	{
	  pc = imap_next_word (pc);
	  uid = atoi (pc);
	  if (uid != HEADER_DATA(h)->uid)
	    mutt_error (_("The message index is incorrect. Try reopening the mailbox."));
	}
	else if ((ascii_strncasecmp ("RFC822", pc, 6) == 0) ||
		 (ascii_strncasecmp ("BODY[]", pc, 6) == 0))
	{
	  pc = imap_next_word (pc);
	  if (imap_get_literal_count(pc, &bytes) < 0)
	  {
	    imap_error ("imap_fetch_message()", buf);
	    goto bail;
	  }
	  if (imap_read_literal (msg->fp, idata, bytes) < 0)
	    goto bail;
	  /* pick up trailing line */
	  if ((rc = imap_cmd_step (idata)) != IMAP_CMD_CONTINUE)
	    goto bail;
	  pc = idata->cmd.buf;

	  fetched = 1;
	}
	/* UW-IMAP will provide a FLAGS update here if the FETCH causes a
	 * change (eg from \Unseen to \Seen).
	 * Uncommitted changes in mutt take precedence. If we decide to
	 * incrementally update flags later, this won't stop us syncing */
	else if ((ascii_strncasecmp ("FLAGS", pc, 5) == 0) && !h->changed)
	{
	  if ((pc = imap_set_flags (idata, h, pc)) == NULL)
	    goto bail;
	}
      }
    }
  }
  while (rc == IMAP_CMD_CONTINUE);

  /* see comment before command start. */
  h->active = 1;

  if (rc != IMAP_CMD_OK)
    goto bail;

  if (!fetched || !imap_code (idata->cmd.buf))
    goto bail;
    
  /* Update the header information.  Previously, we only downloaded a
   * portion of the headers, those required for the main display.
   */
  rewind (msg->fp);
  /* It may be that the Status header indicates a message is read, but the
   * IMAP server doesn't know the message has been \Seen. So we capture
   * the server's notion of 'read' and if it differs from the message info
   * picked up in mutt_read_rfc822_header, we mark the message (and context
   * changed). Another possiblity: ignore Status on IMAP?*/
  read = h->read;
  /* I hate do this here, since it's so low-level, but I'm not sure where
   * I can abstract it. Problem: the id and subj hashes lose their keys when
   * mutt_free_envelope gets called, but keep their spots in the hash. This
   * confuses threading. Alternatively we could try to merge the new
   * envelope into the old one. Also messy and lowlevel. */
  if (ctx->id_hash && h->env->message_id)
    hash_delete (ctx->id_hash, h->env->message_id, h, NULL);
  mutt_free_envelope (&h->env);
  h->env = mutt_read_rfc822_header (msg->fp, h, 0, 0);
  if (ctx->id_hash && h->env->message_id)
    hash_insert (ctx->id_hash, h->env->message_id, h, 0);

  /* see above. We want the new status in h->read, so we unset it manually
   * and let mutt_set_flag set it correctly, updating context. */
  if (read != h->read)
  {
    h->read = read;
    mutt_set_flag (ctx, h, M_NEW, read);
  }

  h->lines = 0;
  fgets (buf, sizeof (buf), msg->fp);
  while (!feof (msg->fp))
  {
    h->lines++;
    fgets (buf, sizeof (buf), msg->fp);
  }

  h->content->length = ftell (msg->fp) - h->content->offset;

  /* This needs to be done in case this is a multipart message */
#ifdef HAVE_PGP
  h->pgp = pgp_query (h->content);
#endif /* HAVE_PGP */

  mutt_clear_error();
  rewind (msg->fp);

  return 0;

bail:
  safe_fclose (&msg->fp);
  if (cache->path)
  {
    unlink (cache->path);
    FREE (&cache->path);
  }

  return -1;
}