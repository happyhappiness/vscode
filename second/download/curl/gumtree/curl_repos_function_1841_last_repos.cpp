CURLcode Curl_base64url_encode(struct Curl_easy *data,
                               const char *inputbuff, size_t insize,
                               char **outptr, size_t *outlen)
{
  return base64_encode(base64url, data, inputbuff, insize, outptr, outlen);
}