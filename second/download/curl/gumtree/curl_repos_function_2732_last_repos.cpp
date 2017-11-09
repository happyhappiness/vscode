static CURLcode Curl_gtls_md5sum(unsigned char *tmp, /* input */
                                 size_t tmplen,
                                 unsigned char *md5sum, /* output */
                                 size_t md5len)
{
#if defined(USE_GNUTLS_NETTLE)
  struct md5_ctx MD5pw;
  md5_init(&MD5pw);
  md5_update(&MD5pw, (unsigned int)tmplen, tmp);
  md5_digest(&MD5pw, (unsigned int)md5len, md5sum);
#elif defined(USE_GNUTLS)
  gcry_md_hd_t MD5pw;
  gcry_md_open(&MD5pw, GCRY_MD_MD5, 0);
  gcry_md_write(MD5pw, tmp, tmplen);
  memcpy(md5sum, gcry_md_read(MD5pw, 0), md5len);
  gcry_md_close(MD5pw);
#endif
  return CURLE_OK;
}