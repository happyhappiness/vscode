static void *Curl_ossl_get_internals(struct ssl_connect_data *connssl,
                                     CURLINFO info)
{
  /* Legacy: CURLINFO_TLS_SESSION must return an SSL_CTX pointer. */
  return info == CURLINFO_TLS_SESSION ?
         (void *)BACKEND->ctx : (void *)BACKEND->handle;
}