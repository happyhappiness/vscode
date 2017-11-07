static int mutt_execute_commands (LIST *p)
{
  BUFFER err, token;
  char errstr[SHORT_STRING];

  memset (&err, 0, sizeof (err));
  err.data = errstr;
  err.dsize = sizeof (errstr);
  memset (&token, 0, sizeof (token));
  for (; p; p = p->next)
  {
    if (mutt_parse_rc_line (p->data, &token, &err) != 0)
    {
      fprintf (stderr, _("Error in command line: %s\n"), err.data);
      FREE (&token.data);
      return (-1);
    }
  }
  FREE (&token.data);
  return 0;
}