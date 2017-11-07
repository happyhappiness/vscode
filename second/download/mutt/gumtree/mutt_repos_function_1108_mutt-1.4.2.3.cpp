int mutt_print_attachment (FILE *fp, BODY *a)
{
  char newfile[_POSIX_PATH_MAX] = "";
  char type[STRING];
  pid_t thepid;
  FILE *ifp, *fpout;
  short unlink_newfile = 0;
  
  snprintf (type, sizeof (type), "%s/%s", TYPE (a), a->subtype);

  if (rfc1524_mailcap_lookup (a, type, NULL, M_PRINT)) 
  {
    char command[_POSIX_PATH_MAX+STRING];
    rfc1524_entry *entry;
    int piped = FALSE;

    dprint (2, (debugfile, "Using mailcap...\n"));
    
    entry = rfc1524_new_entry ();
    rfc1524_mailcap_lookup (a, type, entry, M_PRINT);
    if (rfc1524_expand_filename (entry->nametemplate, a->filename,
						  newfile, sizeof (newfile)))
    {
      if (!fp)
      {
	if (safe_symlink(a->filename, newfile) == -1)
	{
	  if (mutt_yesorno (_("Can't match nametemplate, continue?"), 1) != M_YES)
	  {
	    rfc1524_free_entry (&entry);
	    return 0;
	  }
	  strfcpy (newfile, a->filename, sizeof (newfile));
	}
	else
	  unlink_newfile = 1;
      }
    }

    /* in recv mode, save file to newfile first */
    if (fp)
      mutt_save_attachment (fp, a, newfile, 0, NULL);

    strfcpy (command, entry->printcommand, sizeof (command));
    piped = rfc1524_expand_command (a, newfile, type, command, sizeof (command));

    mutt_endwin (NULL);

    /* interactive program */
    if (piped)
    {
      if ((ifp = fopen (newfile, "r")) == NULL)
      {
	mutt_perror ("fopen");
	rfc1524_free_entry (&entry);
	return (0);
      }

      if ((thepid = mutt_create_filter (command, &fpout, NULL, NULL)) < 0)
      {
	mutt_perror _("Can't create filter");
	rfc1524_free_entry (&entry);
	safe_fclose (&ifp);
	return 0;
      }
      mutt_copy_stream (ifp, fpout);
      safe_fclose (&fpout);
      safe_fclose (&ifp);
      if (mutt_wait_filter (thepid) || option (OPTWAITKEY))
	mutt_any_key_to_continue (NULL);
    }
    else
    {
      if (mutt_system (command) || option (OPTWAITKEY))
	mutt_any_key_to_continue (NULL);
    }

    if (fp)
      mutt_unlink (newfile);
    else if (unlink_newfile)
      unlink(newfile);

    rfc1524_free_entry (&entry);
    return (1);
  }

  if (!ascii_strcasecmp ("text/plain", type) ||
      !ascii_strcasecmp ("application/postscript", type))
  {
    return (mutt_pipe_attachment (fp, a, NONULL(PrintCmd), NULL));
  }
  else if (mutt_can_decode (a))
  {
    /* decode and print */

    int rc = 0;
    
    ifp = NULL;
    fpout = NULL;
    
    mutt_mktemp (newfile);
    if (mutt_decode_save_attachment (fp, a, newfile, M_PRINTING, 0) == 0)
    {
      
      dprint (2, (debugfile, "successfully decoded %s type attachment to %s\n",
		  type, newfile));
      
      if ((ifp = fopen (newfile, "r")) == NULL)
      {
	mutt_perror ("fopen");
	goto bail0;
      }

      dprint (2, (debugfile, "successfully opened %s read-only\n", newfile));
      
      mutt_endwin (NULL);
      if ((thepid = mutt_create_filter (NONULL(PrintCmd), &fpout, NULL, NULL)) < 0)
      {
	mutt_perror _("Can't create filter");
	goto bail0;
      }

      dprint (2, (debugfile, "Filter created.\n"));
      
      mutt_copy_stream (ifp, fpout);

      safe_fclose (&fpout);
      safe_fclose (&ifp);

      if (mutt_wait_filter (thepid) != 0 || option (OPTWAITKEY))
	mutt_any_key_to_continue (NULL);
      rc = 1;
    }
  bail0:
    safe_fclose (&ifp);
    safe_fclose (&fpout);
    mutt_unlink (newfile);
    return rc;
  }
  else
  {
    mutt_error _("I don't know how to print that!");
    return 0;
  }
}