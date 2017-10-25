struct hostent *GetHost(struct UrlData *data,
                        char *hostname,
                        char *buf,
                        int buf_size )
{
  struct hostent *h = NULL;
  unsigned long in;

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
    MakeIP(ntohl(in),h->h_name,buf_size - (long)(h->h_name) + (long)buf);
  }
#if defined(HAVE_GETHOSTBYNAME_R)
  else {
    int h_errnop;
    memset(buf,0,buf_size);	/* workaround for gethostbyname_r bug in qnx nto */
#ifdef HAVE_GETHOSTBYNAME_R_5
    /* Solaris, IRIX and more */
    if ((h = gethostbyname_r(hostname,
                             (struct hostent *)buf,
                             buf + sizeof(struct hostent),
                             buf_size - sizeof(struct hostent),
                             &h_errnop)) == NULL )
#endif
#ifdef HAVE_GETHOSTBYNAME_R_6
    /* Linux */
    if( gethostbyname_r(hostname,
                        (struct hostent *)buf,
                        buf + sizeof(struct hostent),
                        buf_size - sizeof(struct hostent),
                        &h, /* DIFFERENCE */
                        &h_errnop))
#endif
#ifdef HAVE_GETHOSTBYNAME_R_3
    /* AIX, Digital Unix, HPUX 10, more? */

    /* August 4th, 2000. I don't have any such system around so I write this
       blindly in hope it might work or that someone else will help me fix
       this. */

    h = gethostbyname_r(hostname,
                        (struct hostent *)buf,
                        (struct hostent_data *)(buf + sizeof(struct hostent)));
    h_errnop= errno; /* we don't deal with this, but set it anyway */
    if(NULL == h)
#endif
      {
      infof(data, "gethostbyname_r(2) failed for %s\n", hostname);
    }
#else
  else {
    if ((h = gethostbyname(hostname)) == NULL ) {
      infof(data, "gethostbyname(2) failed for %s\n", hostname);
    }
#endif
  }
  return (h);
}