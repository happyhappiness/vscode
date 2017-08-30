 */

static void

ftp_pasv_verbose(struct connectdata *conn,

                 Curl_ipconnect *addr,

                 char *newhost, /* ascii version */

                 int port)

{

#ifndef ENABLE_IPV6

  /*****************************************************************

   *

   * IPv4-only code section

   */



  struct in_addr in;

  struct hostent * answer;



#ifdef HAVE_INET_NTOA_R

  char ntoa_buf[64];

#endif

  /* The array size trick below is to make this a large chunk of memory

     suitably 8-byte aligned on 64-bit platforms. This was thoughtfully

     suggested by Philip Gladstone. */

  long bigbuf[9000 / sizeof(long)];



#if defined(HAVE_INET_ADDR)

  in_addr_t address;

# if defined(HAVE_GETHOSTBYADDR_R)

  int h_errnop;

# endif

  char *hostent_buf = (char *)bigbuf; /* get a char * to the buffer */

  (void)hostent_buf;

  address = inet_addr(newhost);

# ifdef HAVE_GETHOSTBYADDR_R



#  ifdef HAVE_GETHOSTBYADDR_R_5

  /* AIX, Digital Unix (OSF1, Tru64) style:

     extern int gethostbyaddr_r(char *addr, size_t len, int type,

     struct hostent *htent, struct hostent_data *ht_data); */



  /* Fred Noz helped me try this out, now it at least compiles! */



  /* Bjorn Reese (November 28 2001):

     The Tru64 man page on gethostbyaddr_r() says that

     the hostent struct must be filled with zeroes before the call to

     gethostbyaddr_r(). 



     ... as must be struct hostent_data Craig Markwardt 19 Sep 2002. */



  memset(hostent_buf, 0, sizeof(struct hostent)+sizeof(struct hostent_data));



  if(gethostbyaddr_r((char *) &address,

                     sizeof(address), AF_INET,

                     (struct hostent *)hostent_buf,

                     (struct hostent_data *)(hostent_buf + sizeof(*answer))))

    answer=NULL;

  else

    answer=(struct hostent *)hostent_buf;

                           

#  endif

#  ifdef HAVE_GETHOSTBYADDR_R_7

  /* Solaris and IRIX */

  answer = gethostbyaddr_r((char *) &address, sizeof(address), AF_INET,

                           (struct hostent *)bigbuf,

                           hostent_buf + sizeof(*answer),

                           sizeof(bigbuf) - sizeof(*answer),

                           &h_errnop);

#  endif

#  ifdef HAVE_GETHOSTBYADDR_R_8

  /* Linux style */

  if(gethostbyaddr_r((char *) &address, sizeof(address), AF_INET,

                     (struct hostent *)hostent_buf,

                     hostent_buf + sizeof(*answer),

                     sizeof(bigbuf) - sizeof(*answer),

                     &answer,

                     &h_errnop))

    answer=NULL; /* error */

#  endif

        

# else

  answer = gethostbyaddr((char *) &address, sizeof(address), AF_INET);

# endif

#else

  answer = NULL;

#endif

  (void) memcpy(&in.s_addr, addr, sizeof (Curl_ipconnect));

  infof(conn->data, "Connecting to %s (%s) port %u\n",

        answer?answer->h_name:newhost,

#if defined(HAVE_INET_NTOA_R)

        inet_ntoa_r(in, ntoa_buf, sizeof(ntoa_buf)),

#else

        inet_ntoa(in),

#endif

        port);



#else

  /*****************************************************************

   *

   * IPv6-only code section

   */

  char hbuf[NI_MAXHOST]; /* ~1KB */

  char nbuf[NI_MAXHOST]; /* ~1KB */

  char sbuf[NI_MAXSERV]; /* around 32 */

#ifdef NI_WITHSCOPEID

  const int niflags = NI_NUMERICHOST | NI_NUMERICSERV | NI_WITHSCOPEID;

#else

  const int niflags = NI_NUMERICHOST | NI_NUMERICSERV;

#endif

  port = 0; /* unused, prevent warning */

  if (getnameinfo(addr->ai_addr, addr->ai_addrlen,

                  nbuf, sizeof(nbuf), sbuf, sizeof(sbuf), niflags)) {

    snprintf(nbuf, sizeof(nbuf), "?");

    snprintf(sbuf, sizeof(sbuf), "?");

  }

        

  if (getnameinfo(addr->ai_addr, addr->ai_addrlen,

                  hbuf, sizeof(hbuf), NULL, 0, 0)) {

    infof(conn->data, "Connecting to %s (%s) port %s\n", nbuf, newhost, sbuf);

  }

  else {

    infof(conn->data, "Connecting to %s (%s) port %s\n", hbuf, nbuf, sbuf);

  }

#endif

}



/***********************************************************************

