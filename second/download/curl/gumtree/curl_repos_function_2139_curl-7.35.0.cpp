CURLcode Curl_ssl_set_engine(struct SessionHandle *data, const char *engine)
{
  return curlssl_set_engine(data, engine);
}