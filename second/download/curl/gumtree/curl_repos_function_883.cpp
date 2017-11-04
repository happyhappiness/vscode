static CURLcode bindlocal(struct connectdata *conn,
                          curl_socket_t sockfd, int af, unsigned int scope)
{
  struct SessionHandle *data = conn->data;

  struct Curl_sockaddr_storage sa;
  struct sockaddr *sock = (struct sockaddr *)&sa;  /* bind to this address */
  curl_socklen_t sizeof_sa = 0; /* size of the data sock points to */
  struct sockaddr_in *si4 = (struct sockaddr_in *)&sa;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 *si6 = (struct sockaddr_in6 *)&sa;
#endif

  struct Curl_dns_entry *h=NULL;
  unsigned short port = data->set.localport; /* use this port number, 0 for
                                                "random" */
  /* how many port numbers to try to bind to, increasing one at a time */
  int portnum = data->set.localportrange;
  const char *dev = data->set.str[STRING_DEVICE];
  int error;

  /*************************************************************
   * Select device to bind socket to
   *************************************************************/
  if(!dev && !port)
    /* no local kind of binding was requested */
    return CURLE_OK;

  memset(&sa, 0, sizeof(struct Curl_sockaddr_storage));

  if(dev && (strlen(dev)<255) ) {
    char myhost[256] = "";
    int done = 0; /* -1 for error, 1 for address found */
    bool is_interface = FALSE;
    bool is_host = FALSE;
    static const char *if_prefix = "if!";
    static const char *host_prefix = "host!";

    if(strncmp(if_prefix, dev, strlen(if_prefix)) == 0) {
      dev += strlen(if_prefix);
      is_interface = TRUE;
    }
    else if(strncmp(host_prefix, dev, strlen(host_prefix)) == 0) {
      dev += strlen(host_prefix);
      is_host = TRUE;
    }

    /* interface */
    if(!is_host) {
      switch(Curl_if2ip(af, scope, conn->scope_id, dev,
                        myhost, sizeof(myhost))) {
        case IF2IP_NOT_FOUND:
          if(is_interface) {
            /* Do not fall back to treating it as a host name */
            failf(data, "Couldn't bind to interface '%s'", dev);
            return CURLE_INTERFACE_FAILED;
          }
          break;
        case IF2IP_AF_NOT_SUPPORTED:
          /* Signal the caller to try another address family if available */
          return CURLE_UNSUPPORTED_PROTOCOL;
        case IF2IP_FOUND:
          is_interface = TRUE;
          /*
           * We now have the numerical IP address in the 'myhost' buffer
           */
          infof(data, "Local Interface %s is ip %s using address family %i\n",
                dev, myhost, af);
          done = 1;

#ifdef SO_BINDTODEVICE
          /* I am not sure any other OSs than Linux that provide this feature,
           * and at the least I cannot test. --Ben
           *
           * This feature allows one to tightly bind the local socket to a
           * particular interface.  This will force even requests to other
           * local interfaces to go out the external interface.
           *
           *
           * Only bind to the interface when specified as interface, not just
           * as a hostname or ip address.
           */
          if(setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
                        dev, (curl_socklen_t)strlen(dev)+1) != 0) {
            error = SOCKERRNO;
            infof(data, "SO_BINDTODEVICE %s failed with errno %d: %s;"
                  " will do regular bind\n",
                  dev, error, Curl_strerror(conn, error));
            /* This is typically "errno 1, error: Operation not permitted" if
               you're not running as root or another suitable privileged
               user */
          }
#endif
          break;
      }
    }
    if(!is_interface) {
      /*
       * This was not an interface, resolve the name as a host name
       * or IP number
       *
       * Temporarily force name resolution to use only the address type
       * of the connection. The resolve functions should really be changed
       * to take a type parameter instead.
       */
      long ipver = conn->ip_version;
      int rc;

      if(af == AF_INET)
        conn->ip_version = CURL_IPRESOLVE_V4;
#ifdef 