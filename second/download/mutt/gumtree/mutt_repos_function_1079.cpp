static int pop_open_mailbox (CONTEXT *ctx)
{
  int ret;
  char buf[LONG_STRING];
  CONNECTION *conn;
  ACCOUNT acct;
  POP_DATA *pop_data;
  ciss_url_t url;

  if (pop_parse_path (ctx->path, &acct))
  {
    mutt_error (_("%s is an invalid POP path"), ctx->path);
    mutt_sleep (2);
    return -1;
  }

  mutt_account_tourl (&acct, &url);
  url.path = NULL;
  url_ciss_tostring (&url, buf, sizeof (buf), 0);
  conn = mutt_conn_find (NULL, &acct);
  if (!conn)
    return -1;

  FREE (&ctx->path);
  FREE (&ctx->realpath);
  ctx->path = safe_strdup (buf);
  ctx->realpath = safe_strdup (ctx->path);

  pop_data = safe_calloc (1, sizeof (POP_DATA));
  pop_data->conn = conn;
  ctx->data = pop_data;

  if (pop_open_connection (pop_data) < 0)
    return -1;

  conn->data = pop_data;
  pop_data->bcache = mutt_bcache_open (&acct, NULL);

  /* init (hard-coded) ACL rights */
  memset (ctx->rights, 0, sizeof (ctx->rights));
  mutt_bit_set (ctx->rights, MUTT_ACL_SEEN);
  mutt_bit_set (ctx->rights, MUTT_ACL_DELETE);
#if USE_HCACHE
  /* flags are managed using header cache, so it only makes sense to
   * enable them in that case */
  mutt_bit_set (ctx->rights, MUTT_ACL_WRITE);
#endif

  FOREVER
  {
    if (pop_reconnect (ctx) < 0)
      return -1;

    ctx->size = pop_data->size;

    mutt_message _("Fetching list of messages...");

    ret = pop_fetch_headers (ctx);

    if (ret >= 0)
      return 0;

    if (ret < -1)
    {
      mutt_sleep (2);
      return -1;
    }
  }
}