static void http_connect(curl_socket_t *infdp,
                         curl_socket_t rootfd,
                         const char *ipaddr,
                         unsigned short ipport)
{
  curl_socket_t serverfd[2] = {CURL_SOCKET_BAD, CURL_SOCKET_BAD};
  curl_socket_t clientfd[2] = {CURL_SOCKET_BAD, CURL_SOCKET_BAD};
  ssize_t toc[2] = {0, 0}; /* number of bytes to client */
  ssize_t tos[2] = {0, 0}; /* number of bytes to server */
  char readclient[2][256];
  char readserver[2][256];
  bool poll_client_rd[2] = { TRUE, TRUE };
  bool poll_server_rd[2] = { TRUE, TRUE };
  bool poll_client_wr[2] = { TRUE, TRUE };
  bool poll_server_wr[2] = { TRUE, TRUE };
  bool primary = FALSE;
  bool secondary = FALSE;
  int max_tunnel_idx; /* CTRL or DATA */
  int loop;
  int i;
  int timeout_count = 0;

  /* primary tunnel client endpoint already connected */
  clientfd[CTRL] = *infdp;

  /* Sleep here to make sure the client reads CONNECT response's
     'end of headers' separate from the server data that follows.
     This is done to prevent triggering libcurl known bug #39. */
  for(loop = 2; (loop > 0) && !got_exit_signal; loop--)
    wait_ms(250);
  if(got_exit_signal)
    goto http_connect_cleanup;

  serverfd[CTRL] = connect_to(ipaddr, ipport);
  if(serverfd[CTRL] == CURL_SOCKET_BAD)
    goto http_connect_cleanup;

  /* Primary tunnel socket endpoints are now connected. Tunnel data back and
     forth over the primary tunnel until client or server breaks the primary
     tunnel, simultaneously allowing establishment, operation and teardown of
     a secondary tunnel that may be used for passive FTP data connection. */

  max_tunnel_idx = CTRL;
  primary = TRUE;

  while(!got_exit_signal) {

    fd_set input;
    fd_set output;
    struct timeval timeout = {1, 0}; /* 1000 ms */
    ssize_t rc;
    curl_socket_t maxfd = (curl_socket_t)-1;

    FD_ZERO(&input);
    FD_ZERO(&output);

    if((clientfd[DATA] == CURL_SOCKET_BAD) &&
       (serverfd[DATA] == CURL_SOCKET_BAD) &&
       poll_client_rd[CTRL] && poll_client_wr[CTRL] &&
       poll_server_rd[CTRL] && poll_server_wr[CTRL]) {
      /* listener socket is monitored to allow client to establish
         secondary tunnel only when this tunnel is not established
         and primary one is fully operational */
      FD_SET(rootfd, &input);
      maxfd = rootfd;
    }

    /* set tunnel sockets to wait for */
    for(i = 0; i <= max_tunnel_idx; i++) {
      /* client side socket monitoring */
      if(clientfd[i] != CURL_SOCKET_BAD) {
        if(poll_client_rd[i]) {
          /* unless told not to do so, monitor readability */
          FD_SET(clientfd[i], &input);
          if(clientfd[i] > maxfd)
            maxfd = clientfd[i];
        }
        if(poll_client_wr[i] && toc[i]) {
          /* unless told not to do so, monitor writability
             if there is data ready to be sent to client */
          FD_SET(clientfd[i], &output);
          if(clientfd[i] > maxfd)
            maxfd = clientfd[i];
        }
      }
      /* server side socket monitoring */
      if(serverfd[i] != CURL_SOCKET_BAD) {
        if(poll_server_rd[i]) {
          /* unless told not to do so, monitor readability */
          FD_SET(serverfd[i], &input);
          if(serverfd[i] > maxfd)
            maxfd = serverfd[i];
        }
        if(poll_server_wr[i] && tos[i]) {
          /* unless told not to do so, monitor writability
             if there is data ready to be sent to server */
          FD_SET(serverfd[i], &output);
          if(serverfd[i] > maxfd)
            maxfd = serverfd[i];
        }
      }
    }
    if(got_exit_signal)
      break;

    rc = select((int)maxfd + 1, &input, &output, NULL, &timeout);

    if(rc > 0) {
      /* socket action */
      bool tcp_fin_wr;
      timeout_count = 0;

      if(got_exit_signal)
        break;

      tcp_fin_wr = FALSE;

      /* ---------------------------------------------------------- */

      /* passive mode FTP may establish a secondary tunnel */
      if((clientfd[DATA] == CURL_SOCKET_BAD) &&
         (serverfd[DATA] == CURL_SOCKET_BAD) && FD_ISSET(rootfd, &input)) {
        /* a new connection on listener socket (most likely from client) */
        curl_socket_t datafd = accept(rootfd, NULL, NULL);
        if(datafd != CURL_SOCKET_BAD) {
          struct httprequest req2;
          int err = 0;
          memset(&req2, 0, sizeof(req2));
          logmsg("====> Client connect DATA");
#ifdef TCP_NODELAY
          if(socket_domain_is_ip()) {
            /* Disable the Nagle algorithm */
            curl_socklen_t flag = 1;
            if(0 != setsockopt(datafd, IPPROTO_TCP, TCP_NODELAY,
                               (void *)&flag, sizeof(flag)))
              logmsg("====> TCP_NODELAY for client DATA conection failed");
          }
#endif
          req2.pipelining = FALSE;
          init_httprequest(&req2);
          while(!req2.done_processing) {
            err = get_request(datafd, &req2);
            if(err < 0) {
              /* this socket must be closed, done or not */
              break;
            }
          }

          /* skip this and close the socket if err < 0 */
          if(err >= 0) {
            err = send_doc(datafd, &req2);
            if(!err && req2.connect_request) {
              /* sleep to prevent triggering libcurl known bug #39. */
              for(loop = 2; (loop > 0) && !got_exit_signal; loop--)
                wait_ms(250);
              if(!got_exit_signal) {
                /* connect to the server */
                serverfd[DATA] = connect_to(ipaddr, req2.connect_port);
                if(serverfd[DATA] != CURL_SOCKET_BAD) {
                  /* secondary tunnel established, now we have two
                     connections */
                  poll_client_rd[DATA] = TRUE;
                  poll_client_wr[DATA] = TRUE;
                  poll_server_rd[DATA] = TRUE;
                  poll_server_wr[DATA] = TRUE;
                  max_tunnel_idx = DATA;
                  secondary = TRUE;
                  toc[DATA] = 0;
                  tos[DATA] = 0;
                  clientfd[DATA] = datafd;
                  datafd = CURL_SOCKET_BAD;
                }
              }
            }
          }
          if(datafd != CURL_SOCKET_BAD) {
            /* secondary tunnel not established */
            shutdown(datafd, SHUT_RDWR);
            sclose(datafd);
          }
        }
        if(got_exit_signal)
          break;
      }

      /* ---------------------------------------------------------- */

      /* react to tunnel endpoint readable/writable notifications */
      for(i = 0; i <= max_tunnel_idx; i++) {
        size_t len;
        if(clientfd[i] != CURL_SOCKET_BAD) {
          len = sizeof(readclient[i]) - tos[i];
          if(len && FD_ISSET(clientfd[i], &input)) {
            /* read from client */
            rc = sread(clientfd[i], &readclient[i][tos[i]], len);
            if(rc <= 0) {
              logmsg("[%s] got %zd, STOP READING client", data_or_ctrl(i), rc);
              shutdown(clientfd[i], SHUT_RD);
              poll_client_rd[i] = FALSE;
            }
            else {
              logmsg("[%s] READ %zd bytes from client", data_or_ctrl(i), rc);
              logmsg("[%s] READ \"%s\"", data_or_ctrl(i),
                     data_to_hex(&readclient[i][tos[i]], rc));
              tos[i] += rc;
            }
          }
        }
        if(serverfd[i] != CURL_SOCKET_BAD) {
          len = sizeof(readserver[i])-toc[i];
          if(len && FD_ISSET(serverfd[i], &input)) {
            /* read from server */
            rc = sread(serverfd[i], &readserver[i][toc[i]], len);
            if(rc <= 0) {
              logmsg("[%s] got %zd, STOP READING server", data_or_ctrl(i), rc);
              shutdown(serverfd[i], SHUT_RD);
              poll_server_rd[i] = FALSE;
            }
            else {
              logmsg("[%s] READ %zd bytes from server", data_or_ctrl(i), rc);
              logmsg("[%s] READ \"%s\"", data_or_ctrl(i),
                     data_to_hex(&readserver[i][toc[i]], rc));
              toc[i] += rc;
            }
          }
        }
        if(clientfd[i] != CURL_SOCKET_BAD) {
          if(toc[i] && FD_ISSET(clientfd[i], &output)) {
            /* write to client */
            rc = swrite(clientfd[i], readserver[i], toc[i]);
            if(rc <= 0) {
              logmsg("[%s] got %zd, STOP WRITING client", data_or_ctrl(i), rc);
              shutdown(clientfd[i], SHUT_WR);
              poll_client_wr[i] = FALSE;
              tcp_fin_wr = TRUE;
            }
            else {
              logmsg("[%s] SENT %zd bytes to client", data_or_ctrl(i), rc);
              logmsg("[%s] SENT \"%s\"", data_or_ctrl(i),
                     data_to_hex(readserver[i], rc));
              if(toc[i] - rc)
                memmove(&readserver[i][0], &readserver[i][rc], toc[i]-rc);
              toc[i] -= rc;
            }
          }
        }
        if(serverfd[i] != CURL_SOCKET_BAD) {
          if(tos[i] && FD_ISSET(serverfd[i], &output)) {
            /* write to server */
            rc = swrite(serverfd[i], readclient[i], tos[i]);
            if(rc <= 0) {
              logmsg("[%s] got %zd, STOP WRITING server", data_or_ctrl(i), rc);
              shutdown(serverfd[i], SHUT_WR);
              poll_server_wr[i] = FALSE;
              tcp_fin_wr = TRUE;
            }
            else {
              logmsg("[%s] SENT %zd bytes to server", data_or_ctrl(i), rc);
              logmsg("[%s] SENT \"%s\"", data_or_ctrl(i),
                     data_to_hex(readclient[i], rc));
              if(tos[i] - rc)
                memmove(&readclient[i][0], &readclient[i][rc], tos[i]-rc);
              tos[i] -= rc;
            }
          }
        }
      }
      if(got_exit_signal)
        break;

      /* ---------------------------------------------------------- */

      /* endpoint read/write disabling, endpoint closing and tunnel teardown */
      for(i = 0; i <= max_tunnel_idx; i++) {
        for(loop = 2; loop > 0; loop--) {
          /* loop twice to satisfy condition interdependencies without
             having to await select timeout or another socket event */
          if(clientfd[i] != CURL_SOCKET_BAD) {
            if(poll_client_rd[i] && !poll_server_wr[i]) {
              logmsg("[%s] DISABLED READING client", data_or_ctrl(i));
              shutdown(clientfd[i], SHUT_RD);
              poll_client_rd[i] = FALSE;
            }
            if(poll_client_wr[i] && !poll_server_rd[i] && !toc[i]) {
              logmsg("[%s] DISABLED WRITING client", data_or_ctrl(i));
              shutdown(clientfd[i], SHUT_WR);
              poll_client_wr[i] = FALSE;
              tcp_fin_wr = TRUE;
            }
          }
          if(serverfd[i] != CURL_SOCKET_BAD) {
            if(poll_server_rd[i] && !poll_client_wr[i]) {
              logmsg("[%s] DISABLED READING server", data_or_ctrl(i));
              shutdown(serverfd[i], SHUT_RD);
              poll_server_rd[i] = FALSE;
            }
            if(poll_server_wr[i] && !poll_client_rd[i] && !tos[i]) {
              logmsg("[%s] DISABLED WRITING server", data_or_ctrl(i));
              shutdown(serverfd[i], SHUT_WR);
              poll_server_wr[i] = FALSE;
              tcp_fin_wr = TRUE;
            }
          }
        }
      }

      if(tcp_fin_wr)
        /* allow kernel to place FIN bit packet on the wire */
        wait_ms(250);

      /* socket clearing */
      for(i = 0; i <= max_tunnel_idx; i++) {
        for(loop = 2; loop > 0; loop--) {
          if(clientfd[i] != CURL_SOCKET_BAD) {
            if(!poll_client_wr[i] && !poll_client_rd[i]) {
              logmsg("[%s] CLOSING client socket", data_or_ctrl(i));
              sclose(clientfd[i]);
              clientfd[i] = CURL_SOCKET_BAD;
              if(serverfd[i] == CURL_SOCKET_BAD) {
                logmsg("[%s] ENDING", data_or_ctrl(i));
                if(i == DATA)
                  secondary = FALSE;
                else
                  primary = FALSE;
              }
            }
          }
          if(serverfd[i] != CURL_SOCKET_BAD) {
            if(!poll_server_wr[i] && !poll_server_rd[i]) {
              logmsg("[%s] CLOSING server socket", data_or_ctrl(i));
              sclose(serverfd[i]);
              serverfd[i] = CURL_SOCKET_BAD;
              if(clientfd[i] == CURL_SOCKET_BAD) {
                logmsg("[%s] ENDING", data_or_ctrl(i));
                if(i == DATA)
                  secondary = FALSE;
                else
                  primary = FALSE;
              }
            }
          }
        }
      }

      /* ---------------------------------------------------------- */

      max_tunnel_idx = secondary ? DATA : CTRL;

      if(!primary)
        /* exit loop upon primary tunnel teardown */
        break;

    } /* (rc > 0) */
    else {
      timeout_count++;
      if(timeout_count > 5) {
        logmsg("CONNECT proxy timeout after %d idle seconds!", timeout_count);
        break;
      }
    }
  }

http_connect_cleanup:

  for(i = DATA; i >= CTRL; i--) {
    if(serverfd[i] != CURL_SOCKET_BAD) {
      logmsg("[%s] CLOSING server socket (cleanup)", data_or_ctrl(i));
      shutdown(serverfd[i], SHUT_RDWR);
      sclose(serverfd[i]);
    }
    if(clientfd[i] != CURL_SOCKET_BAD) {
      logmsg("[%s] CLOSING client socket (cleanup)", data_or_ctrl(i));
      shutdown(clientfd[i], SHUT_RDWR);
      sclose(clientfd[i]);
    }
    if((serverfd[i] != CURL_SOCKET_BAD) ||
       (clientfd[i] != CURL_SOCKET_BAD)) {
      logmsg("[%s] ABORTING", data_or_ctrl(i));
    }
  }

  *infdp = CURL_SOCKET_BAD;
}