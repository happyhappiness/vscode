
  if (filter)
  {
    snprintf (warning, sizeof (warning),
	      _("WARNING!  You are about to overwrite %s, continue?"),
	      body->filename);
    if (mutt_yesorno (warning, MUTT_NO) != MUTT_YES) {
      mutt_window_clearline (MuttMessageWindow, 0);
      return;
    }
    mutt_mktemp (tfile, sizeof (tfile));
  }
  else
    tfile[0] = 0;
