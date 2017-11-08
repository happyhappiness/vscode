Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
                                char *hostname,
                                int port,
                                int *waitp)
{
  Curl_addrinfo *ai = NULL;
  struct hostent *h = NULL;
  in_addr_t in;
  struct SessionHandle *data = conn->data;
  struct hostent *buf = NULL;

  (void)port; /* unused in IPv4 code */

  *waitp = 0; /* don't wait, we act synchronously */

  if(1 == Curl_inet_pton(AF_INET, hostname, &in))
    /* This is a dotted IP address 123.123.123.123-style */
    return Curl_ip2addr(in, hostname, port);

#if defined(HAVE_GETHOSTBYNAME_R)
  /*
   * gethostbyname_r() is the preferred resolve function for many platforms.
   * Since there are three different versions of it, the following code is
   * somewhat #ifdef-ridden.
   */
  else {
    int h_errnop;
    int res=ERANGE;

    buf = (struct hostent *)calloc(CURL_HOSTENT_SIZE, 1);
    if(!buf)
      return NULL; /* major failure */
    /*
     * The clearing of the buffer is a workaround for a gethostbyname_r bug in
     * qnx nto and it is also _required_ for some of these functions on some
     * platforms.
     */

#ifdef HAVE_GETHOSTBYNAME_R_5
    /* Solaris, IRIX and more */
    (void)res; /* prevent compiler warning */
    h = gethostbyname_r(hostname,
                        (struct hostent *)buf,
                        (char *)buf + sizeof(struct hostent),
                        CURL_HOSTENT_SIZE - sizeof(struct hostent),
                        &h_errnop);

    /* If the buffer is too small, it returns NULL and sets errno to
     * ERANGE. The errno is thread safe if this is compiled with
     * -D_REENTRANT as then the 'errno' variable is a macro defined to get
     * used properly for threads.
     */

    if(h) {
      ;
    }
    else
#endif /* HAVE_GETHOSTBYNAME_R_5 */
#ifdef HAVE_GETHOSTBYNAME_R_6
    /* Linux */

    res=gethostbyname_r(hostname,
                        (struct hostent *)buf,
                        (char *)buf + sizeof(struct hostent),
                        CURL_HOSTENT_SIZE - sizeof(struct hostent),
                        &h, /* DIFFERENCE */
                        &h_errnop);
    /* Redhat 8, using glibc 2.2.93 changed the behavior. Now all of a
     * sudden this function returns EAGAIN if the given buffer size is too
     * small. Previous versions are known to return ERANGE for the same
     * problem.
     *
     * This wouldn't be such a big problem if older versions wouldn't
     * sometimes return EAGAIN on a common failure case. Alas, we can't
     * assume that EAGAIN *or* ERANGE means ERANGE for any given version of
     * glibc.
     *
     * For now, we do that and thus we may call the function repeatedly and
     * fail for older glibc versions that return EAGAIN, until we run out of
     * buffer size (step_size grows beyond CURL_HOSTENT_SIZE).
     *
     * If anyone has a better fix, please tell us!
     *
     * -------------------------------------------------------------------
     *
     * On October 23rd 2003, Dan C dug up more details on the mysteries of
     * gethostbyname_r() in glibc:
     *
     * In glibc 2.2.5 the interface is different (this has also been
     * discovered in glibc 2.1.1-6 as shipped by Redhat 6). What I can't
     * explain, is that tests performed on glibc 2.2.4-34 and 2.2.4-32
     * (shipped/upgraded by Redhat 7.2) don't show this behavior!
     *
     * In this "buggy" version, the return code is -1 on error and 'errno'
     * is set to the ERANGE or EAGAIN code. Note that 'errno' is not a
     * thread-safe variable.
     */

    if(!h) /* failure */
#endif/* HAVE_GETHOSTBYNAME_R_6 */
#ifdef HAVE_GETHOSTBYNAME_R_3
    /* AIX, Digital Unix/Tru64, HPUX 10, more? */

    /* For AIX 4.3 or later, we don't use gethostbyname_r() at all, because of
     * the plain fact that it does not return unique full buffers on each
     * call, but instead several of the pointers in the hostent structs will
     * point to the same actual data! This have the unfortunate down-side that
     * our caching system breaks down horribly. Luckily for us though, AIX 4.3
     * and more recent versions have a "completely thread-safe"[*] libc where
     * all the data is stored in thread-specific memory areas making calls to
     * the plain old gethostbyname() work fine even for multi-threaded
     * programs.
     *
     * This AIX 4.3 or later detection is all made in the configure script.
     *
     * Troels Walsted Hansen helped us work this out on March 3rd, 2003.
     *
     * [*] = much later we've found out that it isn't at all "completely
     * thread-safe", but at least the gethostbyname() function is.
     */

    if(CURL_HOSTENT_SIZE >=
       (sizeof(struct hostent)+sizeof(struct hostent_data))) {

      /* August 22nd, 2000: Albert Chin-A-Young brought an updated version
       * that should work! September 20: Richard Prescott worked on the buffer
       * size dilemma.
       */

      res = gethostbyname_r(hostname,
                            (struct hostent *)buf,
                            (struct hostent_data *)((char *)buf +
                                                    sizeof(struct hostent)));
      h_errnop= errno; /* we don't deal with this, but set it anyway */
    }
    else
      res = -1; /* failure, too smallish buffer size */

    if(!res) { /* success */

      h = buf; /* result expected in h */

      /* This is the worst kind of the different gethostbyname_r() interfaces.
       * Since we don't know how big buffer this particular lookup required,
       * we can't realloc down the huge alloc without doing closer analysis of
       * the returned data. Thus, we always use CURL_HOSTENT_SIZE for every
       * name lookup. Fixing this would require an extra malloc() and then
       * calling Curl_addrinfo_copy() that subsequent realloc()s down the new
       * memory area to the actually used amount.
       */
    }
    else
#endif /* HAVE_GETHOSTBYNAME_R_3 */
      {
      infof(data, "gethostbyname_r(2) failed for %s\n", hostname);
      h = NULL; /* set return code to NULL */
      free(buf);
    }
#else /* HAVE_GETHOSTBYNAME_R */
    /*
     * Here is code for platforms that don't have gethostbyname_r() or for
     * which the gethostbyname() is the preferred() function.
     */
  else {
    h = gethostbyname(hostname);
    if (!h)
      infof(data, "gethostbyname(2) failed for %s\n", hostname);
#endif /*HAVE_GETHOSTBYNAME_R */
  }

  if(h) {
    ai = Curl_he2ai(h, port);

    if (buf) /* used a *_r() function */
      free(buf);
  }

  return ai;
}

#endif /* CURLRES_SYNCH */

/*
 * Curl_he2ai() translates from a hostent struct to a Curl_addrinfo struct.
 * The Curl_addrinfo is meant to work like the addrinfo struct does for IPv6
 * stacks, but for all hosts and environments.

struct Curl_addrinfo {
  int     ai_flags;
  int     ai_family;
  int     ai_socktype;
  int     ai_protocol;
  size_t  ai_addrlen;
  struct sockaddr *ai_addr;
  char   *ai_canonname;
  struct addrinfo *ai_next;
};

struct hostent {
  char    *h_name;        * official name of host *
  char    **h_aliases;    * alias list *
  int     h_addrtype;     * host address type *
  int     h_length;       * length of address *
  char    **h_addr_list;  * list of addresses *
}
#define h_addr  h_addr_list[0]  * for backward compatibility *

*/

Curl_addrinfo *Curl_he2ai(struct hostent *he, int port)
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

  for(i=0; (curr = (struct in_addr *)he->h_addr_list[i]); i++) {

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
    ai->ai_socktype = SOCK_STREAM;        /* we only support this */
    ai->ai_addrlen = sizeof(struct sockaddr_in);
    /* make the ai_addr point to the address immediately following this struct
       and use that area to store the address */
    ai->ai_addr = (struct sockaddr *) ((char*)ai + sizeof(Curl_addrinfo));

    /* leave the rest of the struct filled with zero */

    addr = (struct sockaddr_in *)ai->ai_addr; /* storage area for this info */

    memcpy((char *)&(addr->sin_addr), curr, sizeof(struct in_addr));
    addr->sin_family = he->h_addrtype;
    addr->sin_port = htons((unsigned short)port);

    prevai = ai;
  }
  return firstai;
}