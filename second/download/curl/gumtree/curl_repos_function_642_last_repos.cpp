static Curl_addrinfo *fake_ai(void)
{
  static Curl_addrinfo *ai;

  ai = calloc(1, sizeof(Curl_addrinfo));
  if(!ai)
    return NULL;

  ai->ai_canonname = strdup("dummy");
  if(!ai->ai_canonname) {
    free(ai);
    return NULL;
  }

  ai->ai_addr = calloc(1, sizeof(struct sockaddr_in));
  if(!ai->ai_addr) {
    free(ai->ai_canonname);
    free(ai);
    return NULL;
  }

  ai->ai_family = AF_INET;
  ai->ai_addrlen = sizeof(struct sockaddr_in);

  return ai;
}