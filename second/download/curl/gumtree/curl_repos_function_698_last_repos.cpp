static int ProcessRequest(struct httprequest *req)
{
  char *line = &req->reqbuf[req->checkindex];
  bool chunked = FALSE;
  static char request[REQUEST_KEYWORD_SIZE];
  static char doc[MAXDOCNAMELEN];
  char logbuf[456];
  int prot_major, prot_minor;
  char *end = strstr(line, end_of_headers);

  req->callcount++;

  logmsg("Process %d bytes request%s", req->offset,
         req->callcount > 1?" [CONTINUED]":"");

  /* try to figure out the request characteristics as soon as possible, but
     only once! */

  if(use_gopher &&
     (req->testno == DOCNUMBER_NOTHING) &&
     !strncmp("/verifiedserver", line, 15)) {
    logmsg("Are-we-friendly question received");
    req->testno = DOCNUMBER_WERULEZ;
    return 1; /* done */
  }

  else if((req->testno == DOCNUMBER_NOTHING) &&
     sscanf(line,
            "%" REQUEST_KEYWORD_SIZE_TXT"s %" MAXDOCNAMELEN_TXT "s HTTP/%d.%d",
            request,
            doc,
            &prot_major,
            &prot_minor) == 4) {
    char *ptr;

    req->prot_version = prot_major*10 + prot_minor;

    /* find the last slash */
    ptr = strrchr(doc, '/');

    /* get the number after it */
    if(ptr) {
      if((strlen(doc) + strlen(request)) < 400)
        snprintf(logbuf, sizeof(logbuf), "Got request: %s %s HTTP/%d.%d",
                 request, doc, prot_major, prot_minor);
      else
        snprintf(logbuf, sizeof(logbuf), "Got a *HUGE* request HTTP/%d.%d",
                 prot_major, prot_minor);
      logmsg("%s", logbuf);

      if(!strncmp("/verifiedserver", ptr, 15)) {
        logmsg("Are-we-friendly question received");
        req->testno = DOCNUMBER_WERULEZ;
        return 1; /* done */
      }

      if(!strncmp("/quit", ptr, 5)) {
        logmsg("Request-to-quit received");
        req->testno = DOCNUMBER_QUIT;
        return 1; /* done */
      }

      ptr++; /* skip the slash */

      /* skip all non-numericals following the slash */
      while(*ptr && !ISDIGIT(*ptr))
        ptr++;

      req->testno = strtol(ptr, &ptr, 10);

      if(req->testno > 10000) {
        req->partno = req->testno % 10000;
        req->testno /= 10000;
      }
      else
        req->partno = 0;

      if(req->testno) {

        snprintf(logbuf, sizeof(logbuf), "Requested test number %ld part %ld",
                 req->testno, req->partno);
        logmsg("%s", logbuf);

        /* find and parse <servercmd> for this test */
        parse_servercmd(req);
      }
      else
        req->testno = DOCNUMBER_NOTHING;

    }

    if(req->testno == DOCNUMBER_NOTHING) {
      /* didn't find any in the first scan, try alternative test case
         number placements */

      if(sscanf(req->reqbuf, "CONNECT %" MAXDOCNAMELEN_TXT "s HTTP/%d.%d",
                doc, &prot_major, &prot_minor) == 3) {
        char *portp = NULL;
        unsigned long part = 0;

        snprintf(logbuf, sizeof(logbuf),
                 "Received a CONNECT %s HTTP/%d.%d request",
                 doc, prot_major, prot_minor);
        logmsg("%s", logbuf);

        req->connect_request = TRUE;

        if(req->prot_version == 10)
          req->open = FALSE; /* HTTP 1.0 closes connection by default */

        if(doc[0] == '[') {
          char *p = &doc[1];
          /* scan through the hexgroups and store the value of the last group
             in the 'part' variable and use as test case number!! */
          while(*p && (ISXDIGIT(*p) || (*p == ':') || (*p == '.'))) {
            char *endp;
            part = strtoul(p, &endp, 16);
            if(ISXDIGIT(*p))
              p = endp;
            else
              p++;
          }
          if(*p != ']')
            logmsg("Invalid CONNECT IPv6 address format");
          else if(*(p + 1) != ':')
            logmsg("Invalid CONNECT IPv6 port format");
          else
            portp = p + 1;

          req->testno = part;
        }
        else
          portp = strchr(doc, ':');

        if(portp && (*(portp + 1) != '\0') && ISDIGIT(*(portp + 1))) {
          unsigned long ulnum = strtoul(portp + 1, NULL, 10);
          if(!ulnum || (ulnum > 65535UL))
            logmsg("Invalid CONNECT port received");
          else
            req->connect_port = curlx_ultous(ulnum);

        }
        logmsg("Port number: %d, test case number: %ld",
               req->connect_port, req->testno);
      }
    }

    if(req->testno == DOCNUMBER_NOTHING) {
      /* check for a Testno: header with the test case number */
      char *testno = strstr(line, "\nTestno: ");
      if(testno) {
        req->testno = strtol(&testno[9], NULL, 10);
        logmsg("Found test number %d in Testno: header!", req->testno);
      }
    }
    if(req->testno == DOCNUMBER_NOTHING) {
      /* Still no test case number. Try to get the the number off the last dot
         instead, IE we consider the TLD to be the test number. Test 123 can
         then be written as "example.com.123". */

      /* find the last dot */
      ptr = strrchr(doc, '.');

      /* get the number after it */
      if(ptr) {
        ptr++; /* skip the dot */

        req->testno = strtol(ptr, &ptr, 10);

        if(req->testno > 10000) {
          req->partno = req->testno % 10000;
          req->testno /= 10000;

          logmsg("found test %d in requested host name", req->testno);

        }
        else
          req->partno = 0;

        snprintf(logbuf, sizeof(logbuf),
                 "Requested test number %ld part %ld (from host name)",
                 req->testno, req->partno);
        logmsg("%s", logbuf);

      }

      if(!req->testno) {
        logmsg("Did not find test number in PATH");
        req->testno = DOCNUMBER_404;
      }
      else
        parse_servercmd(req);
    }
  }
  else if((req->offset >= 3) && (req->testno == DOCNUMBER_NOTHING)) {
    logmsg("** Unusual request. Starts with %02x %02x %02x",
           line[0], line[1], line[2]);
  }

  if(!end) {
    /* we don't have a complete request yet! */
    logmsg("request not complete yet");
    return 0; /* not complete yet */
  }
  logmsg("- request found to be complete");

  if(use_gopher) {
    /* when using gopher we cannot check the request until the entire
       thing has been received */
    char *ptr;

    /* find the last slash in the line */
    ptr = strrchr(line, '/');

    if(ptr) {
      ptr++; /* skip the slash */

      /* skip all non-numericals following the slash */
      while(*ptr && !ISDIGIT(*ptr))
        ptr++;

      req->testno = strtol(ptr, &ptr, 10);

      if(req->testno > 10000) {
        req->partno = req->testno % 10000;
        req->testno /= 10000;
      }
      else
        req->partno = 0;

      snprintf(logbuf, sizeof(logbuf),
               "Requested GOPHER test number %ld part %ld",
               req->testno, req->partno);
      logmsg("%s", logbuf);
    }
  }

  if(req->pipe)
    /* we do have a full set, advance the checkindex to after the end of the
       headers, for the pipelining case mostly */
    req->checkindex += (end - line) + strlen(end_of_headers);

  /* **** Persistence ****
   *
   * If the request is a HTTP/1.0 one, we close the connection unconditionally
   * when we're done.
   *
   * If the request is a HTTP/1.1 one, we MUST check for a "Connection:"
   * header that might say "close". If it does, we close a connection when
   * this request is processed. Otherwise, we keep the connection alive for X
   * seconds.
   */

  do {
    if(got_exit_signal)
      return 1; /* done */

    if((req->cl == 0) && strncasecompare("Content-Length:", line, 15)) {
      /* If we don't ignore content-length, we read it and we read the whole
         request including the body before we return. If we've been told to
         ignore the content-length, we will return as soon as all headers
         have been received */
      char *endptr;
      char *ptr = line + 15;
      unsigned long clen = 0;
      while(*ptr && ISSPACE(*ptr))
        ptr++;
      endptr = ptr;
      errno = 0;
      clen = strtoul(ptr, &endptr, 10);
      if((ptr == endptr) || !ISSPACE(*endptr) || (ERANGE == errno)) {
        /* this assumes that a zero Content-Length is valid */
        logmsg("Found invalid Content-Length: (%s) in the request", ptr);
        req->open = FALSE; /* closes connection */
        return 1; /* done */
      }
      req->cl = clen - req->skip;

      logmsg("Found Content-Length: %lu in the request", clen);
      if(req->skip)
        logmsg("... but will abort after %zu bytes", req->cl);
      break;
    }
    else if(strncasecompare("Transfer-Encoding: chunked", line,
                            strlen("Transfer-Encoding: chunked"))) {
      /* chunked data coming in */
      chunked = TRUE;
    }

    if(chunked) {
      if(strstr(req->reqbuf, "\r\n0\r\n\r\n"))
        /* end of chunks reached */
        return 1; /* done */
      else
        return 0; /* not done */
    }

    line = strchr(line, '\n');
    if(line)
      line++;

  } while(line);

  if(!req->auth && strstr(req->reqbuf, "Authorization:")) {
    req->auth = TRUE; /* Authorization: header present! */
    if(req->auth_req)
      logmsg("Authorization header found, as required");
  }

  if(strstr(req->reqbuf, "Authorization: Negotiate")) {
    /* Negotiate iterations */
    static long prev_testno = -1;
    static long prev_partno = -1;
    logmsg("Negotiate: prev_testno: %d, prev_partno: %d",
            prev_testno, prev_partno);
    if(req->testno != prev_testno) {
      prev_testno = req->testno;
      prev_partno = req->partno;
    }
    prev_partno += 1;
    req->partno = prev_partno;
  }
  else if(!req->digest && strstr(req->reqbuf, "Authorization: Digest")) {
    /* If the client is passing this Digest-header, we set the part number
       to 1000. Not only to spice up the complexity of this, but to make
       Digest stuff to work in the test suite. */
    req->partno += 1000;
    req->digest = TRUE; /* header found */
    logmsg("Received Digest request, sending back data %ld", req->partno);
  }
  else if(!req->ntlm &&
          strstr(req->reqbuf, "Authorization: NTLM TlRMTVNTUAAD")) {
    /* If the client is passing this type-3 NTLM header */
    req->partno += 1002;
    req->ntlm = TRUE; /* NTLM found */
    logmsg("Received NTLM type-3, sending back data %ld", req->partno);
    if(req->cl) {
      logmsg("  Expecting %zu POSTed bytes", req->cl);
    }
  }
  else if(!req->ntlm &&
          strstr(req->reqbuf, "Authorization: NTLM TlRMTVNTUAAB")) {
    /* If the client is passing this type-1 NTLM header */
    req->partno += 1001;
    req->ntlm = TRUE; /* NTLM found */
    logmsg("Received NTLM type-1, sending back data %ld", req->partno);
  }
  else if((req->partno >= 1000) &&
          strstr(req->reqbuf, "Authorization: Basic")) {
    /* If the client is passing this Basic-header and the part number is
       already >=1000, we add 1 to the part number.  This allows simple Basic
       authentication negotiation to work in the test suite. */
    req->partno += 1;
    logmsg("Received Basic request, sending back data %ld", req->partno);
  }
  if(strstr(req->reqbuf, "Connection: close"))
    req->open = FALSE; /* close connection after this request */

  if(!req->pipe &&
     req->open &&
     req->prot_version >= 11 &&
     end &&
     req->reqbuf + req->offset > end + strlen(end_of_headers) &&
     !req->cl &&
     (!strncmp(req->reqbuf, "GET", strlen("GET")) ||
      !strncmp(req->reqbuf, "HEAD", strlen("HEAD")))) {
    /* If we have a persistent connection, HTTP version >= 1.1
       and GET/HEAD request, enable pipelining. */
    req->checkindex = (end - req->reqbuf) + strlen(end_of_headers);
    req->pipelining = TRUE;
  }

  while(req->pipe) {
    if(got_exit_signal)
      return 1; /* done */
    /* scan for more header ends within this chunk */
    line = &req->reqbuf[req->checkindex];
    end = strstr(line, end_of_headers);
    if(!end)
      break;
    req->checkindex += (end - line) + strlen(end_of_headers);
    req->pipe--;
  }

  /* If authentication is required and no auth was provided, end now. This
     makes the server NOT wait for PUT/POST data and you can then make the
     test case send a rejection before any such data has been sent. Test case
     154 uses this.*/
  if(req->auth_req && !req->auth) {
    logmsg("Return early due to auth requested by none provided");
    return 1; /* done */
  }

  if(req->upgrade && strstr(req->reqbuf, "Upgrade:")) {
    /* we allow upgrade and there was one! */
    logmsg("Found Upgrade: in request and allows it");
    req->upgrade_request = TRUE;
  }

  if(req->cl > 0) {
    if(req->cl <= req->offset - (end - req->reqbuf) - strlen(end_of_headers))
      return 1; /* done */
    else
      return 0; /* not complete yet */
  }

  return 1; /* done */
}