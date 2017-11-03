static int check_certificate_by_digest (X509 *peercert)
{
  unsigned char peermd[EVP_MAX_MD_SIZE];
  unsigned int peermdlen;
  X509 *cert = NULL;
  int pass = 0;
  FILE *fp;

  /* expiration check */
  if (option (OPTSSLVERIFYDATES) != MUTT_NO)
  {
    if (X509_cmp_current_time (X509_get_notBefore (peercert)) >= 0)
    {
      dprint (2, (debugfile, "Server certificate is not yet valid\n"));
      mutt_error (_("Server certificate is not yet valid"));
      mutt_sleep (2);
      return 0;
    }
    if (X509_cmp_current_time (X509_get_notAfter (peercert)) <= 0)
    {
      dprint (2, (debugfile, "Server certificate has expired"));
      mutt_error (_("Server certificate has expired"));
      mutt_sleep (2);
      return 0;
    }
  }

  if ((fp = fopen (SslCertFile, "rt")) == NULL)
    return 0;

  if (!X509_digest (peercert, EVP_sha1(), peermd, &peermdlen))
  {
    safe_fclose (&fp);
    return 0;
  }

  while ((cert = PEM_read_X509 (fp, &cert, NULL, NULL)) != NULL)
  {
    pass = compare_certificates (cert, peercert, peermd, peermdlen) ? 0 : 1;

    if (pass)
      break;
  }
  X509_free (cert);
  safe_fclose (&fp);

  return pass;
}