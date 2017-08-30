  return TRUE;

}



#if !defined(USE_THREADING_GETADDRINFO) && !defined(CURLRES_ARES)



#ifdef DEBUG_ADDRINFO

static void dump_addrinfo(struct connectdata *conn, const struct addrinfo *ai)

{

  printf("dump_addrinfo:\n");

  for ( ; ai; ai = ai->ai_next) {

    char  buf[INET6_ADDRSTRLEN];



    printf("    fam %2d, CNAME %s, ",

           ai->ai_family, ai->ai_canonname ? ai->ai_canonname : "<none>");

    if (Curl_printable_address(ai, buf, sizeof(buf)))

      printf("%s\n", buf);

    else

      printf("failed; %s\n", Curl_strerror(conn, Curl_sockerrno()));

  }

}

#else

#define dump_addrinfo(x,y)

#endif



/*

 * Curl_getaddrinfo() when built ipv6-enabled (non-threading and

 * non-ares version).

 *

 * Returns name information about the given hostname and port number. If

 * successful, the 'addrinfo' is returned and the forth argument will point to

 * memory we need to free after use. That memory *MUST* be freed with

 * Curl_freeaddrinfo(), nothing else.

 */

Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,

                                const char *hostname,

                                int port,

                                int *waitp)

{

  struct addrinfo hints, *res;

  int error;

  char sbuf[NI_MAXSERV];

  char *sbufptr = NULL;

  char addrbuf[128];

  curl_socket_t s;

  int pf;

  struct SessionHandle *data = conn->data;

