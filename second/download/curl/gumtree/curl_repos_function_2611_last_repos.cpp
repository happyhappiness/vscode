CURLsslset curl_global_sslset(curl_sslbackend id, const char *name,
                              const curl_ssl_backend ***avail)
{
  int i;

  if(Curl_ssl != &Curl_ssl_multi)
    return id == Curl_ssl->info.id ? CURLSSLSET_OK : CURLSSLSET_TOO_LATE;

  for(i = 0; available_backends[i]; i++) {
    if(available_backends[i]->info.id == id ||
       (name && strcasecompare(available_backends[i]->info.name, name))) {
      multissl_init(available_backends[i]);
      return CURLSSLSET_OK;
    }
  }

  if(avail)
    *avail = (const curl_ssl_backend **)&available_backends;
  return CURLSSLSET_UNKNOWN_BACKEND;
}