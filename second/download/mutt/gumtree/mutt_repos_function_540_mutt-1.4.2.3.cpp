static int check_certificate_by_digest (X509 *peercert)
{
  unsigned char peermd[EVP_MAX_MD_SIZE];
  unsigned int peermdlen;
  X509 *cert = NULL;
  int pass = 0;
  FILE *fp;

  /* expiration check */
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

  if ((fp = fopen (SslCertFile, "rt")) == NULL)
    return 0;

  if (!X509_digest (peercert, EVP_sha1(), peermd, &peermdlen))
  {
    fclose (fp);
    return 0;
  }
  
  while ((cert = READ_X509_KEY (fp, &cert)) != NULL)
  {
    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int mdlen;

    /* Avoid CPU-intensive digest calculation if the certificates are
     * not even remotely equal.
     */
    if (X509_subject_name_cmp (cert, peercert) != 0 ||
	X509_issuer_name_cmp (cert, peercert) != 0)
      continue;

    if (!X509_digest (cert, EVP_sha1(), md, &mdlen) || peermdlen != mdlen)
      continue;
    
    if (memcmp(peermd, md, mdlen) != 0)
      continue;

    pass = 1;
    break;
  }
  X509_free (cert);
  fclose (fp);

  return pass;
}