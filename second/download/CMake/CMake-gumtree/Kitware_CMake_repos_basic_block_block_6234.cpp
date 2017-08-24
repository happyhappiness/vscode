{
  CURLcode result;
  char *plainauth;
  size_t ulen;
  size_t plen;
  size_t plainlen;

  *outlen = 0;
  *outptr = NULL;
  ulen = strlen(userp);
  plen = strlen(passwdp);

  /* Compute binary message length, checking for overflows. */
  plainlen = 2 * ulen;
  if(plainlen < ulen)
    return CURLE_OUT_OF_MEMORY;
  plainlen += plen;
  if(plainlen < plen)
    return CURLE_OUT_OF_MEMORY;
  plainlen += 2;
  if(plainlen < 2)
    return CURLE_OUT_OF_MEMORY;

  plainauth = malloc(plainlen);
  if(!plainauth)
    return CURLE_OUT_OF_MEMORY;

  /* Calculate the reply */
  memcpy(plainauth, userp, ulen);
  plainauth[ulen] = '\0';
  memcpy(plainauth + ulen + 1, userp, ulen);
  plainauth[2 * ulen + 1] = '\0';
  memcpy(plainauth + 2 * ulen + 2, passwdp, plen);

  /* Base64 encode the reply */
  result = Curl_base64_encode(data, plainauth, plainlen, outptr, outlen);
  free(plainauth);

  return result;
}