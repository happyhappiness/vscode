CURLcode Curl_ssl_set_engine(struct Curl_easy *data, const char *engine)
{
  return Curl_ssl->set_engine(data, engine);
}