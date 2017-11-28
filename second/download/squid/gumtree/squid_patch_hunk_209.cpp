         flags.originpeer = 0;
     }
 
     /*
      * Is keep-alive okay for all request methods?
      */
-    if (orig_request->flags.must_keepalive)
+    if (request->flags.must_keepalive)
         flags.keepalive = 1;
     else if (!Config.onoff.server_pconns)
         flags.keepalive = 0;
     else if (_peer == NULL)
         flags.keepalive = 1;
     else if (_peer->stats.n_keepalives_sent < 10)
         flags.keepalive = 1;
     else if ((double) _peer->stats.n_keepalives_recv /
              (double) _peer->stats.n_keepalives_sent > 0.50)
         flags.keepalive = 1;
 
     if (_peer) {
+        /*The old code here was
+          if (neighborType(_peer, request) == PEER_SIBLING && ...
+          which is equivalent to:
+          if (neighborType(_peer, NULL) == PEER_SIBLING && ...
+          or better:
+          if (((_peer->type == PEER_MULTICAST && p->options.mcast_siblings) ||
+                 _peer->type == PEER_SIBLINGS ) && _peer->options.allow_miss)
+               flags.only_if_cached = 1;
+
+           But I suppose it was a bug
+         */
         if (neighborType(_peer, request) == PEER_SIBLING &&
                 !_peer->options.allow_miss)
             flags.only_if_cached = 1;
 
         flags.front_end_https = _peer->front_end_https;
     }
 
     mb.init();
-    buildRequestPrefix(request, orig_request, entry, &mb);
-    debugs(11, 6, "httpSendRequest: FD " << fd << ":\n" << mb.buf);
-    comm_write_mbuf(fd, &mb, requestSender);
+    request->peer_host=_peer?_peer->host:NULL;
+    buildRequestPrefix(&mb);
+
+    debugs(11, 2, "HTTP Server " << serverConnection);
+    debugs(11, 2, "HTTP Server REQUEST:\n---------\n" << mb.buf << "\n----------");
+
+    Comm::Write(serverConnection, &mb, requestSender);
+    return true;
+}
+
+bool
+HttpStateData::getMoreRequestBody(MemBuf &buf)
+{
+    // parent's implementation can handle the no-encoding case
+    if (!flags.chunked_request)
+        return ServerStateData::getMoreRequestBody(buf);
+
+    MemBuf raw;
+
+    Must(requestBodySource != NULL);
+    if (!requestBodySource->getMoreData(raw))
+        return false; // no request body bytes to chunk yet
+
+    // optimization: pre-allocate buffer size that should be enough
+    const mb_size_t rawDataSize = raw.contentSize();
+    // we may need to send: hex-chunk-size CRLF raw-data CRLF last-chunk
+    buf.init(16 + 2 + rawDataSize + 2 + 5, raw.max_capacity);
+
+    buf.Printf("%x\r\n", static_cast<unsigned int>(rawDataSize));
+    buf.append(raw.content(), rawDataSize);
+    buf.Printf("\r\n");
+
+    Must(rawDataSize > 0); // we did not accidently created last-chunk above
+
+    // Do not send last-chunk unless we successfully received everything
+    if (receivedWholeRequestBody) {
+        Must(!flags.sentLastChunk);
+        flags.sentLastChunk = true;
+        buf.append("0\r\n\r\n", 5);
+    }
 
     return true;
 }
 
 void
 httpStart(FwdState *fwd)
 {
     debugs(11, 3, "httpStart: \"" << RequestMethodStr(fwd->request->method) << " " << fwd->entry->url() << "\"" );
-    HttpStateData *httpState = new HttpStateData(fwd);
+    AsyncJob::Start(new HttpStateData(fwd));
+}
 
-    if (!httpState->sendRequest()) {
+void
+HttpStateData::start()
+{
+    if (!sendRequest()) {
         debugs(11, 3, "httpStart: aborted");
-        delete httpState;
+        mustStop("HttpStateData::start failed");
         return;
     }
 
-    statCounter.server.all.requests++;
-    statCounter.server.http.requests++;
+    ++ statCounter.server.all.requests;
+    ++ statCounter.server.http.requests;
 
     /*
      * We used to set the read timeout here, but not any more.
      * Now its set in httpSendComplete() after the full request,
      * including request body, has been written to the server.
      */
 }
 
-void
-HttpStateData::doneSendingRequestBody()
+/// if broken posts are enabled for the request, try to fix and return true
+bool
+HttpStateData::finishingBrokenPost()
 {
-    debugs(11,5, HERE << "doneSendingRequestBody: FD " << fd);
+#if USE_HTTP_VIOLATIONS
+    if (!Config.accessList.brokenPosts) {
+        debugs(11, 5, HERE << "No brokenPosts list");
+        return false;
+    }
 
-#if HTTP_VIOLATIONS
-    if (Config.accessList.brokenPosts) {
-        ACLFilledChecklist ch(Config.accessList.brokenPosts, originalRequest(), NULL);
-        if (!ch.fastCheck()) {
-            debugs(11, 5, "doneSendingRequestBody: didn't match brokenPosts");
-            CommIoCbParams io(NULL);
-            io.fd=fd;
-            io.flag=COMM_OK;
-            sendComplete(io);
-        } else {
-            debugs(11, 2, "doneSendingRequestBody: matched brokenPosts");
+    ACLFilledChecklist ch(Config.accessList.brokenPosts, originalRequest(), NULL);
+    if (!ch.fastCheck()) {
+        debugs(11, 5, HERE << "didn't match brokenPosts");
+        return false;
+    }
 
-            if (!canSend(fd)) {
-                debugs(11,2, HERE << "cannot send CRLF to closing FD " << fd);
-                assert(closeHandler != NULL);
-                return;
-            }
+    if (!Comm::IsConnOpen(serverConnection)) {
+        debugs(11, 3, HERE << "ignoring broken POST for closed " << serverConnection);
+        assert(closeHandler != NULL);
+        return true; // prevent caller from proceeding as if nothing happened
+    }
 
-            typedef CommCbMemFunT<HttpStateData, CommIoCbParams> Dialer;
-            AsyncCall::Pointer call = JobCallback(11,5,
-                                                  Dialer, this, HttpStateData::sendComplete);
-            comm_write(fd, "\r\n", 2, call);
-        }
-        return;
+    debugs(11, 3, "finishingBrokenPost: fixing broken POST");
+    typedef CommCbMemFunT<HttpStateData, CommIoCbParams> Dialer;
+    requestSender = JobCallback(11,5,
+                                Dialer, this, HttpStateData::wroteLast);
+    Comm::Write(serverConnection, "\r\n", 2, requestSender, NULL);
+    return true;
+#else
+    return false;
+#endif /* USE_HTTP_VIOLATIONS */
+}
+
+/// if needed, write last-chunk to end the request body and return true
+bool
+HttpStateData::finishingChunkedRequest()
+{
+    if (flags.sentLastChunk) {
+        debugs(11, 5, HERE << "already sent last-chunk");
+        return false;
     }
-    debugs(11, 5, "doneSendingRequestBody: No brokenPosts list");
-#endif /* HTTP_VIOLATIONS */
 
-    CommIoCbParams io(NULL);
-    io.fd=fd;
-    io.flag=COMM_OK;
-    sendComplete(io);
+    Must(receivedWholeRequestBody); // or we should not be sending last-chunk
+    flags.sentLastChunk = true;
+
+    typedef CommCbMemFunT<HttpStateData, CommIoCbParams> Dialer;
+    requestSender = JobCallback(11,5, Dialer, this, HttpStateData::wroteLast);
+    Comm::Write(serverConnection, "0\r\n\r\n", 5, requestSender, NULL);
+    return true;
+}
+
+void
+HttpStateData::doneSendingRequestBody()
+{
+    ServerStateData::doneSendingRequestBody();
+    debugs(11,5, HERE << serverConnection);
+
+    // do we need to write something after the last body byte?
+    if (flags.chunked_request && finishingChunkedRequest())
+        return;
+    if (!flags.chunked_request && finishingBrokenPost())
+        return;
+
+    sendComplete();
 }
 
 // more origin request body data is available
 void
 HttpStateData::handleMoreRequestBodyAvailable()
 {
-    if (eof || fd < 0) {
+    if (eof || !Comm::IsConnOpen(serverConnection)) {
         // XXX: we should check this condition in other callbacks then!
         // TODO: Check whether this can actually happen: We should unsubscribe
         // as a body consumer when the above condition(s) are detected.
         debugs(11, 1, HERE << "Transaction aborted while reading HTTP body");
         return;
     }
