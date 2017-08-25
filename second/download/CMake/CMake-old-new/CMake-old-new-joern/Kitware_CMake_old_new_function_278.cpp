static CURLcode sasl_create_xoauth2_message(struct SessionHandle *data,
                                            const char *user,
                                            const char *bearer,
                                            char **outptr, size_t *outlen)
{
  CURLcode result = CURLE_OK;
  char *xoauth = NULL;

  /* Generate the message */
  xoauth = aprintf("user=%s\1auth=Bearer %s\1\1", user, bearer);
  if(!xoauth)
    return CURLE_OUT_OF_MEMORY;

  /* Base64 encode the reply */
  result = Curl_base64_encode(data, xoauth, strlen(xoauth), outptr, outlen);

  free(xoauth);

  return result;
}