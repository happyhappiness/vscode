int mx_get_magic (const char *path)
{
  struct stat st;
  int magic = 0;
  char tmp[_POSIX_PATH_MAX];
  FILE *f;

#ifdef USE_IMAP
  if(mx_is_imap(path))
    return MUTT_IMAP;
#endif /* USE_IMAP */

#ifdef USE_POP
  if (mx_is_pop (path))
    return MUTT_POP;
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
    if (mx_is_maildir (path))
      return MUTT_MAILDIR;

    /* check for mh-style mailbox */
    if (mx_is_mh (path))
      return MUTT_MH;
  }
  else if (st.st_size == 0)
  {
    /* hard to tell what zero-length files are, so assume the default magic */
    if (DefaultMagic == MUTT_MBOX || DefaultMagic == MUTT_MMDF)
      return (DefaultMagic);
    else
      return (MUTT_MBOX);
  }
  else if ((f = fopen (path, "r")) != NULL)
  {
    struct utimbuf times;

    fgets (tmp, sizeof (tmp), f);
    if (mutt_strncmp ("From ", tmp, 5) == 0)
      magic = MUTT_MBOX;
    else if (mutt_strcmp (MMDF_SEP, tmp) == 0)
      magic = MUTT_MMDF;
    safe_fclose (&f);

    if (!option(OPTCHECKMBOXSIZE))
    {
      /* need to restore the times here, the file was not really accessed,
       * only the type was accessed.  This is important, because detection
       * of "new mail" depends on those times set correctly.
       */
      times.actime = st.st_atime;
      times.modtime = st.st_mtime;
      utime (path, &times);
    }
  }
  else
  {
    dprint (1, (debugfile, "mx_get_magic(): unable to open file %s for reading.\n",
		path));
    return (-1);
  }

  return (magic);
}