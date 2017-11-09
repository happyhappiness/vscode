static int check_certificate_cache (X509 *peercert)
{
  unsigned char peermd[EVP_MAX_MD_SIZE];
  unsigned int peermdlen;
  X509 *cert;
  int i;

  if (!X509_digest (peercert, EVP_sha256(), peermd, &peermdlen)
      || !SslSessionCerts)
  {
    return 0;
  }

  for (i = sk_X509_num (SslSessionCerts); i-- > 0;)
  {
    cert = sk_X509_value (SslSessionCerts, i);
    if (!compare_certificates (cert, peercert, peermd, peermdlen))
    {
      return 1;
    }
  }

  return 0;
}