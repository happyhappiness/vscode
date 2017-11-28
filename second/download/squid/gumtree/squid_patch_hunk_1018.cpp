         bumpAction = (Ssl::BumpMode)answer.kind;
     } else
         bumpAction = Ssl::bumpSplice;
 
     connState->serverBump()->act.step2 = bumpAction;
     connState->sslBumpMode = bumpAction;
+    Http::StreamPointer context = connState->pipeline.front();
+    if (ClientHttpRequest *http = (context ? context->http : nullptr))
+        http->al->ssl.bumpMode = bumpAction;
 
     if (bumpAction == Ssl::bumpTerminate) {
         connState->clientConnection->close();
     } else if (bumpAction != Ssl::bumpSplice) {
-        connState->startPeekAndSpliceDone();
+        connState->startPeekAndSplice();
+    } else if (!connState->splice())
+        connState->clientConnection->close();
+}
+
+bool
+ConnStateData::splice()
+{
+    // normally we can splice here, because we just got client hello message
+
+    if (fd_table[clientConnection->fd].ssl.get()) {
+        // Restore default read methods
+        fd_table[clientConnection->fd].read_method = &default_read_method;
+        fd_table[clientConnection->fd].write_method = &default_write_method;
+    }
+
+    // XXX: assuming that there was an HTTP/1.1 CONNECT to begin with...
+    // reset the current protocol to HTTP/1.1 (was "HTTPS" for the bumping process)
+    transferProtocol = Http::ProtocolVersion();
+    assert(!pipeline.empty());
+    Http::StreamPointer context = pipeline.front();
+    Must(context);
+    Must(context->http);
+    ClientHttpRequest *http = context->http;
+    HttpRequest::Pointer request = http->request;
+    context->finished();
+    if (transparent()) {
+        // For transparent connections, make a new fake CONNECT request, now
+        // with SNI as target. doCallout() checks, adaptations may need that.
+        return fakeAConnectRequest("splice", preservedClientData);
     } else {
-        //Normally we can splice here, because we just got client hello message
-        SSL *ssl = fd_table[connState->clientConnection->fd].ssl;
-        BIO *b = SSL_get_rbio(ssl);
-        Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(b->ptr);
-        MemBuf const &rbuf = bio->rBufData();
-        debugs(83,5, "Bio for  " << connState->clientConnection << " read " << rbuf.contentSize() << " helo bytes");
-        // Do splice:
-        fd_table[connState->clientConnection->fd].read_method = &default_read_method;
-        fd_table[connState->clientConnection->fd].write_method = &default_write_method;
-
-        ClientSocketContext::Pointer context = connState->getCurrentContext();
-        Must(context != NULL);
-        if (connState->transparent()) {
-            // If we are going to fake the second CONNECT, clear the first one.
-            context->connIsFinished();
-
-            // fake a CONNECT request to force connState to tunnel
-            // XXX: copy from MemBuf reallocates, not a regression since old code did too
-            SBuf temp;
-            temp.append(rbuf.content(), rbuf.contentSize());
-            connState->fakeAConnectRequest("intercepted TLS spliced", temp);
-        } else {
-            // in.buf still has the "CONNECT ..." request data, reset it to SSL hello message
-            connState->in.buf.append(rbuf.content(), rbuf.contentSize());
-            ClientHttpRequest *http = context->http;
-            tunnelStart(http);
-        }
+        // For non transparent connections  make a new tunneled CONNECT, which
+        // also sets the HttpRequest::flags::forceTunnel flag to avoid
+        // respond with "Connection Established" to the client.
+        // This fake CONNECT request required to allow use of SNI in
+        // doCallout() checks and adaptations.
+        return initiateTunneledRequest(request, Http::METHOD_CONNECT, "splice", preservedClientData);
     }
 }
 
 void
-ConnStateData::startPeekAndSpliceDone()
+ConnStateData::startPeekAndSplice()
 {
     // This is the Step2 of the SSL bumping
     assert(sslServerBump);
+    Http::StreamPointer context = pipeline.front();
+    ClientHttpRequest *http = context ? context->http : nullptr;
+
     if (sslServerBump->step == Ssl::bumpStep1) {
         sslServerBump->step = Ssl::bumpStep2;
         // Run a accessList check to check if want to splice or continue bumping
 
-        ACLFilledChecklist *acl_checklist = new ACLFilledChecklist(Config.accessList.ssl_bump, sslServerBump->request.getRaw(), NULL);
+        ACLFilledChecklist *acl_checklist = new ACLFilledChecklist(Config.accessList.ssl_bump, sslServerBump->request.getRaw(), nullptr);
+        acl_checklist->al = http ? http->al : nullptr;
         //acl_checklist->src_addr = params.conn->remote;
         //acl_checklist->my_addr = s->s;
         acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpNone));
         acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpClientFirst));
         acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpServerFirst));
         acl_checklist->nonBlockingCheck(httpsSslBumpStep2AccessCheckDone, this);
         return;
     }
 
