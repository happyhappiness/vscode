static int maildir_sync_message (CONTEXT * ctx, int msgno)
{
  HEADER *h = ctx->hdrs[msgno];

  if (h->attach_del || h->xlabel_changed ||
      (h->env && (h->env->refs_changed || h->env->irt_changed)))
  {
    /* when doing attachment deletion/rethreading, fall back to the MH case. */
    if (mh_rewrite_message (ctx, msgno) != 0)
      return (-1);
  }
  else
  {
    /* we just have to rename the file. */

    char newpath[_POSIX_PATH_MAX];
    char partpath[_POSIX_PATH_MAX];
    char fullpath[_POSIX_PATH_MAX];
    char oldpath[_POSIX_PATH_MAX];
    char suffix[16];
    char *p;

    if ((p = strrchr (h->path, '/')) == NULL)
    {
      dprint (1,
	      (debugfile,
	       "maildir_sync_message: %s: unable to find subdir!\n",
	       h->path));
      return (-1);
    }
    p++;
    strfcpy (newpath, p, sizeof (newpath));

    /* kill the previous flags */
    if ((p = strchr (newpath, ':')) != NULL)
      *p = 0;

    maildir_flags (suffix, sizeof (suffix), h);

    snprintf (partpath, sizeof (partpath), "%s/%s%s",
	      (h->read || h->old) ? "cur" : "new", newpath, suffix);
    snprintf (fullpath, sizeof (fullpath), "%s/%s", ctx->path, partpath);
    snprintf (oldpath, sizeof (oldpath), "%s/%s", ctx->path, h->path);

    if (mutt_strcmp (fullpath, oldpath) == 0)
    {
      /* message hasn't really changed */
      return 0;
    }

    /* record that the message is possibly marked as trashed on disk */
    h->trash = h->deleted;

    if (rename (oldpath, fullpath) != 0)
    {
      mutt_perror ("rename");
      return (-1);
    }
    mutt_str_replace (&h->path, partpath);
  }
  return (0);
}