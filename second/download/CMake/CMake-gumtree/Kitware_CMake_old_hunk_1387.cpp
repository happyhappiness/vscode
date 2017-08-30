  return TRUE;

}



#ifndef USE_THREADING_GETADDRINFO

/*

 * Curl_getaddrinfo() when built ipv6-enabled (non-threading version).

 *

 * Returns name information about the given hostname and port number. If

 * successful, the 'addrinfo' is returned and the forth argument will point to

 * memory we need to free after use. That memory *MUST* be freed with

 * Curl_freeaddrinfo(), nothing else.

 */

Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,

                                char *hostname,

                                int port,

                                int *waitp)

{

  struct addrinfo hints, *res;

  int error;

  char sbuf[NI_MAXSERV];

  curl_socket_t s;

  int pf;

  struct SessionHandle *data = conn->data;

