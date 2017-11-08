void Curl_ossl_random(struct SessionHandle *data, unsigned char *entropy,
                      size_t length)
{
  Curl_ossl_seed(data); /* Initiate the seed if not already done */
  RAND_bytes(entropy, curlx_uztosi(length));
}