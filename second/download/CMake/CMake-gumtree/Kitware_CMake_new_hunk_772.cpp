

#endif



  if(0 != getsockopt(sockfd, SOL_SOCKET, SO_ERROR, (void *)&err, &errSize))

    err = SOCKERRNO;

#ifdef _WIN32_WCE

  /* Old WinCE versions don't support SO_ERROR */

  if(WSAENOPROTOOPT == err) {

    SET_SOCKERRNO(0);

    err = 0;

  }

#endif

#ifdef __minix

  /* Minix 3.1.x doesn't support getsockopt on UDP sockets */

  if(EBADIOCTL == err) {

    SET_SOCKERRNO(0);

    err = 0;

  }

#endif

  if((0 == err) || (EISCONN == err))

    /* we are connected, awesome! */

    rc = TRUE;

  else

    /* This wasn't a successful connect */

    rc = FALSE;

  if(error)

    *error = err;

#else

  (void)sockfd;

  if(error)

    *error = SOCKERRNO;

#endif

  return rc;

}



/* Used within the multi interface. Try next IP address, return TRUE if no

   more address exists or error */

static CURLcode trynextip(struct connectdata *conn,

                          int sockindex,

                          int tempindex)

{

  CURLcode rc = CURLE_COULDNT_CONNECT;



  /* First clean up after the failed socket.

     Don't close it yet to ensure that the next IP's socket gets a different

     file descriptor, which can prevent bugs when the curl_multi_socket_action

     interface is used with certain select() replacements such as kqueue. */

  curl_socket_t fd_to_close = conn->tempsock[tempindex];

  conn->tempsock[tempindex] = CURL_SOCKET_BAD;



  if(sockindex == FIRSTSOCKET) {

    Curl_addrinfo *ai = NULL;

    int family = AF_UNSPEC;



    if(conn->tempaddr[tempindex]) {

      /* find next address in the same protocol family */

      family = conn->tempaddr[tempindex]->ai_family;

      ai = conn->tempaddr[tempindex]->ai_next;

    }

    else if(conn->tempaddr[0]) {

      /* happy eyeballs - try the other protocol family */

      int firstfamily = conn->tempaddr[0]->ai_family;

#ifdef ENABLE_IPV6

      family = (firstfamily == AF_INET) ? AF_INET6 : AF_INET;

#else

      family = firstfamily;

#endif

      ai = conn->tempaddr[0]->ai_next;

    }



    while(ai) {

      while(ai && ai->ai_family != family)

        ai = ai->ai_next;



      if(ai) {

        rc = singleipconnect(conn, ai, &conn->tempsock[tempindex]);

        if(rc == CURLE_COULDNT_CONNECT) {

          ai = ai->ai_next;

          continue;

        }

        conn->tempaddr[tempindex] = ai;

      }

      break;

    }

  }



  if(fd_to_close != CURL_SOCKET_BAD)

    Curl_closesocket(conn, fd_to_close);



  return rc;

}



/* Copies connection info into the session handle to make it available

   when the session handle is no longer associated with a connection. */

void Curl_persistconninfo(struct connectdata *conn)

{

  memcpy(conn->data->info.conn_primary_ip, conn->primary_ip, MAX_IPADR_LEN);

  memcpy(conn->data->info.conn_local_ip, conn->local_ip, MAX_IPADR_LEN);

  conn->data->info.conn_primary_port = conn->primary_port;

  conn->data->info.conn_local_port = conn->local_port;

}



/* retrieves ip address and port from a sockaddr structure */

static bool getaddressinfo(struct sockaddr* sa, char* addr,

                           long* port)

