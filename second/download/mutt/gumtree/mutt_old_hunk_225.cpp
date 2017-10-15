  if (mbox_lock_mailbox (ctx, 0, 1) == -1)
  {
    mutt_unblock_signals ();
    return (-1);
  }

  if (ctx->magic == M_MBOX)
    rc = mbox_parse_mailbox (ctx);
  else if (ctx->magic == M_MMDF)
    rc = mmdf_parse_mailbox (ctx);
  else
    rc = -1;

  mbox_unlock_mailbox (ctx);
  mutt_unblock_signals ();
  return (rc);
}

/* return 1 if address lists are strictly identical */
static int strict_addrcmp (const ADDRESS *a, const ADDRESS *b)
{
  while (a && b)
  {
    if (mutt_strcmp (a->mailbox, b->mailbox) ||
