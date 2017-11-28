                 host = thost;
             } else if (!t) {
                 snprintf(thost, sizeof(thost), "%s:%d",host, vport);
                 host = thost;
             }
         } // else nothing to alter port-wise.
-        int url_sz = strlen(url) + 32 + Config.appendDomainLen +
-                     strlen(host);
+        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen + strlen(host);
         http->uri = (char *)xcalloc(url_sz, 1);
-        const char *protocol = switchedToHttps ?
-                               "https" : AnyP::UriScheme(conn->port->transport.protocol).c_str();
-        snprintf(http->uri, url_sz, "%s://%s%s", protocol, host, url);
-        debugs(33, 5, "ACCEL VHOST REWRITE: '" << http->uri << "'");
+        const SBuf &scheme = AnyP::UriScheme(conn->transferProtocol.protocol).image();
+        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s" SQUIDSBUFPH, SQUIDSBUFPRINT(scheme), host, SQUIDSBUFPRINT(url));
+        debugs(33, 5, "ACCEL VHOST REWRITE: " << http->uri);
     } else if (conn->port->defaultsite /* && !vhost */) {
         debugs(33, 5, "ACCEL DEFAULTSITE REWRITE: defaultsite=" << conn->port->defaultsite << " + vport=" << vport);
-        int url_sz = strlen(url) + 32 + Config.appendDomainLen +
-                     strlen(conn->port->defaultsite);
+        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen +
+                           strlen(conn->port->defaultsite);
         http->uri = (char *)xcalloc(url_sz, 1);
         char vportStr[32];
         vportStr[0] = '\0';
         if (vport > 0) {
             snprintf(vportStr, sizeof(vportStr),":%d",vport);
         }
-        snprintf(http->uri, url_sz, "%s://%s%s%s",
-                 AnyP::UriScheme(conn->port->transport.protocol).c_str(), conn->port->defaultsite, vportStr, url);
-        debugs(33, 5, "ACCEL DEFAULTSITE REWRITE: '" << http->uri <<"'");
+        const SBuf &scheme = AnyP::UriScheme(conn->transferProtocol.protocol).image();
+        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s%s" SQUIDSBUFPH,
+                 SQUIDSBUFPRINT(scheme), conn->port->defaultsite, vportStr, SQUIDSBUFPRINT(url));
+        debugs(33, 5, "ACCEL DEFAULTSITE REWRITE: " << http->uri);
     } else if (vport > 0 /* && (!vhost || no Host:) */) {
         debugs(33, 5, "ACCEL VPORT REWRITE: *_port IP + vport=" << vport);
         /* Put the local socket IP address as the hostname, with whatever vport we found  */
-        int url_sz = strlen(url) + 32 + Config.appendDomainLen;
+        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen;
         http->uri = (char *)xcalloc(url_sz, 1);
         http->getConn()->clientConnection->local.toHostStr(ipbuf,MAX_IPSTRLEN);
-        snprintf(http->uri, url_sz, "%s://%s:%d%s",
-                 AnyP::UriScheme(conn->port->transport.protocol).c_str(),
-                 ipbuf, vport, url);
-        debugs(33, 5, "ACCEL VPORT REWRITE: '" << http->uri << "'");
+        const SBuf &scheme = AnyP::UriScheme(conn->transferProtocol.protocol).image();
+        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s:%d" SQUIDSBUFPH,
+                 SQUIDSBUFPRINT(scheme), ipbuf, vport, SQUIDSBUFPRINT(url));
+        debugs(33, 5, "ACCEL VPORT REWRITE: " << http->uri);
     }
 }
 
 static void
-prepareTransparentURL(ConnStateData * conn, ClientHttpRequest *http, char *url, const char *req_hdr)
+prepareTransparentURL(ConnStateData * conn, ClientHttpRequest *http, const Http1::RequestParserPointer &hp)
 {
-    char *host;
-    char ipbuf[MAX_IPSTRLEN];
-
-    if (*url != '/')
+    // TODO Must() on URI !empty when the parser supports throw. For now avoid assert().
+    if (!hp->requestUri().isEmpty() && hp->requestUri()[0] != '/')
         return; /* already in good shape */
 
     /* BUG: Squid cannot deal with '*' URLs (RFC2616 5.1.2) */
 
-    if ((host = mime_get_header(req_hdr, "Host")) != NULL) {
-        int url_sz = strlen(url) + 32 + Config.appendDomainLen +
-                     strlen(host);
+    if (const char *host = hp->getHeaderField("Host")) {
+        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen +
+                           strlen(host);
         http->uri = (char *)xcalloc(url_sz, 1);
-        snprintf(http->uri, url_sz, "%s://%s%s", AnyP::UriScheme(conn->port->transport.protocol).c_str(), host, url);
-        debugs(33, 5, "TRANSPARENT HOST REWRITE: '" << http->uri <<"'");
+        const SBuf &scheme = AnyP::UriScheme(conn->transferProtocol.protocol).image();
+        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s" SQUIDSBUFPH,
+                 SQUIDSBUFPRINT(scheme), host, SQUIDSBUFPRINT(hp->requestUri()));
+        debugs(33, 5, "TRANSPARENT HOST REWRITE: " << http->uri);
     } else {
         /* Put the local socket IP address as the hostname.  */
-        int url_sz = strlen(url) + 32 + Config.appendDomainLen;
+        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen;
         http->uri = (char *)xcalloc(url_sz, 1);
+        static char ipbuf[MAX_IPSTRLEN];
         http->getConn()->clientConnection->local.toHostStr(ipbuf,MAX_IPSTRLEN);
-        snprintf(http->uri, url_sz, "%s://%s:%d%s",
-                 AnyP::UriScheme(http->getConn()->port->transport.protocol).c_str(),
-                 ipbuf, http->getConn()->clientConnection->local.port(), url);
-        debugs(33, 5, "TRANSPARENT REWRITE: '" << http->uri << "'");
+        const SBuf &scheme = AnyP::UriScheme(http->getConn()->transferProtocol.protocol).image();
+        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s:%d" SQUIDSBUFPH,
+                 SQUIDSBUFPRINT(scheme),
+                 ipbuf, http->getConn()->clientConnection->local.port(), SQUIDSBUFPRINT(hp->requestUri()));
+        debugs(33, 5, "TRANSPARENT REWRITE: " << http->uri);
     }
 }
 
 /** Parse an HTTP request
  *
  *  \note Sets result->flags.parsed_ok to 0 if failed to parse the request,
  *          to 1 if the request was correctly parsed.
  *  \param[in] csd a ConnStateData. The caller must make sure it is not null
- *  \param[in] hp an HttpParser
+ *  \param[in] hp an Http1::RequestParser
  *  \param[out] mehtod_p will be set as a side-effect of the parsing.
  *          Pointed-to value will be set to Http::METHOD_NONE in case of
  *          parsing failure
  *  \param[out] http_ver will be set as a side-effect of the parsing
  *  \return NULL on incomplete requests,
- *          a ClientSocketContext structure on success or failure.
+ *          a Http::Stream on success or failure.
  */
-ClientSocketContext *
-parseHttpRequest(ConnStateData *csd, HttpParser *hp, HttpRequestMethod * method_p, Http::ProtocolVersion *http_ver)
+Http::Stream *
+parseHttpRequest(ConnStateData *csd, const Http1::RequestParserPointer &hp)
 {
-    char *req_hdr = NULL;
-    char *end;
-    size_t req_sz;
-    ClientHttpRequest *http;
-    ClientSocketContext *result;
-    StoreIOBuffer tempBuffer;
-    int r;
-
-    /* pre-set these values to make aborting simpler */
-    *method_p = Http::METHOD_NONE;
-
-    /* NP: don't be tempted to move this down or remove again.
-     * It's the only DDoS protection old-String has against long URL */
-    if ( hp->bufsiz <= 0) {
-        debugs(33, 5, "Incomplete request, waiting for end of request line");
-        return NULL;
-    } else if ( (size_t)hp->bufsiz >= Config.maxRequestHeaderSize && headersEnd(hp->buf, Config.maxRequestHeaderSize) == 0) {
-        debugs(33, 5, "parseHttpRequest: Too large request");
-        hp->request_parse_status = Http::scHeaderTooLarge;
-        return csd->abortRequestParsing("error:request-too-large");
-    }
-
-    /* Attempt to parse the first line; this'll define the method, url, version and header begin */
-    r = HttpParserParseReqLine(hp);
-
-    if (r == 0) {
-        debugs(33, 5, "Incomplete request, waiting for end of request line");
-        return NULL;
-    }
-
-    if (r == -1) {
-        return csd->abortRequestParsing("error:invalid-request");
-    }
+    /* Attempt to parse the first line; this will define where the method, url, version and header begin */
+    {
+        const bool parsedOk = hp->parse(csd->inBuf);
 
-    /* Request line is valid here .. */
-    *http_ver = Http::ProtocolVersion(hp->req.v_maj, hp->req.v_min);
+        // sync the buffers after parsing.
+        csd->inBuf = hp->remaining();
 
-    /* This call scans the entire request, not just the headers */
-    if (hp->req.v_maj > 0) {
-        if ((req_sz = headersEnd(hp->buf, hp->bufsiz)) == 0) {
-            debugs(33, 5, "Incomplete request, waiting for end of headers");
+        if (hp->needsMoreData()) {
+            debugs(33, 5, "Incomplete request, waiting for end of request line");
             return NULL;
         }
-    } else {
-        debugs(33, 3, "parseHttpRequest: Missing HTTP identifier");
-        req_sz = HttpParserReqSz(hp);
-    }
 
-    /* We know the whole request is in hp->buf now */
-
-    assert(req_sz <= (size_t) hp->bufsiz);
-
-    /* Will the following be true with HTTP/0.9 requests? probably not .. */
-    /* So the rest of the code will need to deal with '0'-byte headers (ie, none, so don't try parsing em) */
-    assert(req_sz > 0);
-
-    hp->hdr_end = req_sz - 1;
-
-    hp->hdr_start = hp->req.end + 1;
+        if (csd->mayTunnelUnsupportedProto()) {
+            csd->preservedClientData = hp->parsed();
+            csd->preservedClientData.append(csd->inBuf);
+        }
 
-    /* Enforce max_request_size */
-    if (req_sz >= Config.maxRequestHeaderSize) {
-        debugs(33, 5, "parseHttpRequest: Too large request");
-        hp->request_parse_status = Http::scHeaderTooLarge;
-        return csd->abortRequestParsing("error:request-too-large");
+        if (!parsedOk) {
+            const bool tooBig =
+                hp->parseStatusCode == Http::scRequestHeaderFieldsTooLarge ||
+                hp->parseStatusCode == Http::scUriTooLong;
+            auto result = csd->abortRequestParsing(
+                              tooBig ? "error:request-too-large" : "error:invalid-request");
+            // assume that remaining leftovers belong to this bad request
+            if (!csd->inBuf.isEmpty())
+                csd->consumeInput(csd->inBuf.length());
+            return result;
+        }
     }
 
-    /* Set method_p */
-    *method_p = HttpRequestMethod(&hp->buf[hp->req.m_start], &hp->buf[hp->req.m_end]+1);
+    /* We know the whole request is in parser now */
+    debugs(11, 2, "HTTP Client " << csd->clientConnection);
+    debugs(11, 2, "HTTP Client REQUEST:\n---------\n" <<
+           hp->method() << " " << hp->requestUri() << " " << hp->messageProtocol() << "\n" <<
+           hp->mimeHeader() <<
+           "\n----------");
 
     /* deny CONNECT via accelerated ports */
-    if (*method_p == Http::METHOD_CONNECT && csd->port != NULL && csd->port->flags.accelSurrogate) {
-        debugs(33, DBG_IMPORTANT, "WARNING: CONNECT method received on " << csd->port->transport.protocol << " Accelerator port " << csd->port->s.port());
-        /* XXX need a way to say "this many character length string" */
-        debugs(33, DBG_IMPORTANT, "WARNING: for request: " << hp->buf);
-        hp->request_parse_status = Http::scMethodNotAllowed;
+    if (hp->method() == Http::METHOD_CONNECT && csd->port != NULL && csd->port->flags.accelSurrogate) {
+        debugs(33, DBG_IMPORTANT, "WARNING: CONNECT method received on " << csd->transferProtocol << " Accelerator port " << csd->port->s.port());
+        debugs(33, DBG_IMPORTANT, "WARNING: for request: " << hp->method() << " " << hp->requestUri() << " " << hp->messageProtocol());
+        hp->parseStatusCode = Http::scMethodNotAllowed;
         return csd->abortRequestParsing("error:method-not-allowed");
     }
 
     /* RFC 7540 section 11.6 registers the method PRI as HTTP/2 specific
      * Deny "PRI" method if used in HTTP/1.x or 0.9 versions.
      * If seen it signals a broken client or proxy has corrupted the traffic.
      */
-    if (*method_p == Http::METHOD_PRI && *http_ver < Http::ProtocolVersion(2,0)) {
-        debugs(33, DBG_IMPORTANT, "WARNING: PRI method received on " << csd->port->transport.protocol << "port " << csd->port->s.port());
-        debugs(33, DBG_IMPORTANT, "WARNING: for request: " << hp->buf);
-        hp->request_parse_status = Http::scMethodNotAllowed;
+    if (hp->method() == Http::METHOD_PRI && hp->messageProtocol() < Http::ProtocolVersion(2,0)) {
+        debugs(33, DBG_IMPORTANT, "WARNING: PRI method received on " << csd->transferProtocol << " port " << csd->port->s.port());
+        debugs(33, DBG_IMPORTANT, "WARNING: for request: " << hp->method() << " " << hp->requestUri() << " " << hp->messageProtocol());
+        hp->parseStatusCode = Http::scMethodNotAllowed;
         return csd->abortRequestParsing("error:method-not-allowed");
     }
 
-    if (*method_p == Http::METHOD_NONE) {
-        /* XXX need a way to say "this many character length string" */
-        debugs(33, DBG_IMPORTANT, "clientParseRequestMethod: Unsupported method in request '" << hp->buf << "'");
-        hp->request_parse_status = Http::scMethodNotAllowed;
+    if (hp->method() == Http::METHOD_NONE) {
+        debugs(33, DBG_IMPORTANT, "WARNING: Unsupported method: " << hp->method() << " " << hp->requestUri() << " " << hp->messageProtocol());
+        hp->parseStatusCode = Http::scMethodNotAllowed;
         return csd->abortRequestParsing("error:unsupported-request-method");
     }
 
-    /*
-     * Process headers after request line
-     * TODO: Use httpRequestParse here.
-     */
-    /* XXX this code should be modified to take a const char * later! */
-    req_hdr = (char *) hp->buf + hp->req.end + 1;
-
-    debugs(33, 3, "parseHttpRequest: req_hdr = {" << req_hdr << "}");
-
-    end = (char *) hp->buf + hp->hdr_end;
-
-    debugs(33, 3, "parseHttpRequest: end = {" << end << "}");
-
-    debugs(33, 3, "parseHttpRequest: prefix_sz = " <<
-           (int) HttpParserRequestLen(hp) << ", req_line_sz = " <<
-           HttpParserReqSz(hp));
+    // Process headers after request line
+    debugs(33, 3, "complete request received. " <<
+           "prefix_sz = " << hp->messageHeaderSize() <<
+           ", request-line-size=" << hp->firstLineSize() <<
+           ", mime-header-size=" << hp->headerBlockSize() <<
+           ", mime header block:\n" << hp->mimeHeader() << "\n----------");
 
     /* Ok, all headers are received */
-    http = new ClientHttpRequest(csd);
+    ClientHttpRequest *http = new ClientHttpRequest(csd);
+
+    http->req_sz = hp->messageHeaderSize();
+    Http::Stream *result = new Http::Stream(csd->clientConnection, http);
 
-    http->req_sz = HttpParserRequestLen(hp);
-    result = new ClientSocketContext(csd->clientConnection, http);
+    StoreIOBuffer tempBuffer;
     tempBuffer.data = result->reqbuf;
     tempBuffer.length = HTTP_REQBUF_SZ;
 
     ClientStreamData newServer = new clientReplyContext(http);
     ClientStreamData newClient = result;
     clientStreamInit(&http->client_stream, clientGetMoreData, clientReplyDetach,
                      clientReplyStatus, newServer, clientSocketRecipient,
                      clientSocketDetach, newClient, tempBuffer);
 
-    debugs(33, 5, "parseHttpRequest: Request Header is\n" <<(hp->buf) + hp->hdr_start);
-
     /* set url */
-    /*
-     * XXX this should eventually not use a malloc'ed buffer; the transformation code
-     * below needs to be modified to not expect a mutable nul-terminated string.
-     */
-    char *url = (char *)xmalloc(hp->req.u_end - hp->req.u_start + 16);
-
-    memcpy(url, hp->buf + hp->req.u_start, hp->req.u_end - hp->req.u_start + 1);
-
-    url[hp->req.u_end - hp->req.u_start + 1] = '\0';
-
-#if THIS_VIOLATES_HTTP_SPECS_ON_URL_TRANSFORMATION
-
-    if ((t = strchr(url, '#'))) /* remove HTML anchors */
-        *t = '\0';
-
-#endif
-
     debugs(33,5, "Prepare absolute URL from " <<
            (csd->transparent()?"intercept":(csd->port->flags.accelSurrogate ? "accel":"")));
     /* Rewrite the URL in transparent or accelerator mode */
     /* NP: there are several cases to traverse here:
      *  - standard mode (forward proxy)
      *  - transparent mode (TPROXY)
      *  - transparent mode with failures
      *  - intercept mode (NAT)
      *  - intercept mode with failures
      *  - accelerator mode (reverse proxy)
-     *  - internal URL
+     *  - internal relative-URL
      *  - mixed combos of the above with internal URL
      *  - remote interception with PROXY protocol
      *  - remote reverse-proxy with PROXY protocol
      */
     if (csd->transparent()) {
         /* intercept or transparent mode, properly working with no failures */
-        prepareTransparentURL(csd, http, url, req_hdr);
+        prepareTransparentURL(csd, http, hp);
 
-    } else if (internalCheck(url)) {
+    } else if (internalCheck(hp->requestUri())) { // NP: only matches relative-URI
         /* internal URL mode */
         /* prepend our name & port */
-        http->uri = xstrdup(internalLocalUri(NULL, url));
+        http->uri = xstrdup(internalLocalUri(NULL, hp->requestUri()));
         // We just re-wrote the URL. Must replace the Host: header.
         //  But have not parsed there yet!! flag for local-only handling.
         http->flags.internal = true;
 
     } else if (csd->port->flags.accelSurrogate || csd->switchedToHttps()) {
         /* accelerator mode */
-        prepareAcceleratedURL(csd, http, url, req_hdr);
+        prepareAcceleratedURL(csd, http, hp);
     }
 
     if (!http->uri) {
         /* No special rewrites have been applied above, use the
          * requested url. may be rewritten later, so make extra room */
-        int url_sz = strlen(url) + Config.appendDomainLen + 5;
+        int url_sz = hp->requestUri().length() + Config.appendDomainLen + 5;
         http->uri = (char *)xcalloc(url_sz, 1);
-        strcpy(http->uri, url);
+        SBufToCstring(http->uri, hp->requestUri());
     }
 
-    debugs(33, 5, "parseHttpRequest: Complete request received");
-
-    // XXX: crop this dump at the end of headers. No need for extras
-    debugs(11, 2, "HTTP Client " << csd->clientConnection);
-    debugs(11, 2, "HTTP Client REQUEST:\n---------\n" << (hp->buf) + hp->req.m_start << "\n----------");
-
     result->flags.parsed_ok = 1;
-    xfree(url);
-    return result;
-}
-
-/// Prepare inBuf for I/O. This method balances several conflicting desires:
-/// 1. Do not read too few bytes at a time.
-/// 2. Do not waste too much buffer space.
-/// 3. Do not [re]allocate or memmove the buffer too much.
-/// 4. Obey Config.maxRequestBufferSize limit.
-void
-ConnStateData::In::maybeMakeSpaceAvailable()
-{
-    // The hard-coded parameters are arbitrary but seem reasonable.
-    // A careful study of Squid I/O and parsing patterns is needed to tune them.
-    SBufReservationRequirements requirements;
-    requirements.minSpace = 1024; // smaller I/Os are not worth their overhead
-    requirements.idealSpace = CLIENT_REQ_BUF_SZ; // we expect few larger I/Os
-    requirements.maxCapacity = Config.maxRequestBufferSize;
-    requirements.allowShared = true; // allow because inBuf is used immediately
-    buf.reserve(requirements);
-    if (!buf.spaceSize())
-        debugs(33, 4, "request buffer full: client_request_buffer_max_size=" << Config.maxRequestBufferSize);
-}
-
-void
-ConnStateData::addContextToQueue(ClientSocketContext * context)
-{
-    ClientSocketContext::Pointer *S;
-
-    for (S = (ClientSocketContext::Pointer *) & currentobject; S->getRaw();
-            S = &(*S)->next);
-    *S = context;
-
-    ++nrequests;
-}
-
-int
-ConnStateData::getConcurrentRequestCount() const
-{
-    int result = 0;
-    ClientSocketContext::Pointer *T;
-
-    for (T = (ClientSocketContext::Pointer *) &currentobject;
-            T->getRaw(); T = &(*T)->next, ++result);
     return result;
 }
 
-int
+bool
 ConnStateData::connFinishedWithConn(int size)
 {
     if (size == 0) {
-        if (getConcurrentRequestCount() == 0 && in.buf.isEmpty()) {
+        if (pipeline.empty() && inBuf.isEmpty()) {
             /* no current or pending requests */
             debugs(33, 4, HERE << clientConnection << " closed");
-            return 1;
+            return true;
         } else if (!Config.onoff.half_closed_clients) {
             /* admin doesn't want to support half-closed client sockets */
             debugs(33, 3, HERE << clientConnection << " aborted (half_closed_clients disabled)");
-            notifyAllContexts(0); // no specific error implies abort
-            return 1;
+            pipeline.terminateAll(0);
+            return true;
         }
     }
 
-    return 0;
+    return false;
 }
 
 void
 ConnStateData::consumeInput(const size_t byteCount)
 {
-    assert(byteCount > 0 && byteCount <= in.buf.length());
-    in.buf.consume(byteCount);
-    debugs(33, 5, "in.buf has " << in.buf.length() << " unused bytes");
-}
-
-// TODO: Remove when renaming ConnStateData
-void
-connNoteUseOfBuffer(ConnStateData* conn, size_t byteCount)
-{
-    conn->consumeInput(byteCount);
+    assert(byteCount > 0 && byteCount <= inBuf.length());
+    inBuf.consume(byteCount);
+    debugs(33, 5, "inBuf has " << inBuf.length() << " unused bytes");
 }
 
 void
 ConnStateData::clientAfterReadingRequests()
 {
     // Were we expecting to read more request body from half-closed connection?
