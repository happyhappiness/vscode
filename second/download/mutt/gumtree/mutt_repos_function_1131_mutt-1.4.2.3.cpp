static int source_rc (const char *rcfile, BUFFER *err)
{
  FILE *f;
  int line = 0, rc = 0;
  BUFFER token;
  char *linebuf = NULL;
  size_t buflen;
  pid_t pid;

  if ((f = mutt_open_read (rcfile, &pid)) == NULL)
  {
    snprintf (err->data, err->dsize, "%s: %s", rcfile, strerror (errno));
    return (-1);
  }

  memset (&token, 0, sizeof (token));
  while ((linebuf = mutt_read_line (linebuf, &buflen, f, &line)) != NULL)
  {
    if (mutt_parse_rc_line (linebuf, &token, err) == -1)
    {
      mutt_error (_("Error in %s, line %d: %s"), rcfile, line, err->data);
      if (--rc < -MAXERRS)
        break;
    }
    else
      if (rc < 0)
        rc = -1;
  }
  FREE (&token.data);
  safe_free ((void **) &linebuf);
  fclose (f);
  if (pid != -1)
    mutt_wait_filter (pid);
  if (rc)
  {
    /* the muttrc source keyword */
    snprintf (err->data, err->dsize, rc >= -MAXERRS ? _("source: errors in %s")
      : _("source: reading aborted due too many errors in %s"), rcfile);
    rc = -1;
  }
  return (rc);
}