static CURLcode sasl_create_plain_message(struct SessionHandle *data,
                                          const char *userp,
                                          const char *passwdp,
                                          char **outptr, size_t *outlen)
{
  CURLcode result;
  char *plainauth;
  size_t ulen;
  size_t plen;

  ulen = strlen(userp);
  plen = strlen(passwdp);

  plainauth = malloc(2 * ulen + plen + 2);
  if(!plainauth) {
    *outlen = 0;
    *outptr = NULL;
    return CURLE_OUT_OF_MEMORY;
  }

  /* Calculate the reply */
  memcpy(plainauth, userp, ulen);
  plainauth[ulen] = '\0';
  memcpy(plainauth + ulen + 1, userp, ulen);
  plainauth[2 * ulen + 1] = '\0';
  memcpy(plainauth + 2 * ulen + 2, passwdp, plen);

  /* Base64 encode the reply */
  result = Curl_base64_encode(data, plainauth, 2 * ulen + plen + 2, outptr,
                              outlen);
  Curl_safefree(plainauth);
  return result;
}