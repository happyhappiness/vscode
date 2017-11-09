static int compare_certificates (X509 *cert, X509 *peercert,
  unsigned char *peermd, unsigned int peermdlen)
{
  unsigned char md[EVP_MAX_MD_SIZE];
  unsigned int mdlen;

  /* Avoid CPU-intensive digest calculation if the certificates are
    * not even remotely equal.
    */
  if (X509_subject_name_cmp (cert, peercert) != 0 ||
      X509_issuer_name_cmp (cert, peercert) != 0)
    return -1;

  if (!X509_digest (cert, EVP_sha256(), md, &mdlen) || peermdlen != mdlen)
    return -1;

  if (memcmp(peermd, md, mdlen) != 0)
    return -1;

  return 0;
}