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
