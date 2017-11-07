static QUERY *run_query (char *s, int quiet)
{
  FILE *fp;
  QUERY *first = NULL;
  QUERY *cur = NULL;
  char cmd[_POSIX_PATH_MAX];
  char *buf = NULL;
  size_t buflen;
  int dummy = 0;
  char msg[STRING];
  char *p;
  pid_t thepid;
  int l;


  mutt_expand_file_fmt (cmd, sizeof(cmd), QueryCmd, s);

  if ((thepid = mutt_create_filter (cmd, NULL, &fp, NULL)) < 0)
  {
    dprint (1, (debugfile, "unable to fork command: %s", cmd));
    return 0;
  }
  if (!quiet)
    mutt_message _("Waiting for response...");
  fgets (msg, sizeof (msg), fp);
  if ((p = strrchr (msg, '\n')))
    *p = '\0';
  while ((buf = mutt_read_line (buf, &buflen, fp, &dummy)) != NULL)
  {
    if ((p = strtok(buf, "\t\n")))
    {
      if (first == NULL)
      {
	FirstColumn = 0;
	SecondColumn = 0;
	first = (QUERY *) safe_calloc (1, sizeof (QUERY));
	cur = first;
      }
      else
      {
	cur->next = (QUERY *) safe_calloc (1, sizeof (QUERY));
	cur = cur->next;
      }

      l = mutt_strlen (p);
      if (l > SecondColumn)
	SecondColumn = l;
	
      cur->addr = rfc822_parse_adrlist (cur->addr, p);
      p = strtok(NULL, "\t\n");
      if (p)
      {
	l = mutt_strlen (p);
	if (l > FirstColumn)
	  FirstColumn = l;
	cur->name = safe_strdup (p);
	p = strtok(NULL, "\t\n");
	if (p)
	{
	  cur->other = safe_strdup (p);
	}
      }
    }
  }
  safe_free ((void **) &buf);
  fclose (fp);
  if (mutt_wait_filter (thepid))
  {
    dprint (1, (debugfile, "Error: %s\n", msg));
    if (!quiet)  mutt_error ("%s", msg);
  }
  else
  {
    if (!quiet)
      mutt_message ("%s", msg);
  }
  
  return first;
}