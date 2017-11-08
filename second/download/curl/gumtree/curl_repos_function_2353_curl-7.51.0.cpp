int Curl_cyassl_random(struct Curl_easy *data,
                       unsigned char *entropy,
                       size_t length)
{
  RNG rng;
  (void)data;
  if(InitRng(&rng))
    return 1;
  if(length > UINT_MAX)
    return 1;
  if(RNG_GenerateBlock(&rng, entropy, (unsigned)length))
    return 1;
  return 0;
}