{

  unsigned short us_port;

  struct sockaddr_in* si = NULL;

#ifdef ENABLE_IPV6

  struct sockaddr_in6* si6 = NULL;

#endif

#if defined(HAVE_SYS_UN_H) && defined(AF_UNIX)

  struct sockaddr_un* su = NULL;

#endif



  switch (sa->sa_family) {

    case AF_INET:

      si = (struct sockaddr_in*) sa;

      if(Curl_inet_ntop(sa->sa_family, &si->sin_addr,

                        addr, MAX_IPADR_LEN)) {

        us_port = ntohs(si->sin_port);

        *port = us_port;

        return TRUE;

      }

      break;

#ifdef ENABLE_IPV6

    case AF_INET6:

      si6 = (struct sockaddr_in6*)sa;

      if(Curl_inet_ntop(sa->sa_family, &si6->sin6_addr,

                        addr, MAX_IPADR_LEN)) {

        us_port = ntohs(si6->sin6_port);

        *port = us_port;

        return TRUE;

      }

      break;

#endif

#if defined(HAVE_SYS_UN_H) && defined(AF_UNIX)

    case AF_UNIX:

      su = (struct sockaddr_un*)sa;

      snprintf(addr, MAX_IPADR_LEN, "%s", su->sun_path);

      *port = 0;

      return TRUE;

#endif

    default:

      break;

  }



  addr[0] = '\0';

  *port = 0;



  return FALSE;

}



/* retrieves the start/end point information of a socket of an established

   connection */

void Curl_updateconninfo(struct connectdata *conn, curl_socket_t sockfd)

{

  int error;

  curl_socklen_t len;

  struct Curl_sockaddr_storage ssrem;

  struct Curl_sockaddr_storage ssloc;

  struct SessionHandle *data = conn->data;



  if(conn->socktype == SOCK_DGRAM)

    /* there's no connection! */

    return;



  if(!conn->bits.reuse) {



    len = sizeof(struct Curl_sockaddr_storage);

    if(getpeername(sockfd, (struct sockaddr*) &ssrem, &len)) {

      error = SOCKERRNO;

      failf(data, "getpeername() failed with errno %d: %s",

            error, Curl_strerror(conn, error));

      return;

    }



    len = sizeof(struct Curl_sockaddr_storage);

    if(getsockname(sockfd, (struct sockaddr*) &ssloc, &len)) {

      error = SOCKERRNO;

      failf(data, "getsockname() failed with errno %d: %s",

            error, Curl_strerror(conn, error));

      return;

    }



    if(!getaddressinfo((struct sockaddr*)&ssrem,

                        conn->primary_ip, &conn->primary_port)) {

      error = ERRNO;

      failf(data, "ssrem inet_ntop() failed with errno %d: %s",

            error, Curl_strerror(conn, error));

      return;

    }

    memcpy(conn->ip_addr_str, conn->primary_ip, MAX_IPADR_LEN);



    if(!getaddressinfo((struct sockaddr*)&ssloc,

                       conn->local_ip, &conn->local_port)) {

      error = ERRNO;

      failf(data, "ssloc inet_ntop() failed with errno %d: %s",

            error, Curl_strerror(conn, error));

      return;

    }



  }



  /* persist connection info in session handle */

  Curl_persistconninfo(conn);

}



/*

 * Curl_is_connected() checks if the socket has connected.

 */



CURLcode Curl_is_connected(struct connectdata *conn,

                           int sockindex,

                           bool *connected)

