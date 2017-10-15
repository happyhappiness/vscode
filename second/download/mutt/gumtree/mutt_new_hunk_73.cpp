  mutt_quote_filename (tmp, sizeof (tmp), src);
  mutt_expand_fmt (dest, destlen, fmt, tmp);
}

void mutt_expand_fmt (char *dest, size_t destlen, const char *fmt, const char *src)
{
  const char *p;
  char *d;
  size_t slen;
  int found = 0;

  slen = mutt_strlen (src);
  destlen--;
  
  for (p = fmt, d = dest; destlen && *p; p++)
  {
    if (*p == '%') 
    {
      switch (p[1])
      {
	case '%':
	  *d++ = *p++;
	  destlen--;
	  break;
	case 's':
	  found = 1;
	  strfcpy (d, src, destlen + 1);
	  d       += destlen > slen ? slen : destlen;
	  destlen -= destlen > slen ? slen : destlen;
	  p++;
	  break;
	default:
	  *d++ = *p; 
	  destlen--;
	  break;
      }
    }
    else
    {
      *d++ = *p;
      destlen--;
    }
  }
  
  *d = '\0';
  
  if (!found && destlen > 0)
  {
    safe_strcat (dest, destlen, " ");
    safe_strcat (dest, destlen, src);
  }
  
}

/* return 0 on success, -1 on abort, 1 on error */
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
