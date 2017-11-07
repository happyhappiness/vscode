int imap_close_mailbox (CONTEXT* ctx)
{
  IMAP_DATA* idata;
  int i;

  idata = (IMAP_DATA*) ctx->data;
  /* Check to see if the mailbox is actually open */
  if (!idata)
    return 0;

  if (ctx == idata->ctx)
  {
    if (idata->status != IMAP_FATAL && idata->state >= IMAP_SELECTED)
    {
      /* mx_close_mailbox won't sync if there are no deleted messages
       * and the mailbox is unchanged, so we may have to close here */
      if (!ctx->deleted)
        imap_exec (idata, "CLOSE", IMAP_CMD_QUEUE);
      idata->state = IMAP_AUTHENTICATED;
    }

    idata->reopen &= IMAP_REOPEN_ALLOW;
    FREE (&(idata->mailbox));
    mutt_free_list (&idata->flags);
    idata->ctx = NULL;
  }

  /* free IMAP part of headers */
  for (i = 0; i < ctx->msgcount; i++)
    /* mailbox may not have fully loaded */
    if (ctx->hdrs[i] && ctx->hdrs[i]->data)
      imap_free_header_data ((IMAP_HEADER_DATA**)&(ctx->hdrs[i]->data));

  for (i = 0; i < IMAP_CACHE_LEN; i++)
  {
    if (idata->cache[i].path)
    {
      unlink (idata->cache[i].path);
      FREE (&idata->cache[i].path);
    }
  }

  mutt_bcache_close (&idata->bcache);

  return 0;
}