static CURLcode bindlocal(struct connectdata *conn,
                          curl_socket_t sockfd)
{
#ifdef HAVE_INET_NTOA
  bool bindworked = FALSE;
  struct SessionHandle *data = conn->data;

  /*************************************************************
   * Select device to bind socket to
   *************************************************************/
  if (strlen(data->set.device)<255) {
    struct Curl_dns_entry *h=NULL;
    size_t size;
    char myhost[256] = "";
    in_addr_t in;
    int rc;
    bool was_iface = FALSE;

    /* First check if the given name is an IP address */
    in=inet_addr(data->set.device);

    if((in == CURL_INADDR_NONE) &&
       Curl_if2ip(data->set.device, myhost, sizeof(myhost))) {
      /*
       * We now have the numerical IPv4-style x.y.z.w in the 'myhost' buffer
       */
      rc = Curl_resolv(conn, myhost, 0, &h);
      if(rc == CURLRESOLV_PENDING)
        (void)Curl_wait_for_resolv(conn, &h);

      if(h)
        was_iface = TRUE;
    }

    if(!was_iface) {
      /*
       * This was not an interface, resolve the name as a host name
       * or IP number
       */
      rc = Curl_resolv(conn, data->set.device, 0, &h);
      if(rc == CURLRESOLV_PENDING)
        (void)Curl_wait_for_resolv(conn, &h);

      if(h)
        /* we know data->set.device is shorter than the myhost array */
        strcpy(myhost, data->set.device);
    }

    if(! *myhost) {
      /* need to fix this
         h=Curl_gethost(data,
         getmyhost(*myhost,sizeof(myhost)),
         hostent_buf,
         sizeof(hostent_buf));
      */
      failf(data, "Couldn't bind to '%s'", data->set.device);
      return CURLE_HTTP_PORT_FAILED;
    }

    infof(data, "We bind local end to %s\n", myhost);

#ifdef SO_BINDTODEVICE
    /* I am not sure any other OSs than Linux that provide this feature, and
     * at the least I cannot test. --Ben
     *
     * This feature allows one to tightly bind the local socket to a
     * particular interface.  This will force even requests to other local
     * interfaces to go out the external interface.
     *
     */
    if (was_iface) {
      /* Only bind to the interface when specified as interface, not just as a
       * hostname or ip address.
       */
      if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
                     data->set.device, strlen(data->set.device)+1) != 0) {
        /* printf("Failed to BINDTODEVICE, socket: %d  device: %s error: %s\n",
           sockfd, data->set.device, Curl_strerror(Curl_ourerrno())); */
        infof(data, "SO_BINDTODEVICE %s failed\n",
              data->set.device);
        /* This is typically "errno 1, error: Operation not permitted" if
           you're not running as root or another suitable privileged user */
      }
    }
#endif

    in=inet_addr(myhost);
    if (CURL_INADDR_NONE != in) {

      if ( h ) {
        Curl_addrinfo *addr = h->addr;

        Curl_resolv_unlock(data, h);
        /* we don't need it anymore after this function has returned */

        if( bind(sockfd, addr->ai_addr, (socklen_t)addr->ai_addrlen) >= 0) {
          /* we succeeded to bind */
#ifdef ENABLE_IPV6
          struct sockaddr_in6 add;
#else
          struct sockaddr_in add;
#endif

          bindworked = TRUE;

          size = sizeof(add);
          if(getsockname(sockfd, (struct sockaddr *) &add,
                         (socklen_t *)&size)<0) {
            failf(data, "getsockname() failed");
            return CURLE_HTTP_PORT_FAILED;
          }
        }

        if(!bindworked) {
          data->state.os_errno = Curl_ourerrno();
          failf(data, "bind failure: %s",
                Curl_strerror(conn, data->state.os_errno));
          return CURLE_HTTP_PORT_FAILED;
        }

      } /* end of if  h */
      else {
        failf(data,"could't find my own IP address (%s)", myhost);
        return CURLE_HTTP_PORT_FAILED;
      }
    } /* end of inet_addr */

    else {
      failf(data, "could't find my own IP address (%s)", myhost);
      return CURLE_HTTP_PORT_FAILED;
    }

    return CURLE_OK;

  } /* end of device selection support */
#else
  (void)conn;
  (void)sockfd;
#endif /* end of HAVE_INET_NTOA */

  return CURLE_HTTP_PORT_FAILED;
}