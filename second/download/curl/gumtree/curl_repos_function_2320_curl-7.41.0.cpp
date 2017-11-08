int Curl_nss_random(struct SessionHandle *data,
                    unsigned char *entropy,
                    size_t length)
{
  if(data)
    Curl_nss_seed(data);  /* Initiate the seed if not already done */

  if(SECSuccess != PK11_GenerateRandom(entropy, curlx_uztosi(length))) {
    /* no way to signal a failure from here, we have to abort */
    failf(data, "PK11_GenerateRandom() failed, calling abort()...");
    abort();
  }

  return 0;
}