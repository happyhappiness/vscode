{
  CURLcode result = CURLE_OK;
  size_t i;
  MD5_context *ctxt;
  char *response = NULL;
  unsigned char digest[MD5_DIGEST_LEN];
  char HA1_hex[2 * MD5_DIGEST_LEN + 1];
  char HA2_hex[2 * MD5_DIGEST_LEN + 1];
  char resp_hash_hex[2 * MD5_DIGEST_LEN + 1];
  char nonce[64];
  char realm[128];
  char algorithm[64];
  char qop_options[64];
  int qop_values;
  char cnonce[33];
  unsigned int entropy[4];
  char nonceCount[] = "00000001";
  char method[]     = "AUTHENTICATE";
  char qop[]        = DIGEST_QOP_VALUE_STRING_AUTH;
  char *spn         = NULL;

  /* Decode the challenge message */
  result = auth_decode_digest_md5_message(chlg64, nonce, sizeof(nonce),
                                          realm, sizeof(realm),
                                          algorithm, sizeof(algorithm),
                                          qop_options, sizeof(qop_options));
  if(result)
    return result;

  /* We only support md5 sessions */
  if(strcmp(algorithm, "md5-sess") != 0)
    return CURLE_BAD_CONTENT_ENCODING;

  /* Get the qop-values from the qop-options */
  result = auth_digest_get_qop_values(qop_options, &qop_values);
  if(result)
    return result;

  /* We only support auth quality-of-protection */
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
    return CURLE_OUT_OF_MEMORY;

  Curl_MD5_update(ctxt, (const unsigned char *) userp,
                  curlx_uztoui(strlen(userp)));
  Curl_MD5_update(ctxt, (const unsigned char *) ":", 1);
  Curl_MD5_update(ctxt, (const unsigned char *) realm,
                  curlx_uztoui(strlen(realm)));
  Curl_MD5_update(ctxt, (const unsigned char *) ":", 1);
  Curl_MD5_update(ctxt, (const unsigned char *) passwdp,
                  curlx_uztoui(strlen(passwdp)));
  Curl_MD5_final(ctxt, digest);

  ctxt = Curl_MD5_init(Curl_DIGEST_MD5);
  if(!ctxt)
    return CURLE_OUT_OF_MEMORY;

  Curl_MD5_update(ctxt, (const unsigned char *) digest, MD5_DIGEST_LEN);
  Curl_MD5_update(ctxt, (const unsigned char *) ":", 1);
  Curl_MD5_update(ctxt, (const unsigned char *) nonce,
                  curlx_uztoui(strlen(nonce)));
  Curl_MD5_update(ctxt, (const unsigned char *) ":", 1);
  Curl_MD5_update(ctxt, (const unsigned char *) cnonce,
                  curlx_uztoui(strlen(cnonce)));
  Curl_MD5_final(ctxt, digest);

  /* Convert calculated 16 octet hex into 32 bytes string */
  for(i = 0; i < MD5_DIGEST_LEN; i++)
    snprintf(&HA1_hex[2 * i], 3, "%02x", digest[i]);

  /* Generate our SPN */
  spn = Curl_auth_build_spn(service, realm, NULL);
  if(!spn)
    return CURLE_OUT_OF_MEMORY;

  /* Calculate H(A2) */
  ctxt = Curl_MD5_init(Curl_DIGEST_MD5);
  if(!ctxt) {
    free(spn);

    return CURLE_OUT_OF_MEMORY;
  }

  Curl_MD5_update(ctxt, (const unsigned char *) method,
                  curlx_uztoui(strlen(method)));
  Curl_MD5_update(ctxt, (const unsigned char *) ":", 1);
  Curl_MD5_update(ctxt, (const unsigned char *) spn,
                  curlx_uztoui(strlen(spn)));
  Curl_MD5_final(ctxt, digest);

  for(i = 0; i < MD5_DIGEST_LEN; i++)
    snprintf(&HA2_hex[2 * i], 3, "%02x", digest[i]);

  /* Now calculate the response hash */
  ctxt = Curl_MD5_init(Curl_DIGEST_MD5);
  if(!ctxt) {
    free(spn);

    return CURLE_OUT_OF_MEMORY;
  }

  Curl_MD5_update(ctxt, (const unsigned char *) HA1_hex, 2 * MD5_DIGEST_LEN);
  Curl_MD5_update(ctxt, (const unsigned char *) ":", 1);
  Curl_MD5_update(ctxt, (const unsigned char *) nonce,
                  curlx_uztoui(strlen(nonce)));
  Curl_MD5_update(ctxt, (const unsigned char *) ":", 1);

  Curl_MD5_update(ctxt, (const unsigned char *) nonceCount,
                  curlx_uztoui(strlen(nonceCount)));
  Curl_MD5_update(ctxt, (const unsigned char *) ":", 1);
  Curl_MD5_update(ctxt, (const unsigned char *) cnonce,
                  curlx_uztoui(strlen(cnonce)));
  Curl_MD5_update(ctxt, (const unsigned char *) ":", 1);
  Curl_MD5_update(ctxt, (const unsigned char *) qop,
                  curlx_uztoui(strlen(qop)));
  Curl_MD5_update(ctxt, (const unsigned char *) ":", 1);

  Curl_MD5_update(ctxt, (const unsigned char *) HA2_hex, 2 * MD5_DIGEST_LEN);
  Curl_MD5_final(ctxt, digest);

  for(i = 0; i < MD5_DIGEST_LEN; i++)
    snprintf(&resp_hash_hex[2 * i], 3, "%02x", digest[i]);

  /* Generate the response */
  response = aprintf("username=\"%s\",realm=\"%s\",nonce=\"%s\","
                     "cnonce=\"%s\",nc=\"%s\",digest-uri=\"%s\",response=%s,"
                     "qop=%s",
                     userp, realm, nonce,
                     cnonce, nonceCount, spn, resp_hash_hex, qop);
  free(spn);
  if(!response)
    return CURLE_OUT_OF_MEMORY;

  /* Base64 encode the response */
  result = Curl_base64_encode(data, response, 0, outptr, outlen);

  free(response);

  return result;
}