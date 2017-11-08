CURLcode Curl_ssl_md5sum(unsigned char *tmp, /* input */
                         size_t tmplen,
                         unsigned char *md5sum, /* output */
                         size_t md5len)
{
#ifdef curlssl_md5sum
  curlssl_md5sum(tmp, tmplen, md5sum, md5len);
#else
  MD5_context *MD5pw;

  (void) md5len;

  MD5pw = Curl_MD5_init(Curl_DIGEST_MD5);
  if(!MD5pw)
    return CURLE_OUT_OF_MEMORY;
  Curl_MD5_update(MD5pw, tmp, curlx_uztoui(tmplen));
  Curl_MD5_final(MD5pw, md5sum);
#endif
  return CURLE_OK;
}