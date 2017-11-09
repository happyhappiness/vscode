int mh_sync_mailbox (CONTEXT * ctx, int *index_hint)
{
  char path[_POSIX_PATH_MAX], tmp[_POSIX_PATH_MAX];
  int i, j;
#if USE_HCACHE
  header_cache_t *hc = NULL;
#endif /* USE_HCACHE */
  char msgbuf[STRING];
  progress_t progress;

  if (ctx->magic == MUTT_MH)
    i = mh_check_mailbox (ctx, index_hint);
  else 
    i = maildir_check_mailbox (ctx, index_hint);
      
  if (i != 0)
    return i;

#if USE_HCACHE
  if (ctx->magic == MUTT_MAILDIR || ctx->magic == MUTT_MH)
    hc = mutt_hcache_open(HeaderCache, ctx->path, NULL);
#endif /* USE_HCACHE */

  if (!ctx->quiet)
  {
    snprintf (msgbuf, sizeof (msgbuf), _("Writing %s..."), ctx->path);
    mutt_progress_init (&progress, msgbuf, MUTT_PROGRESS_MSG, WriteInc, ctx->msgcount);
  }

  for (i = 0; i < ctx->msgcount; i++)
  {
    if (!ctx->quiet)
      mutt_progress_update (&progress, i, -1);

    if (ctx->hdrs[i]->deleted
	&& (ctx->magic != MUTT_MAILDIR || !option (OPTMAILDIRTRASH)))
    {
      snprintf (path, sizeof (path), "%s/%s", ctx->path, ctx->hdrs[i]->path);
      if (ctx->magic == MUTT_MAILDIR
	  || (option (OPTMHPURGE) && ctx->magic == MUTT_MH))
      {
#if USE_HCACHE
        if (ctx->magic == MUTT_MAILDIR)
          mutt_hcache_delete (hc, ctx->hdrs[i]->path + 3, &maildir_hcache_keylen);
	else if (ctx->magic == MUTT_MH)
	  mutt_hcache_delete (hc, ctx->hdrs[i]->path, strlen);
#endif /* USE_HCACHE */
	unlink (path);
      }
      else if (ctx->magic == MUTT_MH)
      {
	/* MH just moves files out of the way when you delete them */
	if (*ctx->hdrs[i]->path != ',')
	{
	  snprintf (tmp, sizeof (tmp), "%s/,%s", ctx->path,
		    ctx->hdrs[i]->path);
	  unlink (tmp);
	  rename (path, tmp);
	}

      }
    }
    else if (ctx->hdrs[i]->changed || ctx->hdrs[i]->attach_del ||
	     ctx->hdrs[i]->xlabel_changed ||
	     (ctx->magic == MUTT_MAILDIR
	      && (option (OPTMAILDIRTRASH) || ctx->hdrs[i]->trash)
	      && (ctx->hdrs[i]->deleted != ctx->hdrs[i]->trash)))
    {
      if (ctx->magic == MUTT_MAILDIR)
      {
	if (maildir_sync_message (ctx, i) == -1)
	  goto err;
      }
      else
      {
	if (mh_sync_message (ctx, i) == -1)
	  goto err;
      }
    }

#if USE_HCACHE
    if (ctx->hdrs[i]->changed)
    {
      if (ctx->magic == MUTT_MAILDIR)
	mutt_hcache_store (hc, ctx->hdrs[i]->path + 3, ctx->hdrs[i],
			   0, &maildir_hcache_keylen, MUTT_GENERATE_UIDVALIDITY);
      else if (ctx->magic == MUTT_MH)
	mutt_hcache_store (hc, ctx->hdrs[i]->path, ctx->hdrs[i], 0, strlen, MUTT_GENERATE_UIDVALIDITY);
    }
#endif

  }

#if USE_HCACHE
  if (ctx->magic == MUTT_MAILDIR || ctx->magic == MUTT_MH)
    mutt_hcache_close (hc);
#endif /* USE_HCACHE */

  if (ctx->magic == MUTT_MH)
    mh_update_sequences (ctx);

  /* XXX race condition? */

  maildir_update_mtime (ctx);

  /* adjust indices */

  if (ctx->deleted)
  {
    for (i = 0, j = 0; i < ctx->msgcount; i++)
    {
      if (!ctx->hdrs[i]->deleted
	  || (ctx->magic == MUTT_MAILDIR && option (OPTMAILDIRTRASH)))
	ctx->hdrs[i]->index = j++;
    }
  }

  return 0;

err:
#if USE_HCACHE
  if (ctx->magic == MUTT_MAILDIR || ctx->magic == MUTT_MH)
    mutt_hcache_close (hc);
#endif /* USE_HCACHE */
  return -1;
}