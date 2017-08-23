CURLcode Curl_auth_create_oauth_bearer_message(struct Curl_easy *data,
                                               const char *user,
                                               const char *host,
                                               const long port,
                                               const char *bearer,
                                               char **outptr, size_t *outlen)
{
  CURLcode result = CURLE_OK;
  char *oauth = NULL;

  /* Generate the message */
  if(host == NULL && (port == 0 || port == 80))
    oauth = aprintf("user=%s\1auth=Bearer %s\1\1", user, bearer);
  else if(port == 0 || port == 80)
    oauth = aprintf("user=%s\1host=%s\1auth=Bearer %s\1\1", user, host,
                    bearer);
  else
    oauth = aprintf("user=%s\1host=%s\1port=%ld\1auth=Bearer %s\1\1", user,
                    host, port, bearer);
  if(!oauth)
    return CURLE_OUT_OF_MEMORY;

  /* Base64 encode the reply */
  result = Curl_base64_encode(data, oauth, strlen(oauth), outptr, outlen);

  free(oauth);

  return result;
}