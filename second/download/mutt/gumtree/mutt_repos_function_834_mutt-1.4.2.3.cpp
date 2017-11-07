void mutt_bounce_message (FILE *fp, HEADER *h, ADDRESS *to)
{
  ADDRESS *from;
  const char *fqdn = mutt_fqdn (1);
  char resent_from[STRING];

  resent_from[0] = '\0';
  from = mutt_default_from ();

  if (fqdn)
    rfc822_qualify (from, fqdn);

  rfc2047_encode_adrlist (from, "Resent-From");
  
  rfc822_write_address (resent_from, sizeof (resent_from), from);

  _mutt_bounce_message (fp, h, to, resent_from, from);

  rfc822_free_address (&from);
}