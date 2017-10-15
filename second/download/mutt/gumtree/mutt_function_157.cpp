int mutt_check_overwrite (const char *attname, const char *path,
				char *fname, size_t flen, int *append, char **directory) 
{
  int rc = 0;
  char tmp[_POSIX_PATH_MAX];
  struct stat st;

  strfcpy (fname, path, flen);
  if (access (fname, F_OK) != 0)
    return 0;
  if (stat (fname, &st) != 0)
    return -1;
  if (S_ISDIR (st.st_mode))
  {
    if (directory)
    {
      switch (mutt_multi_choice
      /* L10N:
         Means "The path you specified as the destination file is a directory."
         See the msgid "Save to file: " (alias.c, recvattach.c) */
	      (_("File is a directory, save under it? [(y)es, (n)o, (a)ll]"), _("yna")))
      {
	case 3:		/* all */
	  mutt_str_replace (directory, fname);
	  break;
	case 1:		/* yes */
	  FREE (directory);		/* __FREE_CHECKED__ */
	  break;
	case -1:	/* abort */
	  FREE (directory); 		/* __FREE_CHECKED__ */
	  return -1;
	case  2:	/* no */
	  FREE (directory);		/* __FREE_CHECKED__ */
	  return 1;
      }
    }
    /* L10N:
       Means "The path you specified as the destination file is a directory."
       See the msgid "Save to file: " (alias.c, recvattach.c) */
    else if ((rc = mutt_yesorno (_("File is a directory, save under it?"), M_YES)) != M_YES)
      return (rc == M_NO) ? 1 : -1;

    strfcpy (tmp, mutt_basename (NONULL (attname)), sizeof (tmp));
    if (mutt_get_field (_("File under directory: "), tmp, sizeof (tmp),
                                    M_FILE | M_CLEAR) != 0 || !tmp[0])
      return (-1);
    mutt_concat_path (fname, path, tmp, flen);
  }
  
  if (*append == 0 && access (fname, F_OK) == 0)
  {
    switch (mutt_multi_choice
	    (_("File exists, (o)verwrite, (a)ppend, or (c)ancel?"), _("oac")))
    {
      case -1: /* abort */
        return -1;
      case 3:  /* cancel */
	return 1;

      case 2: /* append */
        *append = M_SAVE_APPEND;
        break;
      case 1: /* overwrite */
        *append = M_SAVE_OVERWRITE;
        break;
    }
  }
  return 0;
}