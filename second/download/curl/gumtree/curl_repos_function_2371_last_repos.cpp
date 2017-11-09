static CURLcode Curl_ossl_set_engine_default(struct Curl_easy *data)
{
#ifdef HAVE_OPENSSL_ENGINE_H
  if(data->state.engine) {
    if(ENGINE_set_default(data->state.engine, ENGINE_METHOD_ALL) > 0) {
      infof(data, "set default crypto engine '%s'\n",
            ENGINE_get_id(data->state.engine));
    }
    else {
      failf(data, "set default crypto engine '%s' failed",
            ENGINE_get_id(data->state.engine));
      return CURLE_SSL_ENGINE_SETFAILED;
    }
  }
#else
  (void) data;
#endif
  return CURLE_OK;
}