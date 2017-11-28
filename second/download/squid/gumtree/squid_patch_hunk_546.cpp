                       getMyHostname(), getMyPort());
 
 #endif
 
     const bool maySendChunkedReply = !request->multipartRangeRequest() &&
                                      reply->sline.protocol == AnyP::PROTO_HTTP && // response is HTTP
-                                     (request->http_ver >= HttpVersion(1, 1));
+                                     (request->http_ver >= Http::ProtocolVersion(1, 1));
 
     /* Check whether we should send keep-alive */
-    if (!Config.onoff.error_pconns && reply->sline.status >= 400 && !request->flags.mustKeepalive) {
+    if (!Config.onoff.error_pconns && reply->sline.status() >= 400 && !request->flags.mustKeepalive) {
         debugs(33, 3, "clientBuildReplyHeader: Error, don't keep-alive");
-        request->flags.proxyKeepalive = 0;
+        request->flags.proxyKeepalive = false;
     } else if (!Config.onoff.client_pconns && !request->flags.mustKeepalive) {
         debugs(33, 2, "clientBuildReplyHeader: Connection Keep-Alive not requested by admin or client");
-        request->flags.proxyKeepalive = 0;
+        request->flags.proxyKeepalive = false;
     } else if (request->flags.proxyKeepalive && shutting_down) {
         debugs(88, 3, "clientBuildReplyHeader: Shutting down, don't keep-alive.");
-        request->flags.proxyKeepalive = 0;
+        request->flags.proxyKeepalive = false;
     } else if (request->flags.connectionAuth && !reply->keep_alive) {
         debugs(33, 2, "clientBuildReplyHeader: Connection oriented auth but server side non-persistent");
-        request->flags.proxyKeepalive = 0;
+        request->flags.proxyKeepalive = false;
     } else if (reply->bodySize(request->method) < 0 && !maySendChunkedReply) {
         debugs(88, 3, "clientBuildReplyHeader: can't keep-alive, unknown body size" );
-        request->flags.proxyKeepalive = 0;
+        request->flags.proxyKeepalive = false;
     } else if (fdUsageHigh()&& !request->flags.mustKeepalive) {
         debugs(88, 3, "clientBuildReplyHeader: Not many unused FDs, can't keep-alive");
-        request->flags.proxyKeepalive = 0;
+        request->flags.proxyKeepalive = false;
     } else if (request->flags.sslBumped && !reply->persistent()) {
         // We do not really have to close, but we pretend we are a tunnel.
         debugs(88, 3, "clientBuildReplyHeader: bumped reply forces close");
-        request->flags.proxyKeepalive = 0;
+        request->flags.proxyKeepalive = false;
     } else if (request->pinnedConnection() && !reply->persistent()) {
         // The peer wants to close the pinned connection
         debugs(88, 3, "pinned reply forces close");
-        request->flags.proxyKeepalive = 0;
+        request->flags.proxyKeepalive = false;
     }
 
     // Decide if we send chunked reply
     if (maySendChunkedReply &&
             request->flags.proxyKeepalive &&
             reply->bodySize(request->method) < 0) {
         debugs(88, 3, "clientBuildReplyHeader: chunked reply");
-        request->flags.chunkedReply = 1;
+        request->flags.chunkedReply = true;
         hdr->putStr(HDR_TRANSFER_ENCODING, "chunked");
     }
 
     /* Append VIA */
     if (Config.onoff.via) {
         LOCAL_ARRAY(char, bbuf, MAX_URL + 32);
