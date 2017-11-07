int imap_mailbox_state (const char* path, struct mailbox_state* state)
{
  IMAP_DATA* idata;
  IMAP_MBOX mx;
  IMAP_STATUS* status;

  memset (state, 0, sizeof (*state));
  if (imap_parse_path (path, &mx) < 0)
  {
    dprint (1, (debugfile, "imap_mailbox_state: bad path %s\n", path));
    return -1;
  }
  if (!(idata = imap_conn_find (&mx.account, M_IMAP_CONN_NONEW)))
  {
    dprint (2, (debugfile, "imap_mailbox_state: no open connection for %s\n",
		path));
    FREE (&mx.mbox);
    return -1;
  }

  if (idata->ctx && !imap_mxcmp(mx.mbox, idata->mailbox))
  {
    state->new = idata->ctx->new;
    state->messages = idata->ctx->msgcount;
  }
  else if ((status = imap_mboxcache_get (idata, mx.mbox, 0)))
  {
    state->new = status->unseen;
    state->messages = status->messages;
  }

  FREE (&mx.mbox);

  return 0;
}