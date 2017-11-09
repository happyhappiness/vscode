CURLcode Curl_base64_encode(struct Curl_easy *data,
                            const char *inputbuff, size_t insize,
                            char **outptr, size_t *outlen)
{
  return base64_encode(base64, data, inputbuff, insize, outptr, outlen);
}