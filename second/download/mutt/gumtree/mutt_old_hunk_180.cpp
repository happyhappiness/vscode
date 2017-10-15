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
	  if (mutt_yesorno (_("Can't match nametemplate, continue?"), M_YES) != M_YES)
	  {
	    rfc1524_free_entry (&entry);
	    return 0;
	  }
	  strfcpy (newfile, a->filename, sizeof (newfile));
	}
