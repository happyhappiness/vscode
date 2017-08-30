 * returns a pointer to the malloc()ed copy. You need to call free() on the
 * returned buffer when you're done with it.
 */
Curl_addrinfo *Curl_addrinfo_copy(const void *org, int port)
{
  const struct hostent *orig = org;

  return Curl_he2ai(orig, port);
}
#endif /* CURLRES_ADDRINFO_COPY */

/***********************************************************************
 * Only for plain-ipv4 and c-ares builds
 **********************************************************************/

#if defined(CURLRES_IPV4) || defined(CURLRES_ARES)
/*
 * This is a function for freeing name information in a protocol independent
 * way.
 */
void Curl_freeaddrinfo(Curl_addrinfo *ai)
{
  Curl_addrinfo *next;

  /* walk over the list and free all entries */
  while(ai) {
    next = ai->ai_next;
    free(ai);
    ai = next;
  }
}

struct namebuf {
  struct hostent hostentry;
  char *h_addr_list[2];
  struct in_addr addrentry;
  char h_name[16]; /* 123.123.123.123 = 15 letters is maximum */
};

/*
 * Curl_ip2addr() takes a 32bit ipv4 internet address as input parameter
 * together with a pointer to the string version of the address, and it
 * returns a Curl_addrinfo chain filled in correctly with information for this
 * address/host.
 *
 * The input parameters ARE NOT checked for validity but they are expected
 * to have been checked already when this is called.
 */
Curl_addrinfo *Curl_ip2addr(in_addr_t num, const char *hostname, int port)
{
  Curl_addrinfo *ai;
  struct hostent *h;
  struct in_addr *addrentry;
  struct namebuf buffer;
  struct namebuf *buf = &buffer;

  h = &buf->hostentry;
  h->h_addr_list = &buf->h_addr_list[0];
  addrentry = &buf->addrentry;
#ifdef _CRAYC
  /* On UNICOS, s_addr is a bit field and for some reason assigning to it
   * doesn't work.  There must be a better fix than this ugly hack.
   */
  memcpy(addrentry, &num, SIZEOF_in_addr);
#else
  addrentry->s_addr = num;
#endif
  h->h_addr_list[0] = (char*)addrentry;
  h->h_addr_list[1] = NULL;
  h->h_addrtype = AF_INET;
  h->h_length = sizeof(*addrentry);
  h->h_name = &buf->h_name[0];
  h->h_aliases = NULL;

  /* Now store the dotted version of the address */
  snprintf((char *)h->h_name, 16, "%s", hostname);

  ai = Curl_he2ai(h, port);

  return ai;
}
#endif