-    FwdState::fwdStart(clientConnection, sslServerBump->entry, sslServerBump->request.getRaw());
+    // will call httpsPeeked() with certificate and connection, eventually
+    Security::ContextPointer unConfiguredCTX(Ssl::createSSLContext(port->signingCert, port->signPkey, *port));
+    fd_table[clientConnection->fd].dynamicTlsContext = unConfiguredCTX;
+
+    if (!httpsCreate(clientConnection, unConfiguredCTX))
+        return;
+
+    switchedToHttps_ = true;
+
+    auto ssl = fd_table[clientConnection->fd].ssl.get();
+    BIO *b = SSL_get_rbio(ssl);
+    Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(BIO_get_data(b));
+    bio->setReadBufData(inBuf);
+    bio->hold(true);
+
+    // Here squid should have all of the client hello message so the
+    // Squid_SSL_accept should return 0;
+    // This block exist only to force openSSL parse client hello and detect
+    // ERR_SECURE_ACCEPT_FAIL error, which should be checked and splice if required.
+    int ret = 0;
+    if ((ret = Squid_SSL_accept(this, NULL)) < 0) {
+        debugs(83, 2, "SSL_accept failed.");
+        HttpRequest::Pointer request(http ? http->request : nullptr);
+        if (!clientTunnelOnError(this, context, request, HttpRequestMethod(), ERR_SECURE_ACCEPT_FAIL))
+            clientConnection->close();
+        return;
+    }
+
+    // We need to reset inBuf here, to be used by incoming requests in the case
+    // of SSL bump
+    inBuf.clear();
+
+    debugs(83, 5, "Peek and splice at step2 done. Start forwarding the request!!! ");
+    FwdState::Start(clientConnection, sslServerBump->entry, sslServerBump->request.getRaw(), http ? http->al : NULL);
 }
 
 void
 ConnStateData::doPeekAndSpliceStep()
 {
-    SSL *ssl = fd_table[clientConnection->fd].ssl;
+    auto ssl = fd_table[clientConnection->fd].ssl.get();
     BIO *b = SSL_get_rbio(ssl);
     assert(b);
-    Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(b->ptr);
+    Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(BIO_get_data(b));
 
     debugs(33, 5, "PeekAndSplice mode, proceed with client negotiation. Currrent state:" << SSL_state_string_long(ssl));
     bio->hold(false);
 
     Comm::SetSelect(clientConnection->fd, COMM_SELECT_WRITE, clientNegotiateSSL, this, 0);
     switchedToHttps_ = true;
 }
 
 void
-ConnStateData::httpsPeeked(PinnedIdleContext pic)
+ConnStateData::httpsPeeked(Comm::ConnectionPointer serverConnection)
 {
     Must(sslServerBump != NULL);
-    Must(sslServerBump->request == pic.request);
-    Must(currentobject == NULL || currentobject->http == NULL || currentobject->http->request == pic.request.getRaw());
 
-    if (Comm::IsConnOpen(pic.connection)) {
-        notePinnedConnectionBecameIdle(pic);
+    if (Comm::IsConnOpen(serverConnection)) {
+        pinConnection(serverConnection, NULL, NULL, false);
 
         debugs(33, 5, HERE << "bumped HTTPS server: " << sslConnectHostOrIp);
-    } else
+    } else {
         debugs(33, 5, HERE << "Error while bumping: " << sslConnectHostOrIp);
 
+        //  copy error detail from bump-server-first request to CONNECT request
+        if (!pipeline.empty() && pipeline.front()->http != nullptr && pipeline.front()->http->request)
+            pipeline.front()->http->request->detailError(sslServerBump->request->errType, sslServerBump->request->errDetail);
+    }
+
     getSslContextStart();
 }
 
 #endif /* USE_OPENSSL */
 
