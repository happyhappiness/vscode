static CURLcode Curl_ossl_random(struct Curl_easy *data,
                                 unsigned char *entropy, size_t length)
{
  int rc;
  if(data) {
    if(Curl_ossl_seed(data)) /* Initiate the seed if not already done */
      return CURLE_FAILED_INIT; /* couldn't seed for some reason */
  }
  else {
    if(!rand_enough())
      return CURLE_FAILED_INIT;
  }
  /* RAND_bytes() returns 1 on success, 0 otherwise.  */
  rc = RAND_bytes(entropy, curlx_uztosi(length));
  return (rc == 1 ? CURLE_OK : CURLE_FAILED_INIT);
}