CURLcode Curl_auth_create_spnego_message(struct Curl_easy *data,
                                         struct negotiatedata *nego,
                                         char **outptr, size_t *outlen)
{
  CURLcode result;

  /* Base64 encode the already generated response */
  result = Curl_base64_encode(data,
                              (const char *) nego->output_token,
                              nego->output_token_length,
                              outptr, outlen);

  if(result)
    return result;

  if(!*outptr || !*outlen) {
    free(*outptr);
    return CURLE_REMOTE_ACCESS_DENIED;
  }

  return CURLE_OK;
}