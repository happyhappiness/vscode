static void tls_fingerprint (gnutls_digest_algorithm_t algo,
                             char* s, int l, const gnutls_datum_t* data)
{
  unsigned char md[36];
  size_t n;
  int j;

  n = 36;

  if (gnutls_fingerprint (algo, data, (char *)md, &n) < 0)
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
    s[2*n+n/2-1] = '\0'; /* don't want trailing space */
  }
}