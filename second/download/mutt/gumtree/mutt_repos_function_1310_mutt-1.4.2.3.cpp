int imap_parse_list_response(IMAP_DATA* idata, char **name, int *noselect,
  int *noinferiors, char *delim)
{
  char *s;
  long bytes;
  int rc;

  *name = NULL;

  rc = imap_cmd_step (idata);
  if (rc == IMAP_CMD_OK)
    return 0;
  if (rc != IMAP_CMD_CONTINUE)
    return -1;

  s = imap_next_word (idata->cmd.buf);
  if ((ascii_strncasecmp ("LIST", s, 4) == 0) ||
      (ascii_strncasecmp ("LSUB", s, 4) == 0))
  {
    *noselect = 0;
    *noinferiors = 0;
      
    s = imap_next_word (s); /* flags */
    if (*s == '(')
    {
      char *ep;

      s++;
      ep = s;
      while (*ep && *ep != ')') ep++;
      do
      {
	if (!ascii_strncasecmp (s, "\\NoSelect", 9))
	  *noselect = 1;
	if (!ascii_strncasecmp (s, "\\NoInferiors", 12))
	  *noinferiors = 1;
	/* See draft-gahrns-imap-child-mailbox-?? */
	if (!ascii_strncasecmp (s, "\\HasNoChildren", 14))
	  *noinferiors = 1;
	if (*s != ')')
	  s++;
	while (*s && *s != '\\' && *s != ')') s++;
      } while (s != ep);
    }
    else
      return 0;
    s = imap_next_word (s); /* delim */
    /* Reset the delimiter, this can change */
    if (ascii_strncasecmp (s, "NIL", 3))
    {
      if (s && s[0] == '\"' && s[1] && s[2] == '\"')
	*delim = s[1];
      else if (s && s[0] == '\"' && s[1] && s[1] == '\\' && s[2] && s[3] == '\"')
	*delim = s[2];
    }
    s = imap_next_word (s); /* name */
    if (s && *s == '{')	/* Literal */
    { 
      if (imap_get_literal_count(idata->cmd.buf, &bytes) < 0)
	return -1;
      if (imap_cmd_step (idata) != IMAP_CMD_CONTINUE)
	return -1;
      *name = idata->cmd.buf;
    }
    else
      *name = s;
  }

  return 0;
}