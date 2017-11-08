void Curl_gtls_sha256sum(const unsigned char *tmp, /* input */
                      size_t tmplen,
                      unsigned char *sha256sum, /* output */
                      size_t sha256len)
{
#if defined(USE_GNUTLS_NETTLE)
  struct sha256_ctx SHA256pw;
  sha256_init(&SHA256pw);
  sha256_update(&SHA256pw, (unsigned int)tmplen, tmp);
  sha256_digest(&SHA256pw, (unsigned int)sha256len, sha256sum);
#elif defined(USE_GNUTLS)
  gcry_md_hd_t SHA256pw;
  gcry_md_open(&SHA256pw, GCRY_MD_SHA256, 0);
  gcry_md_write(SHA256pw, tmp, tmplen);
  memcpy(sha256sum, gcry_md_read(SHA256pw, 0), sha256len);
  gcry_md_close(SHA256pw);
#endif
}