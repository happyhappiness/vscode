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
