static int _maildir_commit_message (CONTEXT * ctx, MESSAGE * msg, HEADER * hdr)
{
  char subdir[4];
  char suffix[16];
  char path[_POSIX_PATH_MAX];
  char full[_POSIX_PATH_MAX];
  char *s;

  if (safe_fsync_close (&msg->fp))
  {
    mutt_perror (_("Could not flush message to disk"));
    return -1;
  }

  /* extract the subdir */
  s = strrchr (msg->path, '/') + 1;
  strfcpy (subdir, s, 4);

  /* extract the flags */
  if ((s = strchr (s, ':')))
    strfcpy (suffix, s, sizeof (suffix));
  else
    suffix[0] = '\0';

  /* construct a new file name. */
  FOREVER
  {
    snprintf (path, _POSIX_PATH_MAX, "%s/%lld.%u_%d.%s%s", subdir,
	      (long long)time (NULL), (unsigned int)getpid (), Counter++,
	      NONULL (Hostname), suffix);
    snprintf (full, _POSIX_PATH_MAX, "%s/%s", ctx->path, path);

    dprint (2, (debugfile, "_maildir_commit_message (): renaming %s to %s.\n",
		msg->path, full));

    if (safe_rename (msg->path, full) == 0)
    {
      if (hdr)
	mutt_str_replace (&hdr->path, path);
      FREE (&msg->path);

      /*
       * Adjust the mtime on the file to match the time at which this
       * message was received.  Currently this is only set when copying
       * messages between mailboxes, so we test to ensure that it is
       * actually set.
       */
      if (msg->received)
      {
	struct utimbuf ut;

	ut.actime = msg->received;
	ut.modtime = msg->received;
	if (utime (full, &ut))
	{
	  mutt_perror (_("_maildir_commit_message(): unable to set time on file"));
	  return -1;
	}
      }

      return 0;
    }
    else if (errno != EEXIST)
    {
      mutt_perror (ctx->path);
      return -1;
    }
  }
}