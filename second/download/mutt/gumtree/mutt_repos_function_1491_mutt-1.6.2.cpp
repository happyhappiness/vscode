static int _mh_commit_message (CONTEXT * ctx, MESSAGE * msg, HEADER * hdr,
			       short updseq)
{
  DIR *dirp;
  struct dirent *de;
  char *cp, *dep;
  unsigned int n, hi = 0;
  char path[_POSIX_PATH_MAX];
  char tmp[16];

  if (safe_fsync_close (&msg->fp))
  {
    mutt_perror (_("Could not flush message to disk"));
    return -1;
  }

  if ((dirp = opendir (ctx->path)) == NULL)
  {
    mutt_perror (ctx->path);
    return (-1);
  }

  /* figure out what the next message number is */
  while ((de = readdir (dirp)) != NULL)
  {
    dep = de->d_name;
    if (*dep == ',')
      dep++;
    cp = dep;
    while (*cp)
    {
      if (!isdigit ((unsigned char) *cp))
	break;
      cp++;
    }
    if (!*cp)
    {
      n = atoi (dep);
      if (n > hi)
	hi = n;
    }
  }
  closedir (dirp);

  /* 
   * Now try to rename the file to the proper name.
   * 
   * Note: We may have to try multiple times, until we find a free
   * slot.
   */

  FOREVER
  {
    hi++;
    snprintf (tmp, sizeof (tmp), "%d", hi);
    snprintf (path, sizeof (path), "%s/%s", ctx->path, tmp);
    if (safe_rename (msg->path, path) == 0)
    {
      if (hdr)
	mutt_str_replace (&hdr->path, tmp);
      FREE (&msg->path);
      break;
    }
    else if (errno != EEXIST)
    {
      mutt_perror (ctx->path);
      return -1;
    }
  }
  if (updseq)
    mh_sequences_add_one (ctx, hi, !msg->flags.read, msg->flags.flagged,
			  msg->flags.replied);
  return 0;
}