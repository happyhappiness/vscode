static int
mutt_nss_init (void)
{
  if (!MuttNssInitialized)
  {
    PK11_SetPasswordFunc (mutt_nss_password_func);
    if (NSS_Init (SslCertFile) == SECFailure)
      return mutt_nss_error ("NSS_Init");
    
    /* always use strong crypto. */
    if (NSS_SetDomesticPolicy () == SECFailure)
      return mutt_nss_error ("NSS_SetDomesticPolicy");
    
    /* intialize the session cache */
    SSL_ClearSessionCache ();
    
    MuttNssInitialized = 1;
  }
  return 0;
}