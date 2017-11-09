CURLcode Curl_is_connected(struct connectdata *conn,
                           int sockindex,
                           bool *connected)
{
  struct Curl_easy *data = conn->data;
  CURLcode result = CURLE_OK;
  time_t allow;
  int error = 0;
  struct curltime now;
  int rc;
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

  for(i = 0; i<2; i++) {
    const int other = i ^ 1;
    if(conn->tempsock[i] == CURL_SOCKET_BAD)
      continue;

#ifdef mpeix
    /* Call this function once now, and ignore the results. We do this to
       "clear" the error state on the socket so that we can later read it
       reliably. This is reported necessary on the MPE/iX operating system. */
    (void)verifyconnect(conn->tempsock[i], NULL);
#endif

    /* check socket for connect */
    rc = SOCKET_WRITABLE(conn->tempsock[i], 0);

    if(rc == 0) { /* no connection yet */
      error = 0;
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
    else if(rc == CURL_CSELECT_OUT || conn->bits.tcp_fastopen) {
      if(verifyconnect(conn->tempsock[i], &error)) {
        /* we are connected with TCP, awesome! */

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
        result = Curl_connected_proxy(conn, sockindex);
        if(result)
          return result;

        conn->bits.tcpconnect[sockindex] = TRUE;

        *connected = TRUE;
        if(sockindex == FIRSTSOCKET)
          Curl_pgrsTime(data, TIMER_CONNECT); /* connect done */
        Curl_updateconninfo(conn, conn->sock[sockindex]);
        Curl_verboseconnect(conn);

        return CURLE_OK;
      }
      infof(data, "Connection failed\n");
    }
    else if(rc & CURL_CSELECT_ERR)
      (void)verifyconnect(conn->tempsock[i], &error);

    /*
     * The connection failed here, we should attempt to connect to the "next
     * address" for the given host. But first remember the latest error.
     */
    if(error) {
      data->state.os_errno = error;
      SET_SOCKERRNO(error);
      if(conn->tempaddr[i]) {
        CURLcode status;
        char ipaddress[MAX_IPADR_LEN];
        Curl_printable_address(conn->tempaddr[i], ipaddress, MAX_IPADR_LEN);
        infof(data, "connect to %s port %ld failed: %s\n",
              ipaddress, conn->port, Curl_strerror(conn, error));

        conn->timeoutms_per_addr = conn->tempaddr[i]->ai_next == NULL ?
                                   allow : allow / 2;

        status = trynextip(conn, sockindex, i);
        if(status != CURLE_COULDNT_CONNECT
            || conn->tempsock[other] == CURL_SOCKET_BAD)
          /* the last attempt failed and no other sockets remain open */
          result = status;
      }
    }
  }

  if(result) {
    /* no more addresses to try */

    const char *hostname;

    /* if the first address family runs out of addresses to try before
       the happy eyeball timeout, go ahead and try the next family now */
    if(conn->tempaddr[1] == NULL) {
      result = trynextip(conn, sockindex, 1);
      if(!result)
        return result;
    }

    if(conn->bits.socksproxy)
      hostname = conn->socks_proxy.host.name;
    else if(conn->bits.httpproxy)
      hostname = conn->http_proxy.host.name;
    else if(conn->bits.conn_to_host)
      hostname = conn->conn_to_host.name;
    else
      hostname = conn->host.name;

    failf(data, "Failed to connect to %s port %ld: %s",
        hostname, conn->port, Curl_strerror(conn, error));
  }

  return result;
}