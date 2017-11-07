void imap_close_mailbox (CONTEXT* ctx)
{
  IMAP_DATA* idata;
  int i;

  idata = (IMAP_DATA*) ctx->data;
  /* Check to see if the mailbox is actually open */
  if (!idata)
    return;

  if ((idata->status != IMAP_FATAL) &&
      (idata->state == IMAP_SELECTED) &&
      (ctx == idata->ctx))
  {
    if (!(idata->noclose) && imap_exec (idata, "CLOSE", 0))
      mutt_error (_("CLOSE failed"));

    idata->reopen &= IMAP_REOPEN_ALLOW;
    idata->state = IMAP_AUTHENTICATED;
    FREE (&(idata->mailbox));
    mutt_free_list (&idata->flags);
  }

  /* free IMAP part of headers */
  for (i = 0; i < ctx->msgcount; i++)
    imap_free_header_data (&(ctx->hdrs[i]->data));

  for (i = 0; i < IMAP_CACHE_LEN; i++)
  {
    if (idata->cache[i].path)
    {
      unlink (idata->cache[i].path);
      safe_free ((void **) &idata->cache[i].path);
    }
  }
}