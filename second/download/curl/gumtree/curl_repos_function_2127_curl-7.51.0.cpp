Curl_addrinfo *Curl_unix2addr(const char *path)
{
  Curl_addrinfo *ai;
  struct sockaddr_un *sa_un;
  size_t path_len;

  ai = calloc(1, sizeof(Curl_addrinfo));
  if(!ai)
    return NULL;
  if((ai->ai_addr = calloc(1, sizeof(struct sockaddr_un))) == NULL) {
    free(ai);
    return NULL;
  }
  /* sun_path must be able to store the NUL-terminated path */
  path_len = strlen(path);
  if(path_len >= sizeof(sa_un->sun_path)) {
    free(ai->ai_addr);
    free(ai);
    return NULL;
  }

  ai->ai_family = AF_UNIX;
  ai->ai_socktype = SOCK_STREAM; /* assume reliable transport for HTTP */
  ai->ai_addrlen = (curl_socklen_t) sizeof(struct sockaddr_un);
  sa_un = (void *) ai->ai_addr;
  sa_un->sun_family = AF_UNIX;
  memcpy(sa_un->sun_path, path, path_len + 1); /* copy NUL byte */
  return ai;
}