CURLcode Curl_ssl_set_engine(struct Curl_easy *data, const char *engine)
{
  return curlssl_set_engine(data, engine);
}