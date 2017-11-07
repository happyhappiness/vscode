int mh_sync_mailbox (CONTEXT * ctx, int *index_hint)
{
  char path[_POSIX_PATH_MAX], tmp[_POSIX_PATH_MAX];
  int i, j;

  if ((i = mh_check_mailbox(ctx, index_hint)) != 0)
    return i;

  for (i = 0; i < ctx->msgcount; i++)
  {
    if (ctx->hdrs[i]->deleted && (ctx->magic != M_MAILDIR || !option(OPTMAILDIRTRASH)))
    {
      snprintf (path, sizeof (path), "%s/%s", ctx->path, ctx->hdrs[i]->path);
      if (ctx->magic == M_MAILDIR || (option (OPTMHPURGE) && ctx->magic == M_MH))
	unlink (path);
      else if (ctx->magic == M_MH)
      {
	/* MH just moves files out of the way when you delete them */
	if(*ctx->hdrs[i]->path != ',')
	{
	  snprintf (tmp, sizeof (tmp), "%s/,%s", ctx->path, ctx->hdrs[i]->path);
	  unlink (tmp);
	  rename (path, tmp);
	}
	  
      }
    }
    else if (ctx->hdrs[i]->changed || ctx->hdrs[i]->attach_del ||
	     (ctx->magic == M_MAILDIR  && (option (OPTMAILDIRTRASH) || ctx->hdrs[i]->trash) 
	      && (ctx->hdrs[i]->deleted != ctx->hdrs[i]->trash)))
    {
      if (ctx->magic == M_MAILDIR)
      {
	if (maildir_sync_message (ctx, i) == -1)
	  return -1;
      }
      else
      {
	if (mh_sync_message (ctx, i) == -1)
	  return -1;
      }
    }
  }

  if (ctx->magic == M_MH)
    mh_update_sequences (ctx);
  
  /* XXX race condition? */

  maildir_update_mtime(ctx);

  /* adjust indices */

  if (ctx->deleted)
  {
    for (i = 0, j = 0; i < ctx->msgcount; i++)
    {
      if (!ctx->hdrs[i]->deleted || (ctx->magic == M_MAILDIR && option (OPTMAILDIRTRASH)))
	ctx->hdrs[i]->index = j++;
    }
  }

  return 0;
}