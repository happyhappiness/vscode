    else
    {
      mutt_copy_stream (fpout, s->fpout);
      /* Check for stderr messages */
      if (fgets (buffer, sizeof(buffer), fperr))
      {
	if (s->flags & M_DISPLAY)
	{
	  state_mark_attach (s);
	  state_printf (s, _("[-- Autoview stderr of %s --]\n"), 
			command);
	}
	
