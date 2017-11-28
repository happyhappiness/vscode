     }
 
     return false;
 }
 #endif // USE_OPENSSL
 
-static void
+/**
+ * Check on_unsupported_protocol checklist and return true if tunnel mode selected
+ * or false otherwise
+ */
+bool
+clientTunnelOnError(ConnStateData *conn, Http::StreamPointer &context, HttpRequest::Pointer &request, const HttpRequestMethod& method, err_type requestError)
+{
+    if (conn->mayTunnelUnsupportedProto()) {
+        ACLFilledChecklist checklist(Config.accessList.on_unsupported_protocol, request.getRaw(), nullptr);
+        checklist.requestErrorType = requestError;
+        checklist.src_addr = conn->clientConnection->remote;
+        checklist.my_addr = conn->clientConnection->local;
+        checklist.conn(conn);
+        allow_t answer = checklist.fastCheck();
+        if (answer == ACCESS_ALLOWED && answer.kind == 1) {
+            debugs(33, 3, "Request will be tunneled to server");
+            if (context) {
+                assert(conn->pipeline.front() == context); // XXX: still assumes HTTP/1 semantics
+                context->finished(); // Will remove from conn->pipeline queue
+            }
+            Comm::SetSelect(conn->clientConnection->fd, COMM_SELECT_READ, NULL, NULL, 0);
+            return conn->initiateTunneledRequest(request, Http::METHOD_NONE, "unknown-protocol", conn->preservedClientData);
+        } else {
+            debugs(33, 3, "Continue with returning the error: " << requestError);
+        }
+    }
+
+    return false;
+}
+
+void
 clientProcessRequestFinished(ConnStateData *conn, const HttpRequest::Pointer &request)
 {
     /*
      * DPW 2007-05-18
      * Moved the TCP_RESET feature from clientReplyContext::sendMoreData
      * to here because calling comm_reset_close() causes http to
-     * be freed and the above connNoteUseOfBuffer() would hit an
-     * assertion, not to mention that we were accessing freed memory.
+     * be freed before accessing.
      */
     if (request != NULL && request->flags.resetTcp && Comm::IsConnOpen(conn->clientConnection)) {
         debugs(33, 3, HERE << "Sending TCP RST on " << conn->clientConnection);
         conn->flags.readMore = false;
         comm_reset_close(conn->clientConnection);
     }
 }
 
 void
-clientProcessRequest(ConnStateData *conn, HttpParser *hp, ClientSocketContext *context, const HttpRequestMethod& method, Http::ProtocolVersion http_ver)
+clientProcessRequest(ConnStateData *conn, const Http1::RequestParserPointer &hp, Http::Stream *context)
 {
     ClientHttpRequest *http = context->http;
-    HttpRequest::Pointer request;
-    bool notedUseOfBuffer = false;
     bool chunked = false;
     bool mustReplyToOptions = false;
     bool unsupportedTe = false;
     bool expectBody = false;
 
+    // We already have the request parsed and checked, so we
+    // only need to go through the final body/conn setup to doCallouts().
+    assert(http->request);
+    HttpRequest::Pointer request = http->request;
+
     // temporary hack to avoid splitting this huge function with sensitive code
     const bool isFtp = !hp;
-    if (isFtp) {
-        // In FTP, case, we already have the request parsed and checked, so we
-        // only need to go through the final body/conn setup to doCallouts().
-        assert(http->request);
-        request = http->request;
-        notedUseOfBuffer = true;
-    } else {
-
-        if (context->flags.parsed_ok == 0) {
-            clientStreamNode *node = context->getClientReplyContext();
-            debugs(33, 2, "clientProcessRequest: Invalid Request");
-            conn->quitAfterError(NULL);
-            // setLogUri should called before repContext->setReplyToError
-            setLogUri(http, http->uri,  true);
-            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
-            assert (repContext);
-            switch (hp->request_parse_status) {
-            case Http::scHeaderTooLarge:
-                repContext->setReplyToError(ERR_TOO_BIG, Http::scBadRequest, method, http->uri, conn->clientConnection->remote, NULL, conn->in.buf.c_str(), NULL);
-                break;
-            case Http::scMethodNotAllowed:
-                repContext->setReplyToError(ERR_UNSUP_REQ, Http::scMethodNotAllowed, method, http->uri,
-                                            conn->clientConnection->remote, NULL, conn->in.buf.c_str(), NULL);
-                break;
-            default:
-                repContext->setReplyToError(ERR_INVALID_REQ, hp->request_parse_status, method, http->uri,
-                                            conn->clientConnection->remote, NULL, conn->in.buf.c_str(), NULL);
-            }
-            assert(context->http->out.offset == 0);
-            context->pullData();
-            connNoteUseOfBuffer(conn, http->req_sz);
-            return;
-        }
-
-        if ((request = HttpRequest::CreateFromUrlAndMethod(http->uri, method)) == NULL) {
-            clientStreamNode *node = context->getClientReplyContext();
-            debugs(33, 5, "Invalid URL: " << http->uri);
-            conn->quitAfterError(request.getRaw());
-            // setLogUri should called before repContext->setReplyToError
-            setLogUri(http, http->uri,  true);
-            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
-            assert (repContext);
-            repContext->setReplyToError(ERR_INVALID_URL, Http::scBadRequest, method, http->uri, conn->clientConnection->remote, NULL, NULL, NULL);
-            assert(context->http->out.offset == 0);
-            context->pullData();
-            connNoteUseOfBuffer(conn, http->req_sz);
-            return;
-        }
-
-        /* RFC 2616 section 10.5.6 : handle unsupported HTTP major versions cleanly. */
-        /* We currently only support 0.9, 1.0, 1.1 properly */
-        /* TODO: move HTTP-specific processing into servers/HttpServer and such */
-        if ( (http_ver.major == 0 && http_ver.minor != 9) ||
-                (http_ver.major > 1) ) {
-
-            clientStreamNode *node = context->getClientReplyContext();
-            debugs(33, 5, "Unsupported HTTP version discovered. :\n" << HttpParserHdrBuf(hp));
-            conn->quitAfterError(request.getRaw());
-            // setLogUri should called before repContext->setReplyToError
-            setLogUri(http, http->uri,  true);
-            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
-            assert (repContext);
-            repContext->setReplyToError(ERR_UNSUP_HTTPVERSION, Http::scHttpVersionNotSupported, method, http->uri,
-                                        conn->clientConnection->remote, NULL, HttpParserHdrBuf(hp), NULL);
-            assert(context->http->out.offset == 0);
-            context->pullData();
-            connNoteUseOfBuffer(conn, http->req_sz);
-            clientProcessRequestFinished(conn, request);
-            return;
-        }
-
-        /* compile headers */
-        /* we should skip request line! */
-        /* XXX should actually know the damned buffer size here */
-        if (http_ver.major >= 1 && !request->parseHeader(HttpParserHdrBuf(hp), HttpParserHdrSz(hp))) {
-            clientStreamNode *node = context->getClientReplyContext();
-            debugs(33, 5, "Failed to parse request headers:\n" << HttpParserHdrBuf(hp));
-            conn->quitAfterError(request.getRaw());
-            // setLogUri should called before repContext->setReplyToError
-            setLogUri(http, http->uri,  true);
-            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
-            assert (repContext);
-            repContext->setReplyToError(ERR_INVALID_REQ, Http::scBadRequest, method, http->uri, conn->clientConnection->remote, NULL, NULL, NULL);
-            assert(context->http->out.offset == 0);
-            context->pullData();
-            connNoteUseOfBuffer(conn, http->req_sz);
-            clientProcessRequestFinished(conn, request);
-            return;
-        }
-
-        // when absolute-URI is provided Host header should be ignored. However
-        // some code still uses Host directly so normalize it.
-        // For now preserve the case where Host is completely absent. That matters.
-        if (request->header.has(HDR_HOST)) {
-            const char *host = request->header.getStr(HDR_HOST);
-            SBuf authority(request->GetHost());
-            if (request->port != urlDefaultPort(request->url.getScheme()))
-                authority.appendf(":%d", request->port);
-            debugs(33, 5, "URL domain " << authority << " overrides header Host: " << host);
-            // URL authority overrides Host header
-            request->header.delById(HDR_HOST);
-            request->header.putStr(HDR_HOST, authority.c_str());
-        }
-    }
 
     // Some blobs below are still HTTP-specific, but we would have to rewrite
     // this entire function to remove them from the FTP code path. Connection
     // setup and body_pipe preparation blobs are needed for FTP.
 
     request->clientConnectionManager = conn;
