void mutt_display_address (ENVELOPE *env)
{
  char *pfx = NULL;
  char buf[SHORT_STRING];
  ADDRESS *adr = NULL;

  adr = mutt_get_address (env, &pfx);

  if (!adr) return;

  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), adr);
  mutt_message ("%s: %s", pfx, buf);
}