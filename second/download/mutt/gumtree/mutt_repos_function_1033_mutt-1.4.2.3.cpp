int maildir_commit_message (CONTEXT *ctx, MESSAGE *msg, HEADER *hdr)
{
  char subdir[4];
  char suffix[16];
  char path[_POSIX_PATH_MAX];
  char full[_POSIX_PATH_MAX];
  char *s;

  if (safe_fclose (&msg->fp) != 0)
    return -1;
  
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
    snprintf (path, _POSIX_PATH_MAX, "%s/%ld.%d_%d.%s%s", subdir,
	      time (NULL), getpid(), Counter++, NONULL (Hostname), suffix);
    snprintf (full, _POSIX_PATH_MAX, "%s/%s", ctx->path, path);

    dprint (2, (debugfile, "maildir_commit_message (): renaming %s to %s.\n",
		msg->path, full));

    if (safe_rename (msg->path, full) == 0)
    {
      if (hdr) 
	mutt_str_replace (&hdr->path, path);
      FREE (&msg->path);
      return 0;
    }
    else if (errno != EEXIST)
    {
      mutt_perror (ctx->path);
      return -1;
    }
  }
}