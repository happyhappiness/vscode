

#endif



  if( -1 == getsockopt(sockfd, SOL_SOCKET, SO_ERROR,

                       (void *)&err, &errSize))

    err = Curl_sockerrno();



#ifdef _WIN32_WCE

  /* Always returns this error, bug in CE? */

  if(WSAENOPROTOOPT==err)

    err=0;

#endif



  if ((0 == err) || (EISCONN == err))

    /* we are connected, awesome! */

    rc = TRUE;

  else

    /* This wasn't a successful connect */

    rc = FALSE;

  if (error)

    *error = err;

#else

  (void)sockfd;

  if (error)

    *error = Curl_sockerrno();

#endif

  return rc;

}



CURLcode Curl_store_ip_addr(struct connectdata *conn)

{

  char addrbuf[256];

  Curl_printable_address(conn->ip_addr, addrbuf, sizeof(addrbuf));



  /* save the string */

  Curl_safefree(conn->ip_addr_str);

  conn->ip_addr_str = strdup(addrbuf);

  if(!conn->ip_addr_str)

    return CURLE_OUT_OF_MEMORY; /* FAIL */



#ifdef PF_INET6

  if(conn->ip_addr->ai_family == PF_INET6)

    conn->bits.ipv6 = TRUE;

#endif



  return CURLE_OK;

}



/* Used within the multi interface. Try next IP address, return TRUE if no

   more address exists */

static bool trynextip(struct connectdata *conn,

                      int sockindex,

                      bool *connected)

{

  curl_socket_t sockfd;

  Curl_addrinfo *ai;



  /* first close the failed socket */

  sclose(conn->sock[sockindex]);

  conn->sock[sockindex] = CURL_SOCKET_BAD;

  *connected = FALSE;



  if(sockindex != FIRSTSOCKET)

    return TRUE; /* no next */



  /* try the next address */

  ai = conn->ip_addr->ai_next;



  while (ai) {

    sockfd = singleipconnect(conn, ai, 0L, connected);

    if(sockfd != CURL_SOCKET_BAD) {

      /* store the new socket descriptor */

      conn->sock[sockindex] = sockfd;

      conn->ip_addr = ai;



      Curl_store_ip_addr(conn);

      return FALSE;

    }

    ai = ai->ai_next;

  }

  return TRUE;

}



/*

 * Curl_is_connected() is used from the multi interface to check if the

 * firstsocket has connected.

 */



CURLcode Curl_is_connected(struct connectdata *conn,

                           int sockindex,

                           bool *connected)

{

  int rc;

  struct SessionHandle *data = conn->data;

  CURLcode code = CURLE_OK;

  curl_socket_t sockfd = conn->sock[sockindex];

  long allow = DEFAULT_CONNECT_TIMEOUT;

  long allow_total = 0;

  long has_passed;



  curlassert(sockindex >= FIRSTSOCKET && sockindex <= SECONDARYSOCKET);



  *connected = FALSE; /* a very negative world view is best */



  /* Evaluate in milliseconds how much time that has passed */

  has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle);



  /* subtract the most strict timeout of the ones */

  if(data->set.timeout && data->set.connecttimeout) {

    if (data->set.timeout < data->set.connecttimeout)

      allow_total = allow = data->set.timeout*1000;

    else

      allow = data->set.connecttimeout*1000;

  }

  else if(data->set.timeout) {

    allow_total = allow = data->set.timeout*1000;

  }

  else if(data->set.connecttimeout) {

    allow = data->set.connecttimeout*1000;

  }



  if(has_passed > allow ) {

    /* time-out, bail out, go home */

    failf(data, "Connection time-out after %ld ms", has_passed);

    return CURLE_OPERATION_TIMEOUTED;

  }

  if(conn->bits.tcpconnect) {

    /* we are connected already! */

    Curl_expire(data, allow_total);

    *connected = TRUE;

    return CURLE_OK;

  }



  Curl_expire(data, allow);



  /* check for connect without timeout as we want to return immediately */

  rc = waitconnect(sockfd, 0);



  if(WAITCONN_CONNECTED == rc) {

    int error;

    if (verifyconnect(sockfd, &error)) {

      /* we are connected, awesome! */

      *connected = TRUE;

      return CURLE_OK;

    }

    /* nope, not connected for real */

    data->state.os_errno = error;

    infof(data, "Connection failed\n");

    if(trynextip(conn, sockindex, connected)) {

      code = CURLE_COULDNT_CONNECT;

    }

  }

  else if(WAITCONN_TIMEOUT != rc) {

    int error = 0;



    /* nope, not connected  */

    if (WAITCONN_FDSET_ERROR == rc) {

      (void)verifyconnect(sockfd, &error);

      data->state.os_errno = error;

      infof(data, "%s\n",Curl_strerror(conn,error));

    }

    else

      infof(data, "Connection failed\n");



    if(trynextip(conn, sockindex, connected)) {

      error = Curl_sockerrno();

      data->state.os_errno = error;

      failf(data, "Failed connect to %s:%d; %s",

            conn->host.name, conn->port, Curl_strerror(conn,error));

      code = CURLE_COULDNT_CONNECT;

    }

  }

  /*

   * If the connection failed here, we should attempt to connect to the "next

   * address" for the given host.

   */



  return code;

}

