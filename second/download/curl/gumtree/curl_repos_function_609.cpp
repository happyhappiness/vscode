static int service_connection(curl_socket_t msgsock, struct httprequest *req,
                              curl_socket_t listensock,
                              const char *connecthost)
{
  if(got_exit_signal)
    return -1;

  while(!req->done_processing) {
    int rc = get_request(msgsock, req);
    if (rc <= 0) {
      /* Nothing further to read now (possibly because the socket was closed */
      return rc;
    }
  }

  if(prevbounce) {
    /* bounce treatment requested */
    if((req->testno == prevtestno) &&
       (req->partno == prevpartno)) {
      req->partno++;
      logmsg("BOUNCE part number to %ld", req->partno);
    }
    else {
      prevbounce = FALSE;
      prevtestno = -1;
      prevpartno = -1;
    }
  }

  send_doc(msgsock, req);
  if(got_exit_signal)
    return -1;

  if(req->testno < 0) {
    logmsg("special request received, no persistency");
    return -1;
  }
  if(!req->open) {
    logmsg("instructed to close connection after server-reply");
    return -1;
  }

  if(req->connect_request) {
    /* a CONNECT request, setup and talk the tunnel */
    if(!is_proxy) {
      logmsg("received CONNECT but isn't running as proxy!");
      return 1;
    }
    else {
      http_connect(&msgsock, listensock, connecthost, req->connect_port);
      return -1;
    }
  }

  if(req->upgrade_request) {
    /* an upgrade request, switch to http2 here */
    http2(req);
    return -1;
  }

  /* if we got a CONNECT, loop and get another request as well! */

  if(req->open) {
    logmsg("=> persistant connection request ended, awaits new request\n");
    return 1;
  }

  return -1;
}