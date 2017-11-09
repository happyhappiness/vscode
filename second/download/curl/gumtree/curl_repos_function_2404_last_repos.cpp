static void Curl_ossl_sha256sum(const unsigned char *tmp, /* input */
                                size_t tmplen,
                                unsigned char *sha256sum /* output */,
                                size_t unused)
{
  SHA256_CTX SHA256pw;
  (void)unused;
  SHA256_Init(&SHA256pw);
  SHA256_Update(&SHA256pw, tmp, tmplen);
  SHA256_Final(sha256sum, &SHA256pw);
}