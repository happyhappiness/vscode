void mutt_enter_command (void)
{
  BUFFER err, token;
  char buffer[LONG_STRING];
  int r;

  buffer[0] = 0;
  if (mutt_get_field (":", buffer, sizeof (buffer), MUTT_COMMAND) != 0 || !buffer[0])
    return;
  mutt_buffer_init (&err);
  err.dsize = STRING;
  err.data = safe_malloc(err.dsize);
  mutt_buffer_init (&token);
  r = mutt_parse_rc_line (buffer, &token, &err);
  FREE (&token.data);
  if (err.data[0])
  {
    /* since errbuf could potentially contain printf() sequences in it,
       we must call mutt_error() in this fashion so that vsprintf()
       doesn't expect more arguments that we passed */
    if (r == 0)
      mutt_message ("%s", err.data);
    else
      mutt_error ("%s", err.data);
  }

  FREE (&err.data);
}