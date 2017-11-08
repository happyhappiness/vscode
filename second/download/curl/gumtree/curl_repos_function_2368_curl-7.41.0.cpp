int Curl_gtls_random(struct SessionHandle *data,
                     unsigned char *entropy,
                     size_t length)
{
#if defined(USE_GNUTLS_NETTLE)
  (void)data;
  gnutls_rnd(GNUTLS_RND_RANDOM, entropy, length);
#elif defined(USE_GNUTLS)
  if(data)
    Curl_gtls_seed(data); /* Initiate the seed if not already done */
  gcry_randomize(entropy, length, GCRY_STRONG_RANDOM);
#endif
  return 0;
}