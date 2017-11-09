int mutt_dump_variables (void)
{
  int i;
  
  char command[STRING];
  
  BUFFER err, token;

  mutt_buffer_init (&err);
  mutt_buffer_init (&token);

  err.dsize = STRING;
  err.data = safe_malloc (err.dsize);
  
  for (i = 0; MuttVars[i].option; i++)
  {
    if (MuttVars[i].type == DT_SYN)
      continue;

    snprintf (command, sizeof (command), "set ?%s\n", MuttVars[i].option);
    if (mutt_parse_rc_line (command, &token, &err) == -1)
    {
      fprintf (stderr, "%s\n", err.data);
      FREE (&token.data);
      FREE (&err.data);

      return 1;
    }
    printf("%s\n", err.data);
  }
  
  FREE (&token.data);
  FREE (&err.data);

  return 0;
}