struct hostent *Curl_gethost(struct SessionHandle *data,
                             char *hostname,
                             char **bufp)
{
  struct hostent *h = NULL;
  unsigned long in;
  int ret; /* this variable is unused on several platforms but used on some */

#define CURL_NAMELOOKUP_SIZE 9000
  /* Allocate enough memory to hold the full name information structs and
   * everything. OSF1 is known to require at least 8872 bytes. The buffer
   * required for storing all possible aliases and IP numbers is according to
   * Stevens' Unix Network Programming 2nd editor, p. 304: 8192 bytes! */
  char *buf = (char *)malloc(CURL_NAMELOOKUP_SIZE);
  if(!buf)
    return NULL; /* major failure */
  *bufp = buf;

  ret = 0; /* to prevent the compiler warning */

  if ( (in=inet_addr(hostname)) != INADDR_NONE ) {
    struct in_addr *addrentry;

    h = (struct hostent*)buf;
    h->h_addr_list = (char**)(buf + sizeof(*h));
    addrentry = (struct in_addr*)(h->h_addr_list + 2);
    addrentry->s_addr = in;
    h->h_addr_list[0] = (char*)addrentry;
    h->h_addr_list[1] = NULL;
    h->h_addrtype = AF_INET;
    h->h_length = sizeof(*addrentry);
    h->h_name = *(h->h_addr_list) + h->h_length;
    /* bad one h->h_name = (char*)(h->h_addr_list + h->h_length); */
    MakeIP(ntohl(in),h->h_name, CURL_NAMELOOKUP_SIZE - (long)(h->h_name) + (long)buf);
  }
#if defined(HAVE_GETHOSTBYNAME_R)
  else {
    int h_errnop;
     /* Workaround for gethostbyname_r bug in qnx nto. It is also _required_
        for some of these functions. */
    memset(buf, 0, CURL_NAMELOOKUP_SIZE);
#ifdef HAVE_GETHOSTBYNAME_R_5
    /* Solaris, IRIX and more */
    if ((h = gethostbyname_r(hostname,
                             (struct hostent *)buf,
                             buf + sizeof(struct hostent),
                             CURL_NAMELOOKUP_SIZE - sizeof(struct hostent),
                             &h_errnop)) == NULL )
#endif
#ifdef HAVE_GETHOSTBYNAME_R_6
    /* Linux */
    if( gethostbyname_r(hostname,
                        (struct hostent *)buf,
                        buf + sizeof(struct hostent),
                        CURL_NAMELOOKUP_SIZE - sizeof(struct hostent),
                        &h, /* DIFFERENCE */
                        &h_errnop))
#endif
#ifdef HAVE_GETHOSTBYNAME_R_3
    /* AIX, Digital Unix, HPUX 10, more? */

    if(CURL_NAMELOOKUP_SIZE >=
       (sizeof(struct hostent)+sizeof(struct hostent_data)))

      /* August 22nd, 2000: Albert Chin-A-Young brought an updated version
       * that should work! September 20: Richard Prescott worked on the buffer
       * size dilemma. */

      ret = gethostbyname_r(hostname,
                          (struct hostent *)buf,
                          (struct hostent_data *)(buf + sizeof(struct hostent)));
    else
      ret = -1; /* failure, too smallish buffer size */
    
    /* result expected in h */
    h = (struct hostent*)buf;
    h_errnop= errno; /* we don't deal with this, but set it anyway */
    if(ret)
#endif
      {
      infof(data, "gethostbyname_r(2) failed for %s\n", hostname);
      h = NULL; /* set return code to NULL */
      free(buf);
      *bufp=NULL;
    }
#else
  else {
    if ((h = gethostbyname(hostname)) == NULL ) {
      infof(data, "gethostbyname(2) failed for %s\n", hostname);
      free(buf);
      *bufp=NULL;
    }
#endif
  }
  return (h);
}