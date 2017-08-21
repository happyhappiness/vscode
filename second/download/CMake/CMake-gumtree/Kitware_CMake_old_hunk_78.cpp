  if(!(qop_values & DIGEST_QOP_VALUE_AUTH))
    return CURLE_BAD_CONTENT_ENCODING;

  /* Generate 16 bytes of random data */
  result = Curl_rand(data, &entropy[0], 4);
  if(result)
    return result;

  /* Convert the random data into a 32 byte hex string */
  snprintf(cnonce, sizeof(cnonce), "%08x%08x%08x%08x",
           entropy[0], entropy[1], entropy[2], entropy[3]);

  /* So far so good, now calculate A1 and H(A1) according to RFC 2831 */
  ctxt = Curl_MD5_init(Curl_DIGEST_MD5);
  if(!ctxt)
