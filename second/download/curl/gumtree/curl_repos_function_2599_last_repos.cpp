CURLcode Curl_none_set_engine(struct Curl_easy *data UNUSED_PARAM,
                              const char *engine UNUSED_PARAM)
{
  (void)data;
  (void)engine;
  return CURLE_NOT_BUILT_IN;
}