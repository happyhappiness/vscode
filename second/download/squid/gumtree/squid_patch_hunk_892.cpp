 
     if (keepGoingAfterRead(len, errcode, xerrno, server, client))
         handleConnectResponse(len);
 }
 
 void
-TunnelStateData::informUserOfPeerError(const char *errMsg)
+TunnelStateData::informUserOfPeerError(const char *errMsg, const size_t sz)
 {
     server.len = 0;
+
+    if (logTag_ptr)
+        *logTag_ptr = LOG_TCP_TUNNEL;
+
     if (!clientExpectsConnectResponse()) {
         // closing the connection is the best we can do here
         debugs(50, 3, server.conn << " closing on error: " << errMsg);
         server.conn->close();
         return;
     }
-    ErrorState *err  = new ErrorState(ERR_CONNECT_FAIL, Http::scBadGateway, request.getRaw());
-    err->callback = tunnelErrorComplete;
-    err->callback_data = this;
-    *status_ptr = Http::scBadGateway;
-    errorSend(http->getConn()->clientConnection, err);
+
+    // if we have no reply suitable to relay, use 502 Bad Gateway
+    if (!sz || sz > static_cast<size_t>(connectRespBuf->contentSize())) {
+        ErrorState *err = new ErrorState(ERR_CONNECT_FAIL, Http::scBadGateway, request.getRaw());
+        *status_ptr = Http::scBadGateway;
+        err->callback = tunnelErrorComplete;
+        err->callback_data = this;
+        errorSend(http->getConn()->clientConnection, err);
+        return;
+    }
+
+    // if we need to send back the server response. write its headers to the client
+    server.len = sz;
+    memcpy(server.buf, connectRespBuf->content(), server.len);
+    copy(server.len, server, client, TunnelStateData::WriteClientDone);
+    // then close the server FD to prevent any relayed keep-alive causing CVE-2015-5400
+    server.closeIfOpen();
 }
 
 /* Read from client side and queue it for writing to the server */
 void
-TunnelStateData::ReadConnectResponseDone(const Comm::ConnectionPointer &, char *buf, size_t len, comm_err_t errcode, int xerrno, void *data)
+TunnelStateData::ReadConnectResponseDone(const Comm::ConnectionPointer &, char *buf, size_t len, Comm::Flag errcode, int xerrno, void *data)
 {
     TunnelStateData *tunnelState = (TunnelStateData *)data;
     assert (cbdataReferenceValid (tunnelState));
 
     tunnelState->readConnectResponseDone(buf, len, errcode, xerrno);
 }