-void
-ConnStateData::fakeAConnectRequest(const char *reason, const SBuf &payload)
+bool
+ConnStateData::initiateTunneledRequest(HttpRequest::Pointer const &cause, Http::MethodType const method, const char *reason, const SBuf &payload)
 {
     // fake a CONNECT request to force connState to tunnel
     SBuf connectHost;
+    unsigned short connectPort = 0;
+
+    if (pinning.serverConnection != nullptr) {
+        static char ip[MAX_IPSTRLEN];
+        pinning.serverConnection->remote.toHostStr(ip, sizeof(ip));
+        connectHost.assign(ip);
+        connectPort = pinning.serverConnection->remote.port();
+    } else if (cause && cause->method == Http::METHOD_CONNECT) {
+        // We are inside a (not fully established) CONNECT request
+        connectHost = cause->url.host();
+        connectPort = cause->url.port();
+    } else {
+        debugs(33, 2, "Not able to compute URL, abort request tunneling for " << reason);
+        return false;
+    }
+
+    debugs(33, 2, "Request tunneling for " << reason);
+    ClientHttpRequest *http = buildFakeRequest(method, connectHost, connectPort, payload);
+    HttpRequest::Pointer request = http->request;
+    request->flags.forceTunnel = true;
+    http->calloutContext = new ClientRequestContext(http);
+    http->doCallouts();
+    clientProcessRequestFinished(this, request);
+    return true;
+}
+
+bool
+ConnStateData::fakeAConnectRequest(const char *reason, const SBuf &payload)
+{
+    debugs(33, 2, "fake a CONNECT request to force connState to tunnel for " << reason);
+
+    SBuf connectHost;
+    assert(transparent());
+    const unsigned short connectPort = clientConnection->local.port();
+
 #if USE_OPENSSL
-    if (serverBump() && !serverBump()->clientSni.isEmpty()) {
+    if (serverBump() && !serverBump()->clientSni.isEmpty())
         connectHost.assign(serverBump()->clientSni);
-        if (clientConnection->local.port() > 0)
-            connectHost.appendf(":%d",clientConnection->local.port());
-    } else
+    else
 #endif
     {
         static char ip[MAX_IPSTRLEN];
-        connectHost.assign(clientConnection->local.toUrl(ip, sizeof(ip)));
+        clientConnection->local.toHostStr(ip, sizeof(ip));
+        connectHost.assign(ip);
     }
-    // Pre-pend this fake request to the TLS bits already in the buffer
-    SBuf retStr;
-    retStr.append("CONNECT ");
-    retStr.append(connectHost);
-    retStr.append(" HTTP/1.1\r\nHost: ");
-    retStr.append(connectHost);
-    retStr.append("\r\n\r\n");
-    retStr.append(payload);
-    in.buf = retStr;
-    bool ret = handleReadData();
-    if (ret)
-        ret = clientParseRequests();
 
-    if (!ret) {
-        debugs(33, 2, "Failed to start fake CONNECT request for " << reason << " connection: " << clientConnection);
-        clientConnection->close();
-    }
+    ClientHttpRequest *http = buildFakeRequest(Http::METHOD_CONNECT, connectHost, connectPort, payload);
+
+    http->calloutContext = new ClientRequestContext(http);
+    HttpRequest::Pointer request = http->request;
+    http->doCallouts();
+    clientProcessRequestFinished(this, request);
+    return true;
+}
+
+ClientHttpRequest *
+ConnStateData::buildFakeRequest(Http::MethodType const method, SBuf &useHost, unsigned short usePort, const SBuf &payload)
+{
+    ClientHttpRequest *http = new ClientHttpRequest(this);
+    Http::Stream *stream = new Http::Stream(clientConnection, http);
+
+    StoreIOBuffer tempBuffer;
+    tempBuffer.data = stream->reqbuf;
+    tempBuffer.length = HTTP_REQBUF_SZ;
+
+    ClientStreamData newServer = new clientReplyContext(http);
+    ClientStreamData newClient = stream;
+    clientStreamInit(&http->client_stream, clientGetMoreData, clientReplyDetach,
+                     clientReplyStatus, newServer, clientSocketRecipient,
+                     clientSocketDetach, newClient, tempBuffer);
+
+    http->uri = SBufToCstring(useHost);
+    stream->flags.parsed_ok = 1; // Do we need it?
+    stream->mayUseConnection(true);
+
+    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "clientLifetimeTimeout",
+                                     CommTimeoutCbPtrFun(clientLifetimeTimeout, stream->http));
+    commSetConnTimeout(clientConnection, Config.Timeout.lifetime, timeoutCall);
+
+    stream->registerWithConn();
+
+    // Setup Http::Request object. Maybe should be replaced by a call to (modified)
+    // clientProcessRequest
+    HttpRequest::Pointer request = new HttpRequest();
+    AnyP::ProtocolType proto = (method == Http::METHOD_NONE) ? AnyP::PROTO_AUTHORITY_FORM : AnyP::PROTO_HTTP;
+    request->url.setScheme(proto, nullptr);
+    request->method = method;
+    request->url.host(useHost.c_str());
+    request->url.port(usePort);
+    http->request = request.getRaw();
+    HTTPMSGLOCK(http->request);
+
+    request->clientConnectionManager = this;
+
+    if (proto == AnyP::PROTO_HTTP)
+        request->header.putStr(Http::HOST, useHost.c_str());
+    request->flags.intercepted = ((clientConnection->flags & COMM_INTERCEPTION) != 0);
+    request->flags.interceptTproxy = ((clientConnection->flags & COMM_TRANSPARENT) != 0 );
+    request->sources |= ((switchedToHttps() || port->transport.protocol == AnyP::PROTO_HTTPS) ? HttpMsg::srcHttps : HttpMsg::srcHttp);
+#if USE_AUTH
+    if (getAuth())
+        request->auth_user_request = getAuth();
+#endif
+    request->client_addr = clientConnection->remote;
+#if FOLLOW_X_FORWARDED_FOR
+    request->indirect_client_addr = clientConnection->remote;
+#endif /* FOLLOW_X_FORWARDED_FOR */
+    request->my_addr = clientConnection->local;
+    request->myportname = port->name;
+
+    inBuf = payload;
+    flags.readMore = false;
+
+    setLogUri(http, urlCanonicalClean(request.getRaw()));
+    return http;
 }
 
 /// check FD after clientHttp[s]ConnectionOpened, adjust HttpSockets as needed
 static bool
 OpenedHttpSocket(const Comm::ConnectionPointer &c, const Ipc::FdNoteId portType)
 {
