static CURLcode Curl_ossl_seed(struct Curl_easy *data)
{
  /* we have the "SSL is seeded" boolean static to prevent multiple
     time-consuming seedings in vain */
  static bool ssl_seeded = FALSE;
  char fname[256];

  if(ssl_seeded)
    return CURLE_OK;

  if(rand_enough()) {
    /* OpenSSL 1.1.0+ will return here */
    ssl_seeded = TRUE;
    return CURLE_OK;
  }

#ifndef RANDOM_FILE
  /* if RANDOM_FILE isn't defined, we only perform this if an option tells
     us to! */
  if(data->set.str[STRING_SSL_RANDOM_FILE])
#define RANDOM_FILE "" /* doesn't matter won't be used */
#endif
  {
    /* let the option override the define */
    RAND_load_file((data->set.str[STRING_SSL_RANDOM_FILE]?
                    data->set.str[STRING_SSL_RANDOM_FILE]:
                    RANDOM_FILE),
                   RAND_LOAD_LENGTH);
    if(rand_enough())
      return CURLE_OK;
  }

#if defined(HAVE_RAND_EGD)
  /* only available in OpenSSL 0.9.5 and later */
  /* EGD_SOCKET is set at configure time or not at all */
#ifndef EGD_SOCKET
  /* If we don't have the define set, we only do this if the egd-option
     is set */
  if(data->set.str[STRING_SSL_EGDSOCKET])
#define EGD_SOCKET "" /* doesn't matter won't be used */
#endif
  {
    /* If there's an option and a define, the option overrides the
       define */
    int ret = RAND_egd(data->set.str[STRING_SSL_EGDSOCKET]?
                       data->set.str[STRING_SSL_EGDSOCKET]:EGD_SOCKET);
    if(-1 != ret) {
      if(rand_enough())
        return CURLE_OK;
    }
  }
#endif

  /* fallback to a custom seeding of the PRNG using a hash based on a current
     time */
  do {
    unsigned char randb[64];
    size_t len = sizeof(randb);
    size_t i, i_max;
    for(i = 0, i_max = len / sizeof(struct curltime); i < i_max; ++i) {
      struct curltime tv = curlx_tvnow();
      Curl_wait_ms(1);
      tv.tv_sec *= i + 1;
      tv.tv_usec *= (unsigned int)i + 2;
      tv.tv_sec ^= ((curlx_tvnow().tv_sec + curlx_tvnow().tv_usec) *
                    (i + 3)) << 8;
      tv.tv_usec ^= (unsigned int) ((curlx_tvnow().tv_sec +
                                     curlx_tvnow().tv_usec) *
                                    (i + 4)) << 16;
      memcpy(&randb[i * sizeof(struct curltime)], &tv,
             sizeof(struct curltime));
    }
    RAND_add(randb, (int)len, (double)len/2);
  } while(!rand_enough());

  /* generates a default path for the random seed file */
  fname[0] = 0; /* blank it first */
  RAND_file_name(fname, sizeof(fname));
  if(fname[0]) {
    /* we got a file name to try */
    RAND_load_file(fname, RAND_LOAD_LENGTH);
    if(rand_enough())
      return CURLE_OK;
  }

  infof(data, "libcurl is now using a weak random seed!\n");
  return (rand_enough() ? CURLE_OK :
    CURLE_SSL_CONNECT_ERROR /* confusing error code */);
}