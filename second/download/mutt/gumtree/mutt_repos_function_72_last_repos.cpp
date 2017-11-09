static int edit_address (ADDRESS **a, /* const */ char *field)
{
  char buf[HUGE_STRING];
  char *err = NULL;
  int idna_ok = 0;
  
  do
  {
    buf[0] = 0;
    mutt_addrlist_to_local (*a);
    rfc822_write_address (buf, sizeof (buf), *a, 0);
    if (mutt_get_field (field, buf, sizeof (buf), MUTT_ALIAS) != 0)
      return (-1);
    rfc822_free_address (a);
    *a = mutt_expand_aliases (mutt_parse_adrlist (NULL, buf));
    if ((idna_ok = mutt_addrlist_to_intl (*a, &err)) != 0)
    {
      mutt_error (_("Error: '%s' is a bad IDN."), err);
      mutt_refresh ();
      mutt_sleep (2);
      FREE (&err);
    }
  } 
  while (idna_ok != 0);
  return 0;
}