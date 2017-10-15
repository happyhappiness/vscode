    /* ... except for certain folder formats which need "unsorted" 
     * sort order in order to synchronize folders.
     * 
     * MH and maildir are safe.  mbox-style seems to need re-sorting,
     * at least with the new threading code.
     */
    if (purge || (ctx->magic != MUTT_MAILDIR && ctx->magic != MUTT_MH))
    {
      /* IMAP does this automatically after handling EXPUNGE */
      if (ctx->magic != MUTT_IMAP)
      {
	mx_update_tables (ctx, 1);
	mutt_sort_headers (ctx, 1); /* rethread from scratch */
      }
    }
  }

  return (rc);
}

/* args:
 *	dest	destination mailbox
 *	hdr	message being copied (required for maildir support, because
 *		the filename depends on the message flags)
 */
MESSAGE *mx_open_new_message (CONTEXT *dest, HEADER *hdr, int flags)
{
  ADDRESS *p = NULL;
  MESSAGE *msg;

  if (!dest->mx_ops->open_new_msg)
  {
      dprint (1, (debugfile, "mx_open_new_message(): function unimplemented for mailbox type %d.\n",
              dest->magic));
      return NULL;
  }

  msg = safe_calloc (1, sizeof (MESSAGE));
  msg->write = 1;

  if (hdr)
  {
    msg->flags.flagged = hdr->flagged;
    msg->flags.replied = hdr->replied;
    msg->flags.read    = hdr->read;
    msg->flags.draft   = (flags & MUTT_SET_DRAFT) ? 1 : 0;
    msg->received = hdr->received;
  }

  if(msg->received == 0)
    time(&msg->received);

  if (dest->mx_ops->open_new_msg (msg, dest, hdr) == 0)
  {
    if (dest->magic == MUTT_MMDF)
      fputs (MMDF_SEP, msg->fp);

    if ((dest->magic == MUTT_MBOX || dest->magic ==  MUTT_MMDF) &&
	flags & MUTT_ADD_FROM)
    {
      if (hdr)
      {
	if (hdr->env->return_path)
	  p = hdr->env->return_path;
	else if (hdr->env->sender)
