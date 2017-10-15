	  return 1;
      }
    }
    else if ((rc = mutt_yesorno (_("File is a directory, save under it?"), M_YES)) != M_YES)
      return (rc == M_NO) ? 1 : -1;

    if (!attname || !attname[0])
    {
      tmp[0] = 0;
      if (mutt_get_field (_("File under directory: "), tmp, sizeof (tmp),
				      M_FILE | M_CLEAR) != 0 || !tmp[0])
	return (-1);
      mutt_concat_path (fname, path, tmp, flen);
    }
    else
      mutt_concat_path (fname, path, mutt_basename (attname), flen);
  }
  
  if (*append == 0 && access (fname, F_OK) == 0)
  {
    switch (mutt_multi_choice
	    (_("File exists, (o)verwrite, (a)ppend, or (c)ancel?"), _("oac")))
