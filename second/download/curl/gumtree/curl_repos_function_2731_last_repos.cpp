static CURLcode Curl_gtls_random(struct Curl_easy *data,
                                 unsigned char *entropy, size_t length)
{
#if defined(USE_GNUTLS_NETTLE)
  int rc;
  (void)data;
  rc = gnutls_rnd(GNUTLS_RND_RANDOM, entropy, length);
  return rc?CURLE_FAILED_INIT:CURLE_OK;
#elif defined(USE_GNUTLS)
  if(data)
    Curl_gtls_seed(data); /* Initiate the seed if not already done */
  gcry_randomize(entropy, length, GCRY_STRONG_RANDOM);
#endif
  return CURLE_OK;
}