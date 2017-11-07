int mutt_bounce_message (FILE *fp, HEADER *h, ADDRESS *to)
{
  ADDRESS *from, *resent_to;
  const char *fqdn = mutt_fqdn (1);
  char resent_from[STRING];
  int ret;
  char *err;

  resent_from[0] = '\0';
  from = mutt_default_from ();

  /*
   * mutt_default_from() does not use $realname if the real name is not set
   * in $from, so we add it here.  The reason it is not added in
   * mutt_default_from() is that during normal sending, we execute
   * send-hooks and set the realname last so that it can be changed based
   * upon message criteria.
   */
  if (! from->personal)
    from->personal = safe_strdup(Realname);

  if (fqdn)
    rfc822_qualify (from, fqdn);

  rfc2047_encode_adrlist (from, "Resent-From");
  if (mutt_addrlist_to_intl (from, &err))
  {
    mutt_error (_("Bad IDN %s while preparing resent-from."),
		err);
    rfc822_free_address (&from);
    return -1;
  }
  rfc822_write_address (resent_from, sizeof (resent_from), from, 0);

  /*
   * prepare recipient list. idna conversion appears to happen before this
   * function is called, since the user receives confirmation of the address
   * list being bounced to.
   */
  resent_to = rfc822_cpy_adr(to, 0);
  rfc2047_encode_adrlist(resent_to, "Resent-To");

  ret = _mutt_bounce_message (fp, h, resent_to, resent_from, from);

  rfc822_free_address (&resent_to);
  rfc822_free_address (&from);

  return ret;
}