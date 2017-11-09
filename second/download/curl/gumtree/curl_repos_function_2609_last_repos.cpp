static size_t Curl_multissl_version(char *buffer, size_t size)
{
  static const struct Curl_ssl *selected;
  static char backends[200];
  static size_t total;
  const struct Curl_ssl *current;

  current = Curl_ssl == &Curl_ssl_multi ? available_backends[0] : Curl_ssl;

  if(current != selected) {
    char *p = backends;
    int i;

    selected = current;

    for(i = 0; available_backends[i]; i++) {
      if(i)
        *(p++) = ' ';
      if(selected != available_backends[i])
        *(p++) = '(';
      p += available_backends[i]->version(p, backends + sizeof(backends) - p);
      if(selected != available_backends[i])
        *(p++) = ')';
    }
    *p = '\0';
    total = p - backends;
  }

  if(size < total)
    memcpy(buffer, backends, total + 1);
  else {
    memcpy(buffer, backends, size - 1);
    buffer[size - 1] = '\0';
  }

  return total;
}