void mutt_display_address (ENVELOPE *env)
{
  char *pfx = NULL;
  char buf[SHORT_STRING];
  ADDRESS *adr = NULL;

  adr = mutt_get_address (env, &pfx);

  if (!adr) return;
  
  /* 
   * Note: We don't convert IDNA to local representation this time.
   * That is intentional, so the user has an opportunity to copy &
   * paste the on-the-wire form of the address to other, IDN-unable
   * software. 
   */
  
  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), adr, 0);
  mutt_message ("%s: %s", pfx, buf);
}