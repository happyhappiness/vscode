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