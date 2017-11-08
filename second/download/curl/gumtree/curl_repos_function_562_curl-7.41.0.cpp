static Curl_addrinfo *fake_ai(void)
{
  static Curl_addrinfo *ai;
  int ss_size;

  ss_size = sizeof (struct sockaddr_in);

  if((ai = calloc(1, sizeof(Curl_addrinfo))) == NULL)
    return NULL;

  if((ai->ai_canonname = strdup("dummy")) == NULL) {
    free(ai);
    return NULL;
  }

  if((ai->ai_addr = calloc(1, ss_size)) == NULL) {
    free(ai->ai_canonname);
    free(ai);
    return NULL;
  }

  ai->ai_family = AF_INET;
  ai->ai_addrlen = ss_size;

  return ai;
}