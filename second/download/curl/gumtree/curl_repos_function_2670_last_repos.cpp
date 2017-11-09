static CURLcode Curl_nss_random(struct Curl_easy *data,
                                unsigned char *entropy,
                                size_t length)
{
  Curl_nss_seed(data);  /* Initiate the seed if not already done */

  if(SECSuccess != PK11_GenerateRandom(entropy, curlx_uztosi(length)))
    /* signal a failure */
    return CURLE_FAILED_INIT;

  return CURLE_OK;
}