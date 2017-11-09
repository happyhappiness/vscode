static int autoview_handler (BODY *a, STATE *s)
{
  rfc1524_entry *entry = rfc1524_new_entry ();
  char buffer[LONG_STRING];
  char type[STRING];
  char command[LONG_STRING];
  char tempfile[_POSIX_PATH_MAX] = "";
  char *fname;
  FILE *fpin = NULL;
  FILE *fpout = NULL;
  FILE *fperr = NULL;
  int piped = FALSE;
  pid_t thepid;
  int rc = 0;

  snprintf (type, sizeof (type), "%s/%s", TYPE (a), a->subtype);
  rfc1524_mailcap_lookup (a, type, entry, MUTT_AUTOVIEW);

  fname = safe_strdup (a->filename);
  mutt_sanitize_filename (fname, 1);
  rfc1524_expand_filename (entry->nametemplate, fname, tempfile, sizeof (tempfile));
  FREE (&fname);

  if (entry->command)
  {
    strfcpy (command, entry->command, sizeof (command));

    /* rfc1524_expand_command returns 0 if the file is required */
    piped = rfc1524_expand_command (a, tempfile, type, command, sizeof (command));

    if (s->flags & MUTT_DISPLAY)
    {
      state_mark_attach (s);
      state_printf (s, _("[-- Autoview using %s --]\n"), command);
      mutt_message(_("Invoking autoview command: %s"),command);
    }

    if ((fpin = safe_fopen (tempfile, "w+")) == NULL)
    {
      mutt_perror ("fopen");
      rfc1524_free_entry (&entry);
      return -1;
    }
    
    mutt_copy_bytes (s->fpin, fpin, a->length);

    if(!piped)
    {
      safe_fclose (&fpin);
      thepid = mutt_create_filter (command, NULL, &fpout, &fperr);
    }
    else
    {
      unlink (tempfile);
      fflush (fpin);
      rewind (fpin);
      thepid = mutt_create_filter_fd (command, NULL, &fpout, &fperr,
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
    }
    
    if (s->prefix)
    {
      while (fgets (buffer, sizeof(buffer), fpout) != NULL)
      {
        state_puts (s->prefix, s);
        state_puts (buffer, s);
      }
      /* check for data on stderr */
      if (fgets (buffer, sizeof(buffer), fperr)) 
      {
	if (s->flags & MUTT_DISPLAY)
	{
	  state_mark_attach (s);
	  state_printf (s, _("[-- Autoview stderr of %s --]\n"), command);
	}

	state_puts (s->prefix, s);
	state_puts (buffer, s);
	while (fgets (buffer, sizeof(buffer), fperr) != NULL)
	{
	  state_puts (s->prefix, s);
	  state_puts (buffer, s);
	}
      }
    }
    else
    {
      mutt_copy_stream (fpout, s->fpout);
      /* Check for stderr messages */
      if (fgets (buffer, sizeof(buffer), fperr))
      {
	if (s->flags & MUTT_DISPLAY)
	{
	  state_mark_attach (s);
	  state_printf (s, _("[-- Autoview stderr of %s --]\n"), 
			command);
	}
	
	state_puts (buffer, s);
	mutt_copy_stream (fperr, s->fpout);
      }
    }

  bail:
    safe_fclose (&fpout);
    safe_fclose (&fperr);

    mutt_wait_filter (thepid);
    if (piped)
      safe_fclose (&fpin);
    else
      mutt_unlink (tempfile);

    if (s->flags & MUTT_DISPLAY) 
      mutt_clear_error ();
  }
  rfc1524_free_entry (&entry);

  return rc;
}