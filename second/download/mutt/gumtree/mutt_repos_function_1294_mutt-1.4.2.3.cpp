static int imap_get_delim (IMAP_DATA *idata)
{
  char *s;
  int rc;

  /* assume that the delim is /.  If this fails, we're in bigger trouble
   * than getting the delim wrong */
  idata->delim = '/';

  imap_cmd_start (idata, "LIST \"\" \"\"");

  do 
  {
    if ((rc = imap_cmd_step (idata)) != IMAP_CMD_CONTINUE)
      break;

    s = imap_next_word (idata->cmd.buf);
    if (ascii_strncasecmp ("LIST", s, 4) == 0)
    {
      s = imap_next_word (s);
      s = imap_next_word (s);
      if (s && s[0] == '\"' && s[1] && s[2] == '\"')
	idata->delim = s[1];
      else if (s && s[0] == '\"' && s[1] && s[1] == '\\' && s[2] && s[3] == '\"')
	idata->delim = s[2];
    }
  }
  while (rc == IMAP_CMD_CONTINUE);

  if (rc != IMAP_CMD_OK)
  {
    dprint (1, (debugfile, "imap_get_delim: failed.\n"));
    return -1;
  }

  dprint (2, (debugfile, "Delimiter: %c\n", idata->delim));

  return -1;
}