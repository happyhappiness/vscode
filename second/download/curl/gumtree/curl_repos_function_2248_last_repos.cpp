CURLcode Curl_input_digest(struct connectdata *conn,
                           bool proxy,
                           const char *header) /* rest of the *-authenticate:
                                                  header */
{
  struct Curl_easy *data = conn->data;

  /* Point to the correct struct with this */
  struct digestdata *digest;

  if(proxy) {
    digest = &data->state.proxydigest;
  }
  else {
    digest = &data->state.digest;
  }

  if(!checkprefix("Digest", header))
    return CURLE_BAD_CONTENT_ENCODING;

  header += strlen("Digest");
  while(*header && ISSPACE(*header))
    header++;

  return Curl_auth_decode_digest_http_message(header, digest);
}