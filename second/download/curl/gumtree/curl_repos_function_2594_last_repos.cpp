CURLcode Curl_none_random(struct Curl_easy *data UNUSED_PARAM,
                          unsigned char *entropy UNUSED_PARAM,
                          size_t length UNUSED_PARAM)
{
  (void)data;
  (void)entropy;
  (void)length;
  return CURLE_NOT_BUILT_IN;
}