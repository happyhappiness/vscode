void Curl_ossl_md5sum(unsigned char *tmp, /* input */
                      size_t tmplen,
                      unsigned char *md5sum /* output */,
                      size_t unused)
{
  MD5_CTX MD5pw;
  (void)unused;
  MD5_Init(&MD5pw);
  MD5_Update(&MD5pw, tmp, tmplen);
  MD5_Final(md5sum, &MD5pw);
}