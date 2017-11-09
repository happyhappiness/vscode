CURLcode Curl_none_md5sum(unsigned char *input, size_t inputlen,
                          unsigned char *md5sum, size_t md5len UNUSED_PARAM)
{
  MD5_context *MD5pw;

  (void)md5len;

  MD5pw = Curl_MD5_init(Curl_DIGEST_MD5);
  if(!MD5pw)
    return CURLE_OUT_OF_MEMORY;
  Curl_MD5_update(MD5pw, input, curlx_uztoui(inputlen));
  Curl_MD5_final(MD5pw, md5sum);
  return CURLE_OK;
}