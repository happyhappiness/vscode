static int check_certificate_expiration (X509 *peercert, int silent)
{
  if (option (OPTSSLVERIFYDATES) != MUTT_NO)
  {
    if (X509_cmp_current_time (X509_get_notBefore (peercert)) >= 0)
    {
      if (!silent)
      {
        dprint (2, (debugfile, "Server certificate is not yet valid\n"));
        mutt_error (_("Server certificate is not yet valid"));
        mutt_sleep (2);
      }
      return 0;
    }
    if (X509_cmp_current_time (X509_get_notAfter (peercert)) <= 0)
    {
      if (!silent)
      {
        dprint (2, (debugfile, "Server certificate has expired\n"));
        mutt_error (_("Server certificate has expired"));
        mutt_sleep (2);
      }
      return 0;
    }
  }

  return 1;
}