{

  struct SessionHandle *data = conn->data;

  CURLcode code = CURLE_OK;

  long allow;

  int error = 0;

  struct timeval now;

  int result;

  int i;



  DEBUGASSERT(sockindex >= FIRSTSOCKET && sockindex <= SECONDARYSOCKET);



  *connected = FALSE; /* a very negative world view is best */



  if(conn->bits.tcpconnect[sockindex]) {

    /* we are connected already! */

    *connected = TRUE;

    return CURLE_OK;

  }



  now = Curl_tvnow();



  /* figure out how long time we have left to connect */

  allow = Curl_timeleft(data, &now, TRUE);



  if(allow < 0) {

    /* time-out, bail out, go home */

    failf(data, "Connection time-out");

    return CURLE_OPERATION_TIMEDOUT;

  }



  for(i=0; i<2; i++) {

    if(conn->tempsock[i] == CURL_SOCKET_BAD)

      continue;



#ifdef mpeix

    /* Call this function once now, and ignore the results. We do this to

       "clear" the error state on the socket so that we can later read it

       reliably. This is reported necessary on the MPE/iX operating system. */

    (void)verifyconnect(conn->tempsock[i], NULL);

#endif



    /* check socket for connect */

    result = Curl_socket_ready(CURL_SOCKET_BAD, conn->tempsock[i], 0);



    if(result == 0) { /* no connection yet */

      if(curlx_tvdiff(now, conn->connecttime) >= conn->timeoutms_per_addr) {

        infof(data, "After %ldms connect time, move on!\n",

              conn->timeoutms_per_addr);

        error = ETIMEDOUT;

      }



      /* should we try another protocol family? */

      if(i == 0 && conn->tempaddr[1] == NULL &&

         curlx_tvdiff(now, conn->connecttime) >= HAPPY_EYEBALLS_TIMEOUT) {

        trynextip(conn, sockindex, 1);

      }

    }

    else if(result == CURL_CSELECT_OUT) {

      if(verifyconnect(conn->tempsock[i], &error)) {

        /* we are connected with TCP, awesome! */

        int other = i ^ 1;



        /* use this socket from now on */

        conn->sock[sockindex] = conn->tempsock[i];

        conn->ip_addr = conn->tempaddr[i];

        conn->tempsock[i] = CURL_SOCKET_BAD;



        /* close the other socket, if open */

        if(conn->tempsock[other] != CURL_SOCKET_BAD) {

          Curl_closesocket(conn, conn->tempsock[other]);

          conn->tempsock[other] = CURL_SOCKET_BAD;

        }



        /* see if we need to do any proxy magic first once we connected */

        code = Curl_connected_proxy(conn, sockindex);

        if(code)

          return code;



        conn->bits.tcpconnect[sockindex] = TRUE;



        *connected = TRUE;

        if(sockindex == FIRSTSOCKET)

          Curl_pgrsTime(data, TIMER_CONNECT); /* connect done */

        Curl_updateconninfo(conn, conn->sock[sockindex]);

        Curl_verboseconnect(conn);



        return CURLE_OK;

      }

      else

        infof(data, "Connection failed\n");

    }

    else if(result & CURL_CSELECT_ERR)

      (void)verifyconnect(conn->tempsock[i], &error);



    /*

     * The connection failed here, we should attempt to connect to the "next

     * address" for the given host. But first remember the latest error.

     */

    if(error) {

      char ipaddress[MAX_IPADR_LEN];

      data->state.os_errno = error;

      SET_SOCKERRNO(error);

      if(conn->tempaddr[i]) {

        Curl_printable_address(conn->tempaddr[i], ipaddress, MAX_IPADR_LEN);

        infof(data, "connect to %s port %ld failed: %s\n",

              ipaddress, conn->port, Curl_strerror(conn, error));



        conn->timeoutms_per_addr = conn->tempaddr[i]->ai_next == NULL ?

                                   allow : allow / 2;



        code = trynextip(conn, sockindex, i);

      }

    }

  }



  if(code) {

    /* no more addresses to try */



    /* if the first address family runs out of addresses to try before

       the happy eyeball timeout, go ahead and try the next family now */

    if(conn->tempaddr[1] == NULL) {

      int rc;

      rc = trynextip(conn, sockindex, 1);

      if(rc == CURLE_OK)

        return CURLE_OK;

    }



    failf(data, "Failed to connect to %s port %ld: %s",

          conn->bits.proxy?conn->proxy.name:conn->host.name,

          conn->port, Curl_strerror(conn, error));

  }



  return code;

}

