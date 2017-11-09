CURLcode Curl_convert_clone(struct Curl_easy *data,
                           const char *indata,
                           size_t insize,
                           char **outbuf)
{
  char *convbuf;
  CURLcode result;

  convbuf = malloc(insize);
  if(!convbuf)
    return CURLE_OUT_OF_MEMORY;

  memcpy(convbuf, indata, insize);
  result = Curl_convert_to_network(data, convbuf, insize);
  if(result) {
    free(convbuf);
    return result;
  }

  *outbuf = convbuf; /* return the converted buffer */

  return CURLE_OK;
}