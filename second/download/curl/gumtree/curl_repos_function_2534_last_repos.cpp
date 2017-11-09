static CURLcode Curl_cyassl_random(struct Curl_easy *data,
                                   unsigned char *entropy, size_t length)
{
  RNG rng;
  (void)data;
  if(InitRng(&rng))
    return CURLE_FAILED_INIT;
  if(length > UINT_MAX)
    return CURLE_FAILED_INIT;
  if(RNG_GenerateBlock(&rng, entropy, (unsigned)length))
    return CURLE_FAILED_INIT;
  return CURLE_OK;
}