  int rc;
  int magic = 0;

  magic = mx_get_magic (s);

#ifdef USE_POP
  if (magic == MUTT_POP)
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
      if ((rc = mutt_yesorno (tmp, MUTT_YES)) == MUTT_NO)
	ret = 1;
      else if (rc == -1)
	ret = -1;
    }
  }

