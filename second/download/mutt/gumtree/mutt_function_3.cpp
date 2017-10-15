int mutt_compose_attachment (BODY *a)
{
  char type[STRING];
  char command[STRING];
  char newfile[_POSIX_PATH_MAX] = "";
  rfc1524_entry *entry = rfc1524_new_entry ();
  short unlink_newfile = 0;
  int rc = 0;
  
  snprintf (type, sizeof (type), "%s/%s", TYPE (a), a->subtype);
  if (rfc1524_mailcap_lookup (a, type, entry, M_COMPOSE))
  {
    if (entry->composecommand || entry->composetypecommand)
    {

      if (entry->composetypecommand)
	strfcpy (command, entry->composetypecommand, sizeof (command));
      else 
	strfcpy (command, entry->composecommand, sizeof (command));
      if (rfc1524_expand_filename (entry->nametemplate,
				      a->filename, newfile, sizeof (newfile)))
      {
	dprint(1, (debugfile, "oldfile: %s\t newfile: %s\n",
				  a->filename, newfile));
	if (safe_symlink (a->filename, newfile) == -1)
	{
	  if (!mutt_yesorno (_("Can't match nametemplate, continue?"), 1))
	    goto bailout;
	}
	unlink_newfile = 1;
      }
      else
	strfcpy(newfile, a->filename, sizeof(newfile));
      
      if (rfc1524_expand_command (a, newfile, type,
				      command, sizeof (command)))
      {
	/* For now, editing requires a file, no piping */
	mutt_error _("Mailcap compose entry requires %%s");
      }
      else
      {
	int r;

	mutt_endwin (NULL);
	if ((r = mutt_system (command)) == -1)
	  mutt_error (_("Error running \"%s\"!"), command);
	
	if (r != -1 && entry->composetypecommand)
	{
	  BODY *b;
	  FILE *fp, *tfp;
	  char tempfile[_POSIX_PATH_MAX];

	  if ((fp = safe_fopen (a->filename, "r")) == NULL)
	  {
	    mutt_perror _("Failure to open file to parse headers.");
	    goto bailout;
	  }

	  b = mutt_read_mime_header (fp, 0);
	  if (b)
	  {
	    if (b->parameter)
	    {
	      mutt_free_parameter (&a->parameter);
	      a->parameter = b->parameter;
	      b->parameter = NULL;
	    }
	    if (b->description) {
	      safe_free ((void **) &a->description);
	      a->description = b->description;
	      b->description = NULL;
	    }
	    if (b->form_name)
	    {
	      safe_free ((void **) &a->form_name);
	      a->form_name = b->form_name;
	      b->form_name = NULL;
	    }

	    /* Remove headers by copying out data to another file, then 
	     * copying the file back */
	    fseek (fp, b->offset, 0);
	    mutt_mktemp (tempfile);
	    if ((tfp = safe_fopen (tempfile, "w")) == NULL)
	    {
	      mutt_perror _("Failure to open file to strip headers.");
	      goto bailout;
	    }
	    mutt_copy_stream (fp, tfp);
	    fclose (fp);
	    fclose (tfp);
	    mutt_unlink (a->filename);  
	    mutt_rename_file (tempfile, a->filename); 

	    mutt_free_body (&b);
	  }
	}
      }
    }
  }
  else
  {
    rfc1524_free_entry (&entry);
    mutt_message (_("No mailcap compose entry for %s, creating empty file."),
		   type);
    return 1;
  }

  rc = 1;
  
  bailout:
  
  if(unlink_newfile)
    unlink(newfile);

  rfc1524_free_entry (&entry);
  return rc;
}