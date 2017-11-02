int Curl_ossl_random(struct SessionHandle *data, unsigned char *entropy,
                     size_t length)
{
  if(data) {
    Curl_ossl_seed(data); /* Initiate the seed if not already done */
  }
  RAND_bytes(entropy, curlx_uztosi(length));
  return 0; /* 0 as in no problem */
}