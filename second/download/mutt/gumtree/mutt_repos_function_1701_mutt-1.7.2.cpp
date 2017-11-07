static int mutt_execute_commands (LIST *p)
{
  BUFFER err, token;

  mutt_buffer_init (&err);
  err.dsize = STRING;
  err.data = safe_malloc (err.dsize);
  mutt_buffer_init (&token);
  for (; p; p = p->next)
  {
    if (mutt_parse_rc_line (p->data, &token, &err) != 0)
    {
      fprintf (stderr, _("Error in command line: %s\n"), err.data);
      FREE (&token.data);
      FREE (&err.data);

      return -1;
    }
  }
  FREE (&token.data);
  FREE (&err.data);

  return 0;
}