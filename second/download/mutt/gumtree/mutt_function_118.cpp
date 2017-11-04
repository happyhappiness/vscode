int mutt_edit_attachment (BODY *a)
{
  char type[STRING];
  char command[STRING];
  char newfile[_POSIX_PATH_MAX] = "";
  rfc1524_entry *entry = rfc1524_new_entry ();
  short unlink_newfile = 0;
  int rc = 0;
  
  snprintf (type, sizeof (type), "%s/%s", TYPE (a), a->subtype);
  if (rfc1524_mailcap_lookup (a, type, entry, M_EDIT))
  {
    if (entry->editcommand)
    {

      strfcpy (command, entry->editcommand, sizeof (command));
      if (rfc1524_expand_filename (entry->nametemplate,
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
  }

  rc = 1;
  
  bailout:
  
  if(unlink_newfile)
    unlink(newfile);
  
  rfc1524_free_entry (&entry);
  return rc;
}