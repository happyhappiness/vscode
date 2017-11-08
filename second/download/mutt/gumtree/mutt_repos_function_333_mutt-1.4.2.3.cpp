int mx_get_magic (const char *path)
{
  struct stat st;
  int magic = 0;
  char tmp[_POSIX_PATH_MAX];
  FILE *f;

#ifdef USE_IMAP
  if(mx_is_imap(path))
    return M_IMAP;
#endif /* USE_IMAP */

#ifdef USE_POP
  if (mx_is_pop (path))
    return M_POP;
#endif /* USE_POP */

  if (stat (path, &st) == -1)
  {
    dprint (1, (debugfile, "mx_get_magic(): unable to stat %s: %s (errno %d).\n",
		path, strerror (errno), errno));
    return (-1);
  }

  if (S_ISDIR (st.st_mode))
  {
    /* check for maildir-style mailbox */

    snprintf (tmp, sizeof (tmp), "%s/cur", path);
    if (stat (tmp, &st) == 0 && S_ISDIR (st.st_mode))
      return (M_MAILDIR);

    /* check for mh-style mailbox */

    snprintf (tmp, sizeof (tmp), "%s/.mh_sequences", path);
    if (access (tmp, F_OK) == 0)
      return (M_MH);

    snprintf (tmp, sizeof (tmp), "%s/.xmhcache", path);
    if (access (tmp, F_OK) == 0)
      return (M_MH);
    
    snprintf (tmp, sizeof (tmp), "%s/.mew_cache", path);
    if (access (tmp, F_OK) == 0)
      return (M_MH);

    snprintf (tmp, sizeof (tmp), "%s/.mew-cache", path);
    if (access (tmp, F_OK) == 0)
      return (M_MH);

    /* 
     * ok, this isn't an mh folder, but mh mode can be used to read
     * Usenet news from the spool. ;-) 
     */

    snprintf (tmp, sizeof (tmp), "%s/.overview", path);
    if (access (tmp, F_OK) == 0)
      return (M_MH);

  }
  else if (st.st_size == 0)
  {
    /* hard to tell what zero-length files are, so assume the default magic */
    if (DefaultMagic == M_MBOX || DefaultMagic == M_MMDF)
      return (DefaultMagic);
    else
      return (M_MBOX);
  }
  else if ((f = fopen (path, "r")) != NULL)
  {
#ifndef BUFFY_SIZE
    struct utimbuf times;
#endif

    fgets (tmp, sizeof (tmp), f);
    if (mutt_strncmp ("From ", tmp, 5) == 0)
      magic = M_MBOX;
    else if (mutt_strcmp (MMDF_SEP, tmp) == 0)
      magic = M_MMDF;
    safe_fclose (&f);
#ifndef BUFFY_SIZE
    /* need to restore the times here, the file was not really accessed,
     * only the type was accessed.  This is important, because detection
     * of "new mail" depends on those times set correctly.
     */
    times.actime = st.st_atime;
    times.modtime = st.st_mtime;
    utime (path, &times);
#endif
  }
  else
  {
    dprint (1, (debugfile, "mx_get_magic(): unable to open file %s for reading.\n",
		path));
    mutt_perror (path);
    return (-1);
  }

  return (magic);
}