static Curl_addrinfo *my_getaddrinfo(struct SessionHandle *data,
                                     char *hostname,
                                     int port,
                                     char **bufp)
{
  struct hostent *h = NULL;
  in_addr_t in;
  int ret; /* this variable is unused on several platforms but used on some */

#define CURL_NAMELOOKUP_SIZE 9000
  /* Allocate enough memory to hold the full name information structs and
   * everything. OSF1 is known to require at least 8872 bytes. The buffer
   * required for storing all possible aliases and IP numbers is according to
   * Stevens' Unix Network Programming 2nd editor, p. 304: 8192 bytes! */
  port=0; /* unused in IPv4 code */
  ret = 0; /* to prevent the compiler warning */

  if ( (in=inet_addr(hostname)) != INADDR_NONE ) {
    struct in_addr *addrentry;
    struct namebuf {
        struct hostent hostentry;
        char *h_addr_list[2];
        struct in_addr addrentry;
        char h_name[128];
    } *buf = (struct namebuf *)malloc(sizeof(struct namebuf));
    if(!buf)
      return NULL; /* major failure */
    *bufp = (char *)buf;

    h = &buf->hostentry;
    h->h_addr_list = &buf->h_addr_list[0];
    addrentry = &buf->addrentry;
    addrentry->s_addr = in;
    h->h_addr_list[0] = (char*)addrentry;
    h->h_addr_list[1] = NULL;
    h->h_addrtype = AF_INET;
    h->h_length = sizeof(*addrentry);
    h->h_name = &buf->h_name[0];
    MakeIP(ntohl(in), (char *)h->h_name, sizeof(buf->h_name));
  }
#if defined(HAVE_GETHOSTBYNAME_R)
  else {
    int h_errnop;
    int res=ERANGE;
    int step_size=200;
    int *buf = (int *)malloc(CURL_NAMELOOKUP_SIZE);
    if(!buf)
      return NULL; /* major failure */
    *bufp=(char *)buf;

     /* Workaround for gethostbyname_r bug in qnx nto. It is also _required_
        for some of these functions. */
    memset(buf, 0, CURL_NAMELOOKUP_SIZE);
#ifdef HAVE_GETHOSTBYNAME_R_5
    /* Solaris, IRIX and more */
    (void)res; /* prevent compiler warning */
    while(!h) {
      h = gethostbyname_r(hostname,
                          (struct hostent *)buf,
                          (char *)buf + sizeof(struct hostent),
                          step_size - sizeof(struct hostent),
                          &h_errnop);

      /* If the buffer is too small, it returns NULL and sets errno to
         ERANGE. The errno is thread safe if this is compiled with
         -D_REENTRANT as then the 'errno' variable is a macro defined to
         get used properly for threads. */

      if(h || (errno != ERANGE))
        break;
      
      step_size+=200;
    }

#ifdef MALLOCDEBUG
    infof(data, "gethostbyname_r() uses %d bytes\n", step_size);
#endif

    if(h) {
      int offset;
      h=(struct hostent *)realloc(buf, step_size);
      offset=(long)h-(long)buf;
      hostcache_fixoffset(h, offset);
      buf=(int *)h;
      *bufp=(char *)buf;
    }
    else
#endif
#ifdef HAVE_GETHOSTBYNAME_R_6
    /* Linux */
    do {
      res=gethostbyname_r(hostname,
			  (struct hostent *)buf,
			  (char *)buf + sizeof(struct hostent),
			  step_size - sizeof(struct hostent),
			  &h, /* DIFFERENCE */
			  &h_errnop);
      /* Redhat 8, using glibc 2.2.93 changed the behavior. Now all of a
         sudden this function returns EAGAIN if the given buffer size is too
         small. Previous versions are known to return ERANGE for the same
         problem.

         This wouldn't be such a big problem if older versions wouldn't
         sometimes return EAGAIN on a common failure case. Alas, we can't
         assume that EAGAIN *or* ERANGE means ERANGE for any given version of
         glibc.

         For now, we do that and thus we may call the function repeatedly and
         fail for older glibc versions that return EAGAIN, until we run out
         of buffer size (step_size grows beyond CURL_NAMELOOKUP_SIZE).

         If anyone has a better fix, please tell us!
      */

      if((ERANGE == res) || (EAGAIN == res)) {
	step_size+=200;
	continue;
      }
      break;
    } while(step_size <= CURL_NAMELOOKUP_SIZE);

    if(!h) /* failure */
      res=1;
    
#ifdef MALLOCDEBUG
    infof(data, "gethostbyname_r() uses %d bytes\n", step_size);
#endif
    if(!res) {
      int offset;
      h=(struct hostent *)realloc(buf, step_size);
      offset=(long)h-(long)buf;
      hostcache_fixoffset(h, offset);
      buf=(int *)h;
      *bufp=(char *)buf;
    }
    else
#endif
#ifdef HAVE_GETHOSTBYNAME_R_3
    /* AIX, Digital Unix, HPUX 10, more? */

    /* For AIX 4.3 or later, we don't use gethostbyname_r() at all, because of
       the plain fact that it does not return unique full buffers on each
       call, but instead several of the pointers in the hostent structs will
       point to the same actual data! This have the unfortunate down-side that
       our caching system breaks down horribly. Luckily for us though, AIX 4.3
       and more recent versions have a completely thread-safe libc where all
       the data is stored in thread-specific memory areas making calls to the
       plain old gethostbyname() work fine even for multi-threaded programs.
       
       This AIX 4.3 or later detection is all made in the configure script.

       Troels Walsted Hansen helped us work this out on March 3rd, 2003. */

    if(CURL_NAMELOOKUP_SIZE >=
       (sizeof(struct hostent)+sizeof(struct hostent_data)))

      /* August 22nd, 2000: Albert Chin-A-Young brought an updated version
       * that should work! September 20: Richard Prescott worked on the buffer
       * size dilemma. */

      ret = gethostbyname_r(hostname,
                            (struct hostent *)buf,
                            (struct hostent_data *)((char *)buf +
                                                    sizeof(struct hostent)));
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
      *bufp=NULL;
    }
    else 
    {
      char *buf=(char *)malloc(CURL_NAMELOOKUP_SIZE);
      /* we make a copy of the hostent right now, right here, as the
         static one we got a pointer to might get removed when we don't
         want/expect that */
      h = pack_hostent(&buf, h);
      *bufp=(char *)buf;
    }
#endif
  }
  return (h);
}