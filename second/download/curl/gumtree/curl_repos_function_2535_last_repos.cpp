static void Curl_cyassl_sha256sum(const unsigned char *tmp, /* input */
                                  size_t tmplen,
                                  unsigned char *sha256sum /* output */,
                                  size_t unused)
{
  Sha256 SHA256pw;
  (void)unused;
  InitSha256(&SHA256pw);
  Sha256Update(&SHA256pw, tmp, (word32)tmplen);
  Sha256Final(&SHA256pw, sha256sum);
}