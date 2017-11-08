static int get_request(curl_socket_t sock, struct httprequest *req)
{
  int fail = 0;
  char *reqbuf = req->reqbuf;
  ssize_t got = 0;

  char *pipereq;
  int pipereq_length = 0;

  if(req->pipelining) {
    pipereq = reqbuf + req->checkindex;
    pipereq_length = req->offset - req->checkindex;
  }

  /*** Init the httpreqest structure properly for the upcoming request ***/

  req->checkindex = 0;
  req->offset = 0;
  req->testno = DOCNUMBER_NOTHING;
  req->partno = 0;
  req->open = TRUE;
  req->auth_req = FALSE;
  req->auth = FALSE;
  req->cl = 0;
  req->digest = FALSE;
  req->ntlm = FALSE;
  req->pipe = 0;
  req->rcmd = RCMD_NORMALREQ;
  req->prot_version = 0;
  req->pipelining = FALSE;

  /*** end of httprequest init ***/

  while (req->offset < REQBUFSIZ-1) {
    if(pipereq_length) {
      memmove(reqbuf, pipereq, pipereq_length); 
      got = pipereq_length;
      pipereq_length = 0;
    }
    else
      got = sread(sock, reqbuf + req->offset, REQBUFSIZ-1 - req->offset);
    if (got <= 0) {
      if (got < 0) {
        logmsg("recv() returned error: %d", SOCKERRNO);
        return DOCNUMBER_INTERNAL;
      }
      logmsg("Connection closed by client");
      reqbuf[req->offset] = '\0';

      /* dump the request receivied so far to the external file */
      storerequest(reqbuf, req->offset);
      return DOCNUMBER_INTERNAL;
    }

    logmsg("Read %d bytes", got);

    req->offset += got;
    reqbuf[req->offset] = '\0';

    if(ProcessRequest(req)) {
      if(req->pipe--) {
        logmsg("Waiting for another piped request");
        continue;
      }
      break;
    }
  }

  if((req->offset == REQBUFSIZ-1) && (got > 0)) {
    logmsg("Request would overflow buffer, closing connection");
    /* dump request received so far to external file anyway */
    reqbuf[REQBUFSIZ-1] = '\0';
    fail = 1;
  }
  else if(req->offset > REQBUFSIZ-1) {
    logmsg("Request buffer overflow, closing connection");
    /* dump request received so far to external file anyway */
    reqbuf[REQBUFSIZ-1] = '\0';
    fail = 1;
  }
  else
    reqbuf[req->offset] = '\0';

  /* dump the request to an external file */
  storerequest(reqbuf, req->pipelining ? req->checkindex : req->offset);

  return fail; /* return 0 on success */
}