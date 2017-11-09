int
Curl_getaddrinfo_ex(const char *nodename,
                    const char *servname,
                    const struct addrinfo *hints,
                    Curl_addrinfo **result)
{
  const struct addrinfo *ai;
  struct addrinfo *aihead;
  Curl_addrinfo *cafirst = NULL;
  Curl_addrinfo *calast = NULL;
  Curl_addrinfo *ca;
  size_t ss_size;
  int error;

  *result = NULL; /* assume failure */

  error = getaddrinfo(nodename, servname, hints, &aihead);
  if(error)
    return error;

  /* traverse the addrinfo list */

  for(ai = aihead; ai != NULL; ai = ai->ai_next) {

    /* ignore elements with unsupported address family, */
    /* settle family-specific sockaddr structure size.  */
    if(ai->ai_family == AF_INET)
      ss_size = sizeof(struct sockaddr_in);
#ifdef ENABLE_IPV6
    else if(ai->ai_family == AF_INET6)
      ss_size = sizeof(struct sockaddr_in6);
#endif
    else
      continue;

    /* ignore elements without required address info */
    if((ai->ai_addr == NULL) || !(ai->ai_addrlen > 0))
      continue;

    /* ignore elements with bogus address size */
    if((size_t)ai->ai_addrlen < ss_size)
      continue;

    ca = malloc(sizeof(Curl_addrinfo));
    if(!ca) {
      error = EAI_MEMORY;
      break;
    }

    /* copy each structure member individually, member ordering, */
    /* size, or padding might be different for each platform.    */

    ca->ai_flags     = ai->ai_flags;
    ca->ai_family    = ai->ai_family;
    ca->ai_socktype  = ai->ai_socktype;
    ca->ai_protocol  = ai->ai_protocol;
    ca->ai_addrlen   = (curl_socklen_t)ss_size;
    ca->ai_addr      = NULL;
    ca->ai_canonname = NULL;
    ca->ai_next      = NULL;

    ca->ai_addr = malloc(ss_size);
    if(!ca->ai_addr) {
      error = EAI_MEMORY;
      free(ca);
      break;
    }
    memcpy(ca->ai_addr, ai->ai_addr, ss_size);

    if(ai->ai_canonname != NULL) {
      ca->ai_canonname = strdup(ai->ai_canonname);
      if(!ca->ai_canonname) {
        error = EAI_MEMORY;
        free(ca->ai_addr);
        free(ca);
        break;
      }
    }

    /* if the return list is empty, this becomes the first element */
    if(!cafirst)
      cafirst = ca;

    /* add this element last in the return list */
    if(calast)
      calast->ai_next = ca;
    calast = ca;

  }

  /* destroy the addrinfo list */
  if(aihead)
    freeaddrinfo(aihead);

  /* if we failed, also destroy the Curl_addrinfo list */
  if(error) {
    Curl_freeaddrinfo(cafirst);
    cafirst = NULL;
  }
  else if(!cafirst) {
#ifdef EAI_NONAME
    /* rfc3493 conformant */
    error = EAI_NONAME;
#else
    /* rfc3493 obsoleted */
    error = EAI_NODATA;
#endif
#ifdef USE_WINSOCK
    SET_SOCKERRNO(error);
#endif
  }

  *result = cafirst;

  /* This is not a CURLcode */
  return error;
}