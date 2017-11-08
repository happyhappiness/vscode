void Curl_ssl_md5sum(unsigned char *tmp, /* input */
                     size_t tmplen,
                     unsigned char *md5sum, /* output */
                     size_t md5len)
{
  curlssl_md5sum(tmp, tmplen, md5sum, md5len);
}