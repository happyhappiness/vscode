static void *Curl_axtls_get_internals(struct ssl_connect_data *connssl,
                                      CURLINFO info UNUSED_PARAM)
{
  (void)info;
  return BACKEND->ssl;
}