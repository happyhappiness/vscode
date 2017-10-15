    FREE (&msg);

  return msg;
}

/* check for new mail */
int mx_check_mailbox (CONTEXT *ctx, int *index_hint, int lock)
{
  int rc;

  if (ctx)
  {
    if (ctx->locked) lock = 0;

    switch (ctx->magic)
    {
      case M_MBOX:
      case M_MMDF:

	if (lock)
	{
	  mutt_block_signals ();
	  if (mbox_lock_mailbox (ctx, 0, 0) == -1)
	  {
	    mutt_unblock_signals ();
	    return M_LOCKED;
	  }
	}
	
	rc = mbox_check_mailbox (ctx, index_hint);

	if (lock)
	{
	  mutt_unblock_signals ();
	  mbox_unlock_mailbox (ctx);
	}
	
	return rc;


      case M_MH:
	return (mh_check_mailbox (ctx, index_hint));
      case M_MAILDIR:
	return (maildir_check_mailbox (ctx, index_hint));

#ifdef USE_IMAP
      case M_IMAP:
	/* caller expects that mailbox may change */
        imap_allow_reopen (ctx);
	rc = imap_check_mailbox (ctx, index_hint, 0);
        imap_disallow_reopen (ctx);
	return rc;
#endif /* USE_IMAP */

#ifdef USE_POP
      case M_POP:
	return (pop_check_mailbox (ctx, index_hint));
#endif /* USE_POP */
    }
  }

  dprint (1, (debugfile, "mx_check_mailbox: null or invalid context.\n"));
  return (-1);
}

/* return a stream pointer for a message */
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

/* commit a message to a folder */

int mx_commit_message (MESSAGE *msg, CONTEXT *ctx)
{
  int r = 0;

  if (!(msg->write && ctx->append))
  {
    dprint (1, (debugfile, "mx_commit_message(): msg->write = %d, ctx->append = %d\n",
		msg->write, ctx->append));
    return -1;
  }

  switch (msg->magic)
  {
    case M_MMDF:
    {
      if (fputs (MMDF_SEP, msg->fp) == EOF)
	r = -1;
      break;
    }
    
    case M_MBOX:
    {
      if (fputc ('\n', msg->fp) == EOF)
	r = -1;
      break;
    }

#ifdef USE_IMAP
    case M_IMAP:
    {
      if ((r = safe_fclose (&msg->fp)) == 0)
	r = imap_append_message (ctx, msg);
      break;
    }
#endif
    
    case M_MAILDIR:
    {
      r = maildir_commit_message (ctx, msg, NULL);
      break;
    }
    
    case M_MH:
    {
      r = mh_commit_message (ctx, msg, NULL);
      break;
    }
  }
  
  if (r == 0 && (ctx->magic == M_MBOX || ctx->magic == M_MMDF)
      && (fflush (msg->fp) == EOF || fsync (fileno (msg->fp)) == -1))
  {
    mutt_perror _("Can't write message");
    r = -1;
  }
 
  return r;
}

/* close a pointer to a message */
int mx_close_message (MESSAGE **msg)
{
  int r = 0;

  if ((*msg)->magic == M_MH || (*msg)->magic == M_MAILDIR
      || (*msg)->magic == M_IMAP || (*msg)->magic == M_POP)
  {
    r = safe_fclose (&(*msg)->fp);
  }
  else
    (*msg)->fp = NULL;

  if ((*msg)->path)
  {
    dprint (1, (debugfile, "mx_close_message (): unlinking %s\n",
		(*msg)->path));
    unlink ((*msg)->path);
    FREE (&(*msg)->path);
  }

  FREE (msg);		/* __FREE_CHECKED__ */
  return (r);
