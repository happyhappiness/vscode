void mutt_enter_command (void)
{
  BUFFER err, token;
  char buffer[LONG_STRING], errbuf[SHORT_STRING];
  int r;

  buffer[0] = 0;
  if (mutt_get_field (":", buffer, sizeof (buffer), M_COMMAND) != 0 || !buffer[0])
    return;
  err.data = errbuf;
  err.dsize = sizeof (errbuf);
  memset (&token, 0, sizeof (token));
  r = mutt_parse_rc_line (buffer, &token, &err);
  FREE (&token.data);
  if (errbuf[0])
  {
    /* since errbuf could potentially contain printf() sequences in it,
       we must call mutt_error() in this fashion so that vsprintf()
       doesn't expect more arguments that we passed */
    if (r == 0)
      mutt_message ("%s", errbuf);
    else
      mutt_error ("%s", errbuf);
  }
}