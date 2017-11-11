int pop_fetch_message (MESSAGE* msg, CONTEXT* ctx, int msgno)
{
  int ret;
  void *uidl;
  char buf[LONG_STRING];
  char path[_POSIX_PATH_MAX];
  char *m = _("Fetching message...");
  POP_DATA *pop_data = (POP_DATA *)ctx->data;
  POP_CACHE *cache;
  HEADER *h = ctx->hdrs[msgno];

  /* see if we already have the message in our cache */
  cache = &pop_data->cache[h->index % POP_CACHE_LEN];

  if (cache->path)
  {
    if (cache->index == h->index)
    {
      /* yes, so just return a pointer to the message */
      msg->fp = fopen (cache->path, "r");
      if (msg->fp)
	return 0;

      mutt_perror (cache->path);
      mutt_sleep (2);
      return -1;
    }
    else
    {
      /* clear the previous entry */
      unlink (cache->path);
      FREE (&cache->path);
    }
  }

  FOREVER
  {
    if (pop_reconnect (ctx) < 0)
      return -1;

    /* verify that massage index is correct */
    if (h->refno < 0)
    {
      mutt_error _("The message index is incorrect. Try reopening the mailbox.");
      mutt_sleep (2);
      return -1;
    }

    mutt_message (m);

    mutt_mktemp (path);
    msg->fp = safe_fopen (path, "w+");
    if (!msg->fp)
    {
      mutt_perror (path);
      mutt_sleep (2);
      return -1;
    }

    snprintf (buf, sizeof (buf), "RETR %d\r\n", h->refno);

    ret = pop_fetch_data (pop_data, buf, m, fetch_message, msg->fp);
    if (ret == 0)
      break;

    safe_fclose (&msg->fp);
    unlink (path);

    if (ret == -2)
    {
      mutt_error ("%s", pop_data->err_msg);
      mutt_sleep (2);
      return -1;
    }

    if (ret == -3)
    {
      mutt_error _("Can't write message to temporary file!");
      mutt_sleep (2);
      return -1;
    }
  }

  /* Update the header information.  Previously, we only downloaded a
   * portion of the headers, those required for the main display.
   */
  cache->index = h->index;
  cache->path = safe_strdup (path);
  rewind (msg->fp);
  uidl = h->data;
  mutt_free_envelope (&h->env);
  h->env = mutt_read_rfc822_header (msg->fp, h, 0, 0);
  h->data = uidl;
  h->lines = 0;
  fgets (buf, sizeof (buf), msg->fp);
  while (!feof (msg->fp))
  {
    ctx->hdrs[msgno]->lines++;
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
}