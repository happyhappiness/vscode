  if(!(qop_values & DIGEST_QOP_VALUE_AUTH))
    return CURLE_BAD_CONTENT_ENCODING;

  /* Generate 32 random hex chars, 32 bytes + 1 zero termination */
  result = Curl_rand_hex(data, (unsigned char *)cnonce, sizeof(cnonce));
  if(result)
    return result;

  /* So far so good, now calculate A1 and H(A1) according to RFC 2831 */
  ctxt = Curl_MD5_init(Curl_DIGEST_MD5);
  if(!ctxt)
