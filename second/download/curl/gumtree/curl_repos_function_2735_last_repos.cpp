static void *Curl_gtls_get_internals(struct ssl_connect_data *connssl,
                                     CURLINFO info UNUSED_PARAM)
{
  (void)info;
  return BACKEND->session;
}