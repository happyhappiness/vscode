static int check_certificate_file (X509 *peercert)
{
  unsigned char peermd[EVP_MAX_MD_SIZE];
  unsigned int peermdlen;
  X509 *cert = NULL;
  int pass = 0;
  FILE *fp;

  if (!SslCertFile)
    return 0;

  if ((fp = fopen (SslCertFile, "rt")) == NULL)
    return 0;

  if (!X509_digest (peercert, EVP_sha256(), peermd, &peermdlen))
  {
    safe_fclose (&fp);
    return 0;
  }

  while (PEM_read_X509 (fp, &cert, NULL, NULL) != NULL)
  {
    if ((compare_certificates (cert, peercert, peermd, peermdlen) == 0) &&
        check_certificate_expiration (cert, 1))
    {
      pass = 1;
      break;
    }
  }
  /* PEM_read_X509 sets an error on eof */
  if (!pass)
    ERR_clear_error();
  X509_free (cert);
  safe_fclose (&fp);

  return pass;
}