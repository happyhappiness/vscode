      mutt_perror _("Can't create filter");
      if (s->flags & M_DISPLAY)
      {
	state_mark_attach (s);
	state_printf (s, _("[-- Can't run %s. --]\n"), command);
      }
      goto bail;
    }
    
    if (s->prefix)
    {
      while (fgets (buffer, sizeof(buffer), fpout) != NULL)
