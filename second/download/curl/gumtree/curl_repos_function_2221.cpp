int Curl_cyassl_random(struct SessionHandle *data,
                       unsigned char *entropy,
                       size_t length)
{
  RNG rng;
  (void)data;
  if(InitRng(&rng))
    return 1;
  if(RNG_GenerateBlock(&rng, entropy, length))
    return 1;
  return 0;
}