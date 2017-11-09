static void *Curl_multissl_get_internals(struct ssl_connect_data *connssl,
                                         CURLINFO info)
{
  if(multissl_init(NULL))
    return NULL;
  return Curl_ssl->get_internals(connssl, info);
}