int mutt_query_variables (LIST *queries)
{
  LIST *p;
  
  char command[STRING];
  
  BUFFER err, token;

  mutt_buffer_init (&err);
  mutt_buffer_init (&token);

  err.dsize = STRING;
  err.data = safe_malloc (err.dsize);
  
  for (p = queries; p; p = p->next)
  {
    snprintf (command, sizeof (command), "set ?%s\n", p->data);
    if (mutt_parse_rc_line (command, &token, &err) == -1)
    {
      fprintf (stderr, "%s\n", err.data);
      FREE (&token.data);
      FREE (&err.data);

      return 1;
    }
    printf ("%s\n", err.data);
  }
  
  FREE (&token.data);
  FREE (&err.data);

  return 0;
}