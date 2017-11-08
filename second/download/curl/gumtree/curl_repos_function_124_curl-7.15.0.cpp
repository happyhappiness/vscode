static int get_request(int sock, struct httprequest *req)
{
  int fail= FALSE;
  char *reqbuf = req->reqbuf;

  /*** Init the httpreqest structure properly for the upcoming request ***/
  memset(req, 0, sizeof(struct httprequest));

  /* here's what should not be 0 from the start */
  req->testno = DOCNUMBER_NOTHING; /* safe default */
  req->open = TRUE; /* connection should remain open and wait for more
                       commands */

  /*** end of httprequest init ***/

  while (req->offset < REQBUFSIZ) {
    int got = sread(sock, reqbuf + req->offset, REQBUFSIZ - req->offset);
    if (got <= 0) {
      if (got < 0) {
        perror("recv");
        logmsg("recv() returned error");
        return DOCNUMBER_INTERNAL;
      }
      logmsg("Connection closed by client");
      reqbuf[req->offset]=0;

      /* dump the request receivied so far to the external file */
      storerequest(reqbuf);
      return DOCNUMBER_INTERNAL;
    }
    req->offset += got;

    reqbuf[req->offset] = 0;

    if(ProcessRequest(req))
      break;
  }

  if (req->offset >= REQBUFSIZ) {
    logmsg("Request buffer overflow, closing connection");
    reqbuf[REQBUFSIZ-1]=0;
    fail = TRUE;
    /* dump the request to an external file anyway */
  }
  else
    reqbuf[req->offset]=0;

  /* dump the request to an external file */
  storerequest(reqbuf);

  return fail; /* success */
}