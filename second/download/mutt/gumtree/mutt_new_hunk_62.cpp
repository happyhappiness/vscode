    /* we're not connected yet - skip mail folder creation */
    if (!mx_is_imap (fpath))
#endif
    if (stat (fpath, &sb) == -1 && errno == ENOENT)
    {
      snprintf (msg, sizeof (msg), _("%s does not exist. Create it?"), Maildir);
      if (mutt_yesorno (msg, M_YES) == M_YES)
      {
	if (mkdir (fpath, 0700) == -1 && errno != EEXIST)
	  mutt_error ( _("Can't create %s: %s."), Maildir, strerror (errno));
      }
    }
  }
