				      a->filename, newfile, sizeof (newfile)))
      {
	dprint(1, (debugfile, "oldfile: %s\t newfile: %s\n",
				  a->filename, newfile));
	if (safe_symlink (a->filename, newfile) == -1)
	{
	  if (mutt_yesorno (_("Can't match nametemplate, continue?"), MUTT_YES) != MUTT_YES)
	    goto bailout;
	}
	else
	  unlink_newfile = 1;
      }
      else
