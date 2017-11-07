static void x509_fingerprint (char *s, int l, X509 * cert)
{
  unsigned char md[EVP_MAX_MD_SIZE];
  unsigned int n;
  int j;

  if (!X509_digest (cert, EVP_md5 (), md, &n))
  {
    snprintf (s, l, _("[unable to calculate]"));
  }
  else
  {
    for (j = 0; j < (int) n; j++)
    {
      char ch[8];
      snprintf (ch, 8, "%02X%s", md[j], (j % 2 ? " " : ""));
      safe_strcat (s, l, ch);
    }
  }
}