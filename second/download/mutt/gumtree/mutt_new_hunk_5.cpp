				      a->filename, newfile, sizeof (newfile)))
      {
	dprint(1, (debugfile, "oldfile: %s\t newfile: %s\n",
				  a->filename, newfile));
	if (safe_symlink (a->filename, newfile) == -1)
	{
	  if (mutt_yesorno (_("Can't match nametemplate, continue?"), M_YES) != M_YES)
	    goto bailout;
	}
	else
	  unlink_newfile = 1;
      }
      else
	strfcpy(newfile, a->filename, sizeof(newfile));

      if (rfc1524_expand_command (a, newfile, type,
				      command, sizeof (command)))
      {
	/* For now, editing requires a file, no piping */
	mutt_error _("Mailcap Edit entry requires %%s");
        goto bailout;
      }
      else
      {
	mutt_endwin (NULL);
	if (mutt_system (command) == -1)
        {
	  mutt_error (_("Error running \"%s\"!"), command);
          goto bailout;
        }
      }
    }
  }
  else if (a->type == TYPETEXT)
  {
    /* On text, default to editor */
    mutt_edit_file (NONULL (Editor), a->filename);
  }
  else
  {
    rfc1524_free_entry (&entry);
    mutt_error (_("No mailcap edit entry for %s"),type);
    return 0;
