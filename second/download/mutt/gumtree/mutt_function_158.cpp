int mutt_save_confirm (const char *s, struct stat *st)
{
  char tmp[_POSIX_PATH_MAX];
  int ret = 0;
  int rc;
  int magic = 0;

  magic = mx_get_magic (s);

#ifdef USE_POP
  if (magic == M_POP)
  {
    mutt_error _("Can't save message to POP mailbox.");
    return 1;
  }
#endif

  if (magic > 0 && !mx_access (s, W_OK))
  {
    if (option (OPTCONFIRMAPPEND))
    {
      snprintf (tmp, sizeof (tmp), _("Append messages to %s?"), s);
      if ((rc = mutt_yesorno (tmp, M_YES)) == M_NO)
	ret = 1;
      else if (rc == -1)
	ret = -1;
    }
  }

  if (stat (s, st) != -1)
  {
    if (magic == -1)
    {
      mutt_error (_("%s is not a mailbox!"), s);
      return 1;
    }
  }
  else if (magic != M_IMAP)
  {
    st->st_mtime = 0;
    st->st_atime = 0;

    if (errno == ENOENT)
    {
      if (option (OPTCONFIRMCREATE))
      {
	snprintf (tmp, sizeof (tmp), _("Create %s?"), s);
	if ((rc = mutt_yesorno (tmp, M_YES)) == M_NO)
	  ret = 1;
	else if (rc == -1)
	  ret = -1;
      }
    }
    else
    {
      mutt_perror (s);
      return 1;
    }
  }

  CLEARLINE (LINES-1);
  return (ret);
}