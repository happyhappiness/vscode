static int get_request(int sock, int *part)
{
  static char reqbuf[REQBUFSIZ], doc[MAXDOCNAMELEN];
  static char request[REQUEST_KEYWORD_SIZE];
  unsigned int offset = 0;
  int prot_major, prot_minor;
  char logbuf[256];

  *part = 0; /* part zero equals none */

  while (offset < REQBUFSIZ) {
    int got = recv(sock, reqbuf + offset, REQBUFSIZ - offset, 0);
    if (got <= 0) {
      if (got < 0) {
        perror("recv");
        logmsg("recv() returned error");
        return DOCNUMBER_INTERNAL;
      }
      logmsg("Connection closed by client");
      return DOCNUMBER_INTERNAL;
    }
    offset += got;

    reqbuf[offset] = 0;

    if(ProcessRequest(reqbuf))
      break;
  }

  if (offset >= REQBUFSIZ) {
    logmsg("Request buffer overflow, closing connection");
    return DOCNUMBER_INTERNAL;
  }
  reqbuf[offset]=0;
  
  /* dump the request to an external file */
  storerequest(reqbuf);

  if(sscanf(reqbuf, "%" REQBUFSIZ_TXT"s %" MAXDOCNAMELEN_TXT "s HTTP/%d.%d",
            request,
            doc,
            &prot_major,
            &prot_minor) == 4) {
    char *ptr;
    int test_no=0;

    /* find the last slash */
    ptr = strrchr(doc, '/');

    /* get the number after it */
    if(ptr) {

      if((strlen(doc) + strlen(request)) < 200)
        sprintf(logbuf, "Got request: %s %s HTTP/%d.%d",
                request, doc, prot_major, prot_minor);
      else
        sprintf(logbuf, "Got a *HUGE* request HTTP/%d.%d",
                prot_major, prot_minor);
      logmsg(logbuf);
      
      if(!strncmp("/verifiedserver", ptr, 15)) {
        logmsg("Are-we-friendly question received");
        return DOCNUMBER_WERULEZ;
      }

      ptr++; /* skip the slash */

      test_no = strtol(ptr, &ptr, 10);

      if(test_no > 10000) {
        *part = test_no % 10000;
        test_no /= 10000;
      }

      sprintf(logbuf, "Found test number %d in path", test_no);
      logmsg(logbuf);
    }
    else {
      if(sscanf(reqbuf, "CONNECT %" MAXDOCNAMELEN_TXT "s HTTP/%d.%d",
                doc,
                &prot_major, &prot_minor) == 3) {
        sprintf(logbuf, "Receiced a CONNECT %s HTTP/%d.%d request", 
                doc, prot_major, prot_minor);
        logmsg(logbuf);

        if(!strncmp(doc, "bad", 3))
          /* if the host name starts with bad, we fake an error here */
          test_no = DOCNUMBER_BADCONNECT;
        else
          test_no = DOCNUMBER_CONNECT;
      }
      else {
        logmsg("Did not find test number in PATH");
        test_no = DOCNUMBER_404;
      }
    }

    return test_no;
  }
  
  logmsg("Got illegal request");
  fprintf(stderr, "Got illegal request\n");
  return DOCNUMBER_404;
}