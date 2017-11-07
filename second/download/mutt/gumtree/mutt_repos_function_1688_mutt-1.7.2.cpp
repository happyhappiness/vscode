static int source_rc (const char *rcfile, BUFFER *err)
{
  FILE *f;
  int line = 0, rc = 0, conv = 0;
  BUFFER token;
  char *linebuf = NULL;
  char *currentline = NULL;
  size_t buflen;
  pid_t pid;

  dprint (2, (debugfile, "Reading configuration file '%s'.\n",
	  rcfile));
  
  if ((f = mutt_open_read (rcfile, &pid)) == NULL)
  {
    snprintf (err->data, err->dsize, "%s: %s", rcfile, strerror (errno));
    return (-1);
  }

  mutt_buffer_init (&token);
  while ((linebuf = mutt_read_line (linebuf, &buflen, f, &line, MUTT_CONT)) != NULL)
  {
    conv=ConfigCharset && (*ConfigCharset) && Charset;
    if (conv) 
    {
      currentline=safe_strdup(linebuf);
      if (!currentline) continue;
      mutt_convert_string(&currentline, ConfigCharset, Charset, 0);
    } 
    else 
      currentline=linebuf;

    if (mutt_parse_rc_line (currentline, &token, err) == -1)
    {
      mutt_error (_("Error in %s, line %d: %s"), rcfile, line, err->data);
      if (--rc < -MAXERRS) 
      {
        if (conv) FREE(&currentline);
        break;
      }
    }
    else
    {
      if (rc < 0)
        rc = -1;
    }
    if (conv) 
      FREE(&currentline);
  }
  FREE (&token.data);
  FREE (&linebuf);
  safe_fclose (&f);
  if (pid != -1)
    mutt_wait_filter (pid);
  if (rc)
  {
    /* the muttrc source keyword */
    snprintf (err->data, err->dsize, rc >= -MAXERRS ? _("source: errors in %s")
      : _("source: reading aborted due to too many errors in %s"), rcfile);
    rc = -1;
  }
  return (rc);
}