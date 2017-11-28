     /*
      * client_addr.IsNoAddr()  indicates this is an "internal" request
      * from peer_digest.c, asn.c, netdb.c, etc and should always
      * be allowed.  yuck, I know.
      */
 
-    if (!request->client_addr.IsNoAddr() && Config.accessList.miss) {
+    if (Config.accessList.miss && !request->client_addr.IsNoAddr()) {
         /*
          * Check if this host is allowed to fetch MISSES from us (miss_access)
          * default is to allow.
          */
         ACLFilledChecklist ch(Config.accessList.miss, request, NULL);
         ch.src_addr = request->client_addr;
         ch.my_addr = request->my_addr;
-        answer = ch.fastCheck();
-
-        if (answer == 0) {
-            err = errorCon(ERR_FORWARDING_DENIED, HTTP_FORBIDDEN, request);
+        if (ch.fastCheck() == ACCESS_DENIED) {
+            debugs(26, 4, HERE << "MISS access forbidden.");
+            err = new ErrorState(ERR_FORWARDING_DENIED, HTTP_FORBIDDEN, request);
             *status_ptr = HTTP_FORBIDDEN;
-            errorSend(fd, err);
+            errorSend(http->getConn()->clientConnection, err);
             return;
         }
     }
 
-    debugs(26, 3, "tunnelStart: '" << RequestMethodStr(request->method) << " " << url << "'");
-    statCounter.server.all.requests++;
-    statCounter.server.other.requests++;
-    /* Create socket. */
-    IpAddress temp = getOutgoingAddr(request,NULL);
-
-    // if IPv6 is disabled try to force IPv4-only outgoing.
-    if (!Ip::EnableIpv6 && !temp.SetIPv4()) {
-        debugs(50, 4, "tunnelStart: IPv6 is Disabled. Tunnel failed from " << temp);
-        ErrorState *anErr = errorCon(ERR_CONNECT_FAIL, HTTP_SERVICE_UNAVAILABLE, request);
-        anErr->xerrno = EAFNOSUPPORT;
-        errorSend(fd, anErr);
-        return;
-    }
-
-    // if IPv6 is split-stack, prefer IPv4
-    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK) {
-        // NP: This is not a great choice of default,
-        // but with the current Internet being IPv4-majority has a higher success rate.
-        // if setting to IPv4 fails we dont care, that just means to use IPv6 outgoing.
-        temp.SetIPv4();
-    }
-
-    int flags = COMM_NONBLOCKING;
-    if (request->flags.spoof_client_ip) {
-        flags |= COMM_TRANSPARENT;
-    }
-    sock = comm_openex(SOCK_STREAM,
-                       IPPROTO_TCP,
-                       temp,
-                       flags,
-                       getOutgoingTOS(request),
-                       url);
-
-    if (sock == COMM_ERROR) {
-        debugs(26, 4, "tunnelStart: Failed because we're out of sockets.");
-        err = errorCon(ERR_SOCKET_FAILURE, HTTP_INTERNAL_SERVER_ERROR, request);
-        *status_ptr = HTTP_INTERNAL_SERVER_ERROR;
-        err->xerrno = errno;
-        errorSend(fd, err);
-        return;
-    }
-
-    // record local IP:port for %<la and %<lp logging
-    if (comm_local_port(sock))
-        request->hier.peer_local_addr = fd_table[sock].local_addr;
+    debugs(26, 3, HERE << "'" << RequestMethodStr(request->method) << " " << url << " " << request->http_ver << "'");
+    ++statCounter.server.all.requests;
+    ++statCounter.server.other.requests;
 
     tunnelState = new TunnelStateData;
-#if DELAY_POOLS
-
+#if USE_DELAY_POOLS
     tunnelState->server.setDelayId(DelayId::DelayClient(http));
 #endif
-
     tunnelState->url = xstrdup(url);
     tunnelState->request = HTTPMSGLOCK(request);
     tunnelState->server.size_ptr = size_ptr;
     tunnelState->status_ptr = status_ptr;
-    tunnelState->client.fd(fd);
-    tunnelState->server.fd(sock);
-    comm_add_close_handler(tunnelState->server.fd(),
-                           tunnelServerClosed,
-                           tunnelState);
-    comm_add_close_handler(tunnelState->client.fd(),
+    tunnelState->client.conn = http->getConn()->clientConnection;
+
+    comm_add_close_handler(tunnelState->client.conn->fd,
                            tunnelClientClosed,
                            tunnelState);
-    commSetTimeout(tunnelState->client.fd(),
-                   Config.Timeout.lifetime,
-                   tunnelTimeout,
-                   tunnelState);
-    commSetTimeout(tunnelState->server.fd(),
-                   Config.Timeout.connect,
-                   tunnelConnectTimeout,
-                   tunnelState);
-    peerSelect(request,
+
+    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "tunnelTimeout",
+                                     CommTimeoutCbPtrFun(tunnelTimeout, tunnelState));
+    commSetConnTimeout(tunnelState->client.conn, Config.Timeout.lifetime, timeoutCall);
+
+    peerSelect(&(tunnelState->serverDestinations), request,
                NULL,
                tunnelPeerSelectComplete,
                tunnelState);
 }
 
 static void
-tunnelProxyConnected(int fd, void *data)
+tunnelRelayConnectRequest(const Comm::ConnectionPointer &srv, void *data)
 {
     TunnelStateData *tunnelState = (TunnelStateData *)data;
     HttpHeader hdr_out(hoRequest);
     Packer p;
     http_state_flags flags;
-    debugs(26, 3, "tunnelProxyConnected: FD " << fd << " tunnelState=" << tunnelState);
+    debugs(26, 3, HERE << srv << ", tunnelState=" << tunnelState);
     memset(&flags, '\0', sizeof(flags));
     flags.proxying = tunnelState->request->flags.proxying;
     MemBuf mb;
     mb.init();
     mb.Printf("CONNECT %s HTTP/1.1\r\n", tunnelState->url);
     HttpStateData::httpBuildRequestHeader(tunnelState->request,
-                                          tunnelState->request,
                                           NULL,			/* StoreEntry */
+                                          NULL,			/* AccessLogEntry */
                                           &hdr_out,
                                           flags);			/* flags */
     packerToMemInit(&p, &mb);
     hdr_out.packInto(&p);
     hdr_out.clean();
     packerClean(&p);
     mb.append("\r\n", 2);
 
-    comm_write_mbuf(tunnelState->server.fd(), &mb, tunnelProxyConnectedWriteDone, tunnelState);
-    commSetTimeout(tunnelState->server.fd(), Config.Timeout.read, tunnelTimeout, tunnelState);
+    AsyncCall::Pointer writeCall = commCbCall(5,5, "tunnelConnectedWriteDone",
+                                   CommIoCbPtrFun(tunnelConnectedWriteDone, tunnelState));
+    Comm::Write(srv, &mb, writeCall);
+
+    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "tunnelTimeout",
+                                     CommTimeoutCbPtrFun(tunnelTimeout, tunnelState));
+    commSetConnTimeout(srv, Config.Timeout.read, timeoutCall);
 }
 
 static void
-tunnelPeerSelectComplete(FwdServer * fs, void *data)
+tunnelPeerSelectComplete(Comm::ConnectionList *peer_paths, ErrorState *err, void *data)
 {
     TunnelStateData *tunnelState = (TunnelStateData *)data;
-    HttpRequest *request = tunnelState->request;
-    peer *g = NULL;
 
-    if (fs == NULL) {
-        ErrorState *err;
-        err = errorCon(ERR_CANNOT_FORWARD, HTTP_SERVICE_UNAVAILABLE, request);
-        *tunnelState->status_ptr = HTTP_SERVICE_UNAVAILABLE;
+    if (peer_paths == NULL || peer_paths->size() < 1) {
+        debugs(26, 3, HERE << "No paths found. Aborting CONNECT");
+        if (!err) {
+            err = new ErrorState(ERR_CANNOT_FORWARD, HTTP_SERVICE_UNAVAILABLE, tunnelState->request);
+        }
+        *tunnelState->status_ptr = err->httpStatus;
         err->callback = tunnelErrorComplete;
         err->callback_data = tunnelState;
-        errorSend(tunnelState->client.fd(), err);
+        errorSend(tunnelState->client.conn, err);
         return;
     }
+    delete err;
 
-    tunnelState->servers = fs;
-    tunnelState->host = fs->_peer ? xstrdup(fs->_peer->host) : xstrdup(request->GetHost());
-
-    if (fs->_peer == NULL) {
-        tunnelState->port = request->port;
-    } else if (fs->_peer->http_port != 0) {
-        tunnelState->port = fs->_peer->http_port;
-    } else if ((g = peerFindByName(fs->_peer->host))) {
-        tunnelState->port = g->http_port;
-    } else {
-        tunnelState->port = CACHE_HTTP_PORT;
+    if (Ip::Qos::TheConfig.isAclTosActive()) {
+        tunnelState->serverDestinations[0]->tos = GetTosToServer(tunnelState->request);
     }
 
-    if (fs->_peer) {
-        tunnelState->request->peer_login = fs->_peer->login;
-        tunnelState->request->flags.proxying = (fs->_peer->options.originserver?0:1);
-    } else {
-        tunnelState->request->peer_login = NULL;
-        tunnelState->request->flags.proxying = 0;
-    }
-
-#if DELAY_POOLS
-    /* no point using the delayIsNoDelay stuff since tunnel is nice and simple */
-    if (g && g->options.no_delay)
-        tunnelState->server.setDelayId(DelayId());
-
+#if SO_MARK && USE_LIBCAP
+    tunnelState->serverDestinations[0]->nfmark = GetNfmarkToServer(tunnelState->request);
 #endif
 
-    commConnectStart(tunnelState->server.fd(),
-                     tunnelState->host,
-                     tunnelState->port,
-                     tunnelConnectDone,
-                     tunnelState);
+    debugs(26, 3, HERE << "paths=" << peer_paths->size() << ", p[0]={" << (*peer_paths)[0] << "}, serverDest[0]={" <<
+           tunnelState->serverDestinations[0] << "}");
+
+    AsyncCall::Pointer call = commCbCall(26,3, "tunnelConnectDone", CommConnectCbPtrFun(tunnelConnectDone, tunnelState));
+    Comm::ConnOpener *cs = new Comm::ConnOpener(tunnelState->serverDestinations[0], call, Config.Timeout.connect);
+    cs->setHost(tunnelState->url);
+    AsyncJob::Start(cs);
 }
 
 CBDATA_CLASS_INIT(TunnelStateData);
 
 void *
 TunnelStateData::operator new (size_t)
