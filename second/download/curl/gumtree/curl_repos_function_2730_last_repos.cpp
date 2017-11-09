static int Curl_gtls_seed(struct Curl_easy *data)
{
  /* we have the "SSL is seeded" boolean static to prevent multiple
     time-consuming seedings in vain */
  static bool ssl_seeded = FALSE;

  /* Quickly add a bit of entropy */
  gcry_fast_random_poll();

  if(!ssl_seeded || data->set.str[STRING_SSL_RANDOM_FILE] ||
     data->set.str[STRING_SSL_EGDSOCKET]) {

    /* TODO: to a good job seeding the RNG
       This may involve the gcry_control function and these options:
       GCRYCTL_SET_RANDOM_SEED_FILE
       GCRYCTL_SET_RNDEGD_SOCKET
    */
    ssl_seeded = TRUE;
  }
  return 0;
}