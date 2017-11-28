     }
 
     debugs(26, 3, request->method << ' ' << url << ' ' << request->http_ver);
     ++statCounter.server.all.requests;
     ++statCounter.server.other.requests;
 
-    tunnelState = new TunnelStateData;
+    tunnelState = new TunnelStateData(http);
 #if USE_DELAY_POOLS
-    tunnelState->server.setDelayId(DelayId::DelayClient(http));
+    //server.setDelayId called from tunnelConnectDone after server side connection established
 #endif
-    tunnelState->url = xstrdup(url);
-    tunnelState->request = request;
-    tunnelState->server.size_ptr = &http->out.size;
-    tunnelState->client.size_ptr = &http->al->http.clientRequestSz.payloadData;
-    tunnelState->status_ptr = &http->al->http.code;
-    tunnelState->logTag_ptr = &http->logType;
-    tunnelState->client.conn = http->getConn()->clientConnection;
-    tunnelState->http = http;
-    tunnelState->al = http->al ;
-    tunnelState->started = squid_curtime;
-
-    comm_add_close_handler(tunnelState->client.conn->fd,
-                           tunnelClientClosed,
-                           tunnelState);
-
-    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "tunnelTimeout",
-                                     CommTimeoutCbPtrFun(tunnelTimeout, tunnelState));
-    commSetConnTimeout(tunnelState->client.conn, Config.Timeout.lifetime, timeoutCall);
 
-    peerSelect(&(tunnelState->serverDestinations), request, tunnelState->al,
+    peerSelect(&(tunnelState->serverDestinations), request, http->al,
                NULL,
                tunnelPeerSelectComplete,
                tunnelState);
 }
 
 void
 TunnelStateData::connectToPeer()
 {
-    const Comm::ConnectionPointer &srv = server.conn;
-
-#if USE_OPENSSL
-    if (CachePeer *p = srv->getPeer()) {
-        if (p->use_ssl) {
+    if (CachePeer *p = server.conn->getPeer()) {
+        if (p->secure.encryptTransport) {
             AsyncCall::Pointer callback = asyncCall(5,4,
                                                     "TunnelStateData::ConnectedToPeer",
                                                     MyAnswerDialer(&TunnelStateData::connectedToPeer, this));
-            Ssl::PeerConnector *connector =
-                new Ssl::PeerConnector(request, srv, client.conn, callback);
+            auto *connector = new Security::BlindPeerConnector(request, server.conn, callback, al);
             AsyncJob::Start(connector); // will call our callback
             return;
         }
     }
-#endif
 
-    tunnelRelayConnectRequest(srv, this);
+    Security::EncryptorAnswer nil;
+    connectedToPeer(nil);
 }
 
-#if USE_OPENSSL
-/// Ssl::PeerConnector callback
 void
-TunnelStateData::connectedToPeer(Ssl::PeerConnectorAnswer &answer)
+TunnelStateData::connectedToPeer(Security::EncryptorAnswer &answer)
 {
     if (ErrorState *error = answer.error.get()) {
         *status_ptr = error->httpStatus;
         error->callback = tunnelErrorComplete;
         error->callback_data = this;
         errorSend(client.conn, error);
         answer.error.clear(); // preserve error for errorSendComplete()
         return;
     }
 
     tunnelRelayConnectRequest(server.conn, this);
 }
-#endif
 
 static void
 tunnelRelayConnectRequest(const Comm::ConnectionPointer &srv, void *data)
 {
     TunnelStateData *tunnelState = (TunnelStateData *)data;
     assert(!tunnelState->waitingForConnectExchange());
     HttpHeader hdr_out(hoRequest);
-    Packer p;
-    HttpStateFlags flags;
+    Http::StateFlags flags;
     debugs(26, 3, HERE << srv << ", tunnelState=" << tunnelState);
     memset(&flags, '\0', sizeof(flags));
     flags.proxying = tunnelState->request->flags.proxying;
     MemBuf mb;
     mb.init();
-    mb.Printf("CONNECT %s HTTP/1.1\r\n", tunnelState->url);
+    mb.appendf("CONNECT %s HTTP/1.1\r\n", tunnelState->url);
     HttpStateData::httpBuildRequestHeader(tunnelState->request.getRaw(),
                                           NULL,         /* StoreEntry */
                                           tunnelState->al,          /* AccessLogEntry */
                                           &hdr_out,
                                           flags);           /* flags */
-    packerToMemInit(&p, &mb);
-    hdr_out.packInto(&p);
+    hdr_out.packInto(&mb);
     hdr_out.clean();
-    packerClean(&p);
     mb.append("\r\n", 2);
 
     debugs(11, 2, "Tunnel Server REQUEST: " << tunnelState->server.conn <<
            ":\n----------\n" << mb.buf << "\n----------");
 
     AsyncCall::Pointer writeCall = commCbCall(5,5, "tunnelConnectReqWriteDone",
