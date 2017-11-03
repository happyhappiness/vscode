static int maildir_parse_dir (CONTEXT * ctx, struct maildir ***last,
			      const char *subdir, int *count,
			      progress_t *progress)
{
  DIR *dirp;
  struct dirent *de;
  char buf[_POSIX_PATH_MAX];
  int is_old = 0;
  struct maildir *entry;
  HEADER *h;

  if (subdir)
  {
    snprintf (buf, sizeof (buf), "%s/%s", ctx->path, subdir);
    is_old = (mutt_strcmp ("cur", subdir) == 0);
  }
  else
    strfcpy (buf, ctx->path, sizeof (buf));

  if ((dirp = opendir (buf)) == NULL)
    return -1;

  while ((de = readdir (dirp)) != NULL)
  {
    if ((ctx->magic == MUTT_MH && !mh_valid_message (de->d_name))
	|| (ctx->magic == MUTT_MAILDIR && *de->d_name == '.'))
      continue;

    /* FOO - really ignore the return value? */
    dprint (2,
	    (debugfile, "%s:%d: queueing %s\n", __FILE__, __LINE__,
	     de->d_name));

    h = mutt_new_header ();
    h->old = is_old;
    if (ctx->magic == MUTT_MAILDIR)
      maildir_parse_flags (h, de->d_name);

    if (count)
    {
      (*count)++;
      if (!ctx->quiet && progress)
	mutt_progress_update (progress, *count, -1);
    }

    if (subdir)
    {
      char tmp[_POSIX_PATH_MAX];
      snprintf (tmp, sizeof (tmp), "%s/%s", subdir, de->d_name);
      h->path = safe_strdup (tmp);
    }
    else
      h->path = safe_strdup (de->d_name);

    entry = safe_calloc (sizeof (struct maildir), 1);
    entry->h = h;
#ifdef HAVE_DIRENT_D_INO
    entry->inode = de->d_ino;
#endif /* HAVE_DIRENT_D_INO */
    **last = entry;
    *last = &entry->next;
  }

  closedir (dirp);

  return 0;
}