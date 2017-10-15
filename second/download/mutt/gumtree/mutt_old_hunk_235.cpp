    /* ... except for certain folder formats which need "unsorted" 
     * sort order in order to synchronize folders.
     * 
     * MH and maildir are safe.  mbox-style seems to need re-sorting,
     * at least with the new threading code.
     */
    if (purge || (ctx->magic != M_MAILDIR && ctx->magic != M_MH))
    {
      /* IMAP does this automatically after handling EXPUNGE */
      if (ctx->magic != M_IMAP)
      {
	mx_update_tables (ctx, 1);
	mutt_sort_headers (ctx, 1); /* rethread from scratch */
      }
    }
  }

  return (rc);
}


/* {maildir,mh}_open_new_message are in mh.c. */

static int mbox_open_new_message (MESSAGE *msg, CONTEXT *dest, HEADER *hdr)
{
  msg->fp = dest->fp;
  return 0;
}

#ifdef USE_IMAP
static int imap_open_new_message (MESSAGE *msg, CONTEXT *dest, HEADER *hdr)
{
  char tmp[_POSIX_PATH_MAX];

  mutt_mktemp (tmp, sizeof (tmp));
  if ((msg->fp = safe_fopen (tmp, "w")) == NULL)
  {
    mutt_perror (tmp);
    return (-1);
  }
  msg->path = safe_strdup(tmp);
  return 0;
}
#endif

/* args:
 *	dest	destination mailbox
 *	hdr	message being copied (required for maildir support, because
 *		the filename depends on the message flags)
 */
MESSAGE *mx_open_new_message (CONTEXT *dest, HEADER *hdr, int flags)
{
  MESSAGE *msg;
  int (*func) (MESSAGE *, CONTEXT *, HEADER *);
  ADDRESS *p = NULL;

  switch (dest->magic)
  {
    case M_MMDF:
    case M_MBOX:
      func = mbox_open_new_message;
      break;
    case M_MAILDIR:
      func = maildir_open_new_message;
      break;
    case M_MH:
      func = mh_open_new_message;
      break;
#ifdef USE_IMAP
    case M_IMAP:
      func = imap_open_new_message;
      break;
#endif
    default:
      dprint (1, (debugfile, "mx_open_new_message(): function unimplemented for mailbox type %d.\n",
		  dest->magic));
      return (NULL);
  }

  msg = safe_calloc (1, sizeof (MESSAGE));
  msg->magic = dest->magic;
  msg->write = 1;

  if (hdr)
  {
    msg->flags.flagged = hdr->flagged;
    msg->flags.replied = hdr->replied;
    msg->flags.read    = hdr->read;
    msg->flags.draft   = (flags & M_SET_DRAFT) ? 1 : 0;
    msg->received = hdr->received;
  }

  if(msg->received == 0)
    time(&msg->received);
  
  if (func (msg, dest, hdr) == 0)
  {
    if (dest->magic == M_MMDF)
      fputs (MMDF_SEP, msg->fp);

    if ((msg->magic == M_MBOX || msg->magic ==  M_MMDF) &&
	flags & M_ADD_FROM)
    {
      if (hdr)
      {
	if (hdr->env->return_path)
	  p = hdr->env->return_path;
	else if (hdr->env->sender)
