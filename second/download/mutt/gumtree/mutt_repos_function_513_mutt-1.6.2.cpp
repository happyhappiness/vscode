static int mx_open_mailbox_append (CONTEXT *ctx, int flags)
{
  struct stat sb;

  ctx->append = 1;

#ifdef USE_IMAP
  
  if(mx_is_imap(ctx->path))  
    return imap_open_mailbox_append (ctx);

#endif
  
  if(stat(ctx->path, &sb) == 0)
  {
    ctx->magic = mx_get_magic (ctx->path);
    
    switch (ctx->magic)
    {
      case 0:
	mutt_error (_("%s is not a mailbox."), ctx->path);
	/* fall through */
      case -1:
	return (-1);
    }
  }
  else if (errno == ENOENT)
  {
    ctx->magic = DefaultMagic;

    if (ctx->magic == M_MH || ctx->magic == M_MAILDIR)
    {
      char tmp[_POSIX_PATH_MAX];

      if (mkdir (ctx->path, S_IRWXU))
      {
	mutt_perror (ctx->path);
	return (-1);
      }

      if (ctx->magic == M_MAILDIR)
      {
	snprintf (tmp, sizeof (tmp), "%s/cur", ctx->path);
	if (mkdir (tmp, S_IRWXU))
	{
	  mutt_perror (tmp);
	  rmdir (ctx->path);
	  return (-1);
	}

	snprintf (tmp, sizeof (tmp), "%s/new", ctx->path);
	if (mkdir (tmp, S_IRWXU))
	{
	  mutt_perror (tmp);
	  snprintf (tmp, sizeof (tmp), "%s/cur", ctx->path);
	  rmdir (tmp);
	  rmdir (ctx->path);
	  return (-1);
	}
	snprintf (tmp, sizeof (tmp), "%s/tmp", ctx->path);
	if (mkdir (tmp, S_IRWXU))
	{
	  mutt_perror (tmp);
	  snprintf (tmp, sizeof (tmp), "%s/cur", ctx->path);
	  rmdir (tmp);
	  snprintf (tmp, sizeof (tmp), "%s/new", ctx->path);
	  rmdir (tmp);
	  rmdir (ctx->path);
	  return (-1);
	}
      }
      else
      {
	int i;

	snprintf (tmp, sizeof (tmp), "%s/.mh_sequences", ctx->path);
	if ((i = creat (tmp, S_IRWXU)) == -1)
	{
	  mutt_perror (tmp);
	  rmdir (ctx->path);
	  return (-1);
	}
	close (i);
      }
    }
  }
  else
  {
    mutt_perror (ctx->path);
    return (-1);
  }

  switch (ctx->magic)
  {
    case M_MBOX:
    case M_MMDF:
    if ((ctx->fp = safe_fopen (ctx->path, flags & M_NEWFOLDER ? "w" : "a")) == NULL ||
	  mbox_lock_mailbox (ctx, 1, 1) != 0)
      {
	if (!ctx->fp)
	  mutt_perror (ctx->path);
	else
	{
	  mutt_error (_("Couldn't lock %s\n"), ctx->path);
	  safe_fclose (&ctx->fp);
	}
	return (-1);
      }
      fseek (ctx->fp, 0, 2);
      break;

    case M_MH:
    case M_MAILDIR:
      /* nothing to do */
      break;

    default:
      return (-1);
  }

  return 0;
}