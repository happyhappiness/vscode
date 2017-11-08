Curl_addrinfo *Curl_he2ai(const struct hostent *he, int port)
{
  Curl_addrinfo *ai;
  Curl_addrinfo *prevai = NULL;
  Curl_addrinfo *firstai = NULL;
  struct sockaddr_in *addr;
  int i;
  struct in_addr *curr;

  if(!he)
    /* no input == no output! */
    return NULL;

  for(i=0; (curr = (struct in_addr *)he->h_addr_list[i]) != NULL; i++) {

    ai = calloc(1, sizeof(Curl_addrinfo) + sizeof(struct sockaddr_in));

    if(!ai)
      break;

    if(!firstai)
      /* store the pointer we want to return from this function */
      firstai = ai;

    if(prevai)
      /* make the previous entry point to this */
      prevai->ai_next = ai;

    ai->ai_family = AF_INET;              /* we only support this */

    /* we return all names as STREAM, so when using this address for TFTP
       the type must be ignored and conn->socktype be used instead! */
    ai->ai_socktype = SOCK_STREAM;

    ai->ai_addrlen = sizeof(struct sockaddr_in);
    /* make the ai_addr point to the address immediately following this struct
       and use that area to store the address */
    ai->ai_addr = (struct sockaddr *) ((char*)ai + sizeof(Curl_addrinfo));

    /* FIXME: need to free this eventually */
    ai->ai_canonname = strdup(he->h_name);

    /* leave the rest of the struct filled with zero */

    addr = (struct sockaddr_in *)ai->ai_addr; /* storage area for this info */

    memcpy((char *)&(addr->sin_addr), curr, sizeof(struct in_addr));
    addr->sin_family = (unsigned short)(he->h_addrtype);
    addr->sin_port = htons((unsigned short)port);

    prevai = ai;
  }
  return firstai;
}