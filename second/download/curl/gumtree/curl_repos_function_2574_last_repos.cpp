CURLcode Curl_ssl_set_engine_default(struct Curl_easy *data)
{
  return Curl_ssl->set_engine_default(data);
}