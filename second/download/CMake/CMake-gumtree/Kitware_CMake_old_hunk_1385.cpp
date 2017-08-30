  return TRUE; /* OK, proceed */
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
Curl_addrinfo *Curl_ip2addr(in_addr_t num, char *hostname, int port)
{
  Curl_addrinfo *ai;
  struct hostent *h;
  struct in_addr *addrentry;
  struct namebuf buffer;
  struct namebuf *buf = &buffer;

  h = &buf->hostentry;
  h->h_addr_list = &buf->h_addr_list[0];
  addrentry = &buf->addrentry;
  addrentry->s_addr = num;
  h->h_addr_list[0] = (char*)addrentry;
  h->h_addr_list[1] = NULL;
  h->h_addrtype = AF_INET;
  h->h_length = sizeof(*addrentry);
  h->h_name = &buf->h_name[0];
  h->h_aliases = NULL;

  /* Now store the dotted version of the address */
  snprintf((char*)(h->h_name), 16, "%s", hostname);

  ai = Curl_he2ai(h, port);

  return ai;
}

#ifdef CURLRES_SYNCH /* the functions below are for synchronous resolves */

/*
 * Curl_getaddrinfo() - the ipv4 synchronous version.
 *
 * The original code to this function was once stolen from the Dancer source
 * code, written by Bjorn Reese, it has since been patched and modified
 * considerably.
 *
 * gethostbyname_r() is the thread-safe version of the gethostbyname()
 * function. When we build for plain IPv4, we attempt to use this
