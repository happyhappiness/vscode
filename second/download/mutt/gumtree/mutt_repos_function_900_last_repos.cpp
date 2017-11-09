static void x509_fingerprint (char *s, int l, X509 * cert, const EVP_MD *(*hashfunc)(void))
{
  unsigned char md[EVP_MAX_MD_SIZE];
  unsigned int n;
  int j;

  if (!X509_digest (cert, hashfunc(), md, &n))
  {
    snprintf (s, l, "%s", _("[unable to calculate]"));
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