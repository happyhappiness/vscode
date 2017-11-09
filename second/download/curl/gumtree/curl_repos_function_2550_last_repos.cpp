static CURLcode Curl_axtls_random(struct Curl_easy *data,
                                  unsigned char *entropy, size_t length)
{
  static bool ssl_seeded = FALSE;
  (void)data;
  if(!ssl_seeded) {
    ssl_seeded = TRUE;
    /* Initialize the seed if not already done. This call is not exactly thread
     * safe (and neither is the ssl_seeded check), but the worst effect of a
     * race condition is that some global resources will leak. */
    RNG_initialize();
  }
  get_random((int)length, entropy);
  return CURLE_OK;
}