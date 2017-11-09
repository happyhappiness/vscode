CURLcode Curl_ssl_md5sum(unsigned char *tmp, /* input */
                         size_t tmplen,
                         unsigned char *md5sum, /* output */
                         size_t md5len)
{
  return Curl_ssl->md5sum(tmp, tmplen, md5sum, md5len);
}