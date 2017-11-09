ADDRESS *mutt_default_from (void)
{
  ADDRESS *adr;
  const char *fqdn = mutt_fqdn(1);

  /* 
   * Note: We let $from override $realname here.  Is this the right
   * thing to do? 
   */

  if (From)
    adr = rfc822_cpy_adr_real (From);
  else if (option (OPTUSEDOMAIN))
  {
    adr = rfc822_new_address ();
    adr->mailbox = safe_malloc (mutt_strlen (Username) + mutt_strlen (fqdn) + 2);
    sprintf (adr->mailbox, "%s@%s", NONULL(Username), NONULL(fqdn));	/* __SPRINTF_CHECKED__ */
  }
  else
  {
    adr = rfc822_new_address ();
    adr->mailbox = safe_strdup (NONULL(Username));
  }
  
  return (adr);
}