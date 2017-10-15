				      fileno(fpin), -1, -1);
    }

    if (thepid < 0)
    {
      mutt_perror _("Can't create filter");
      if (s->flags & MUTT_DISPLAY)
      {
	state_mark_attach (s);
	state_printf (s, _("[-- Can't run %s. --]\n"), command);
      }
      rc = -1;
      goto bail;
