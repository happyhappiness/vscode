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