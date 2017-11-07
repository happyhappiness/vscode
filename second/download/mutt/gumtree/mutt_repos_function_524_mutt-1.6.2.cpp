MESSAGE *mx_open_message (CONTEXT *ctx, int msgno)
{
  MESSAGE *msg;
  
  msg = safe_calloc (1, sizeof (MESSAGE));
  switch (msg->magic = ctx->magic)
  {
    case M_MBOX:
    case M_MMDF:
      msg->fp = ctx->fp;
      break;

    case M_MH:
    case M_MAILDIR:
    {
      HEADER *cur = ctx->hdrs[msgno];
      char path[_POSIX_PATH_MAX];
      
      snprintf (path, sizeof (path), "%s/%s", ctx->path, cur->path);
      
      if ((msg->fp = fopen (path, "r")) == NULL && errno == ENOENT &&
	  ctx->magic == M_MAILDIR)
	msg->fp = maildir_open_find_message (ctx->path, cur->path);
      
      if (msg->fp == NULL)
      {
	mutt_perror (path);
	dprint (1, (debugfile, "mx_open_message: fopen: %s: %s (errno %d).\n",
		    path, strerror (errno), errno));
	FREE (&msg);
      }
    }
    break;
    
#ifdef USE_IMAP
    case M_IMAP:
    {
      if (imap_fetch_message (msg, ctx, msgno) != 0)
	FREE (&msg);
      break;
    }
#endif /* USE_IMAP */

#ifdef USE_POP
    case M_POP:
    {
      if (pop_fetch_message (msg, ctx, msgno) != 0)
	FREE (&msg);
      break;
    }
#endif /* USE_POP */

    default:
      dprint (1, (debugfile, "mx_open_message(): function not implemented for mailbox type %d.\n", ctx->magic));
      FREE (&msg);
      break;
  }
  return (msg);
}