     if (read_size < 2)
         return;
 
     if (flags.do_next_read) {
         flags.do_next_read = 0;
         typedef CommCbMemFunT<HttpStateData, CommIoCbParams> Dialer;
-        entry->delayAwareRead(fd, readBuf->space(read_size), read_size,
+        entry->delayAwareRead(serverConnection, readBuf->space(read_size), read_size,
                               JobCallback(11, 5, Dialer, this,  HttpStateData::readReply));
     }
 }
 
-/*
- * This will be called when request write is complete.
- */
+/// called after writing the very last request byte (body, last-chunk, etc)
 void
-HttpStateData::sendComplete(const CommIoCbParams &io)
+HttpStateData::wroteLast(const CommIoCbParams &io)
 {
-    debugs(11, 5, "httpSendComplete: FD " << fd << ": size " << io.size << ": errflag " << io.flag << ".");
+    debugs(11, 5, HERE << serverConnection << ": size " << io.size << ": errflag " << io.flag << ".");
 #if URL_CHECKSUM_DEBUG
 
     entry->mem_obj->checkUrlChecksum();
 #endif
 
     if (io.size > 0) {
-        fd_bytes(fd, io.size, FD_WRITE);
-        kb_incr(&statCounter.server.all.kbytes_out, io.size);
-        kb_incr(&statCounter.server.http.kbytes_out, io.size);
+        fd_bytes(io.fd, io.size, FD_WRITE);
+        kb_incr(&(statCounter.server.all.kbytes_out), io.size);
+        kb_incr(&(statCounter.server.http.kbytes_out), io.size);
     }
 
     if (io.flag == COMM_ERR_CLOSING)
         return;
 
     if (io.flag) {
-        ErrorState *err;
-        err = errorCon(ERR_WRITE_ERROR, HTTP_BAD_GATEWAY, fwd->request);
+        ErrorState *err = new ErrorState(ERR_WRITE_ERROR, HTTP_BAD_GATEWAY, fwd->request);
         err->xerrno = io.xerrno;
         fwd->fail(err);
-        comm_close(fd);
+        serverConnection->close();
         return;
     }
 
+    sendComplete();
+}
+
+/// successfully wrote the entire request (including body, last-chunk, etc.)
+void
+HttpStateData::sendComplete()
+{
     /*
      * Set the read timeout here because it hasn't been set yet.
      * We only set the read timeout after the request has been
      * fully written to the server-side.  If we start the timeout
      * after connection establishment, then we are likely to hit
      * the timeout for POST/PUT requests that have very large
      * request bodies.
      */
     typedef CommCbMemFunT<HttpStateData, CommTimeoutCbParams> TimeoutDialer;
     AsyncCall::Pointer timeoutCall =  JobCallback(11, 5,
                                       TimeoutDialer, this, HttpStateData::httpTimeout);
 
-    commSetTimeout(fd, Config.Timeout.read, timeoutCall);
+    commSetConnTimeout(serverConnection, Config.Timeout.read, timeoutCall);
 
     flags.request_sent = 1;
 
-    orig_request->hier.peer_http_request_sent = current_time;
+    request->hier.peer_http_request_sent = current_time;
 }
 
 // Close the HTTP server connection. Used by serverComplete().
 void
 HttpStateData::closeServer()
 {
-    debugs(11,5, HERE << "closing HTTP server FD " << fd << " this " << this);
+    debugs(11,5, HERE << "closing HTTP server " << serverConnection << " this " << this);
 
-    if (fd >= 0) {
-        fwd->unregister(fd);
-        comm_remove_close_handler(fd, closeHandler);
+    if (Comm::IsConnOpen(serverConnection)) {
+        fwd->unregister(serverConnection);
+        comm_remove_close_handler(serverConnection->fd, closeHandler);
         closeHandler = NULL;
-        comm_close(fd);
-        fd = -1;
+        serverConnection->close();
     }
 }
 
 bool
 HttpStateData::doneWithServer() const
 {
-    return fd < 0;
+    return !Comm::IsConnOpen(serverConnection);
+}
+
+/*
+ * Fixup authentication request headers for special cases
+ */
+static void
+httpFixupAuthentication(HttpRequest * request, const HttpHeader * hdr_in, HttpHeader * hdr_out, http_state_flags flags)
+{
+    http_hdr_type header = flags.originpeer ? HDR_AUTHORIZATION : HDR_PROXY_AUTHORIZATION;
+
+    /* Nothing to do unless we are forwarding to a peer */
+    if (!request->flags.proxying)
+        return;
+
+    /* Needs to be explicitly enabled */
+    if (!request->peer_login)
+        return;
+
+    /* Maybe already dealt with? */
+    if (hdr_out->has(header))
+        return;
+
+    /* Nothing to do here for PASSTHRU */
+    if (strcmp(request->peer_login, "PASSTHRU") == 0)
+        return;
+
+    /* PROXYPASS is a special case, single-signon to servers with the proxy password (basic only) */
+    if (flags.originpeer && strcmp(request->peer_login, "PROXYPASS") == 0 && hdr_in->has(HDR_PROXY_AUTHORIZATION)) {
+        const char *auth = hdr_in->getStr(HDR_PROXY_AUTHORIZATION);
+
+        if (auth && strncasecmp(auth, "basic ", 6) == 0) {
+            hdr_out->putStr(header, auth);
+            return;
+        }
+    }
+
+    /* Special mode to pass the username to the upstream cache */
+    if (*request->peer_login == '*') {
+        char loginbuf[256];
+        const char *username = "-";
+
+        if (request->extacl_user.size())
+            username = request->extacl_user.termedBuf();
+#if USE_AUTH
+        else if (request->auth_user_request != NULL)
+            username = request->auth_user_request->username();
+#endif
+
+        snprintf(loginbuf, sizeof(loginbuf), "%s%s", username, request->peer_login + 1);
+
+        httpHeaderPutStrf(hdr_out, header, "Basic %s",
+                          old_base64_encode(loginbuf));
+        return;
+    }
+
+    /* external_acl provided credentials */
+    if (request->extacl_user.size() && request->extacl_passwd.size() &&
+            (strcmp(request->peer_login, "PASS") == 0 ||
+             strcmp(request->peer_login, "PROXYPASS") == 0)) {
+        char loginbuf[256];
+        snprintf(loginbuf, sizeof(loginbuf), SQUIDSTRINGPH ":" SQUIDSTRINGPH,
+                 SQUIDSTRINGPRINT(request->extacl_user),
+                 SQUIDSTRINGPRINT(request->extacl_passwd));
+        httpHeaderPutStrf(hdr_out, header, "Basic %s",
+                          old_base64_encode(loginbuf));
+        return;
+    }
+    // if no external user credentials are available to fake authentication with PASS acts like PASSTHRU
+    if (strcmp(request->peer_login, "PASS") == 0)
+        return;
+
+    /* Kerberos login to peer */
+#if HAVE_AUTH_MODULE_NEGOTIATE && HAVE_KRB5 && HAVE_GSSAPI
+    if (strncmp(request->peer_login, "NEGOTIATE",strlen("NEGOTIATE")) == 0) {
+        char *Token=NULL;
+        char *PrincipalName=NULL,*p;
+        if ((p=strchr(request->peer_login,':')) != NULL ) {
+            PrincipalName=++p;
+        }
+        Token = peer_proxy_negotiate_auth(PrincipalName, request->peer_host);
+        if (Token) {
+            httpHeaderPutStrf(hdr_out, header, "Negotiate %s",Token);
+        }
+        return;
+    }
+#endif /* HAVE_KRB5 && HAVE_GSSAPI */
+
+    httpHeaderPutStrf(hdr_out, header, "Basic %s",
+                      old_base64_encode(request->peer_login));
+    return;
 }
 
 /*
  * build request headers and append them to a given MemBuf
  * used by buildRequestPrefix()
  * note: initialised the HttpHeader, the caller is responsible for Clean()-ing
  */
 void
 HttpStateData::httpBuildRequestHeader(HttpRequest * request,
-                                      HttpRequest * orig_request,
                                       StoreEntry * entry,
+                                      const AccessLogEntryPointer &al,
                                       HttpHeader * hdr_out,
                                       const http_state_flags flags)
 {
     /* building buffer for complex strings */
 #define BBUF_SZ (MAX_URL+32)
     LOCAL_ARRAY(char, bbuf, BBUF_SZ);
     LOCAL_ARRAY(char, ntoabuf, MAX_IPSTRLEN);
-    const HttpHeader *hdr_in = &orig_request->header;
+    const HttpHeader *hdr_in = &request->header;
     const HttpHeaderEntry *e = NULL;
     HttpHeaderPos pos = HttpHeaderInitPos;
     assert (hdr_out->owner == hoRequest);
 
     /* append our IMS header */
     if (request->lastmod > -1)
         hdr_out->putTime(HDR_IF_MODIFIED_SINCE, request->lastmod);
 
-    bool we_do_ranges = decideIfWeDoRanges (orig_request);
+    bool we_do_ranges = decideIfWeDoRanges (request);
 
     String strConnection (hdr_in->getList(HDR_CONNECTION));
 
     while ((e = hdr_in->getEntry(&pos)))
-        copyOneHeaderFromClientsideRequestToUpstreamRequest(e, strConnection, request, orig_request, hdr_out, we_do_ranges, flags);
+        copyOneHeaderFromClientsideRequestToUpstreamRequest(e, strConnection, request, hdr_out, we_do_ranges, flags);
 
     /* Abstraction break: We should interpret multipart/byterange responses
      * into offset-length data, and this works around our inability to do so.
      */
-    if (!we_do_ranges && orig_request->multipartRangeRequest()) {
+    if (!we_do_ranges && request->multipartRangeRequest()) {
         /* don't cache the result */
-        orig_request->flags.cachable = 0;
+        request->flags.cachable = 0;
         /* pretend it's not a range request */
-        delete orig_request->range;
-        orig_request->range = NULL;
-        orig_request->flags.range = 0;
+        delete request->range;
+        request->range = NULL;
+        request->flags.range = 0;
     }
 
     /* append Via */
     if (Config.onoff.via) {
         String strVia;
         strVia = hdr_in->getList(HDR_VIA);
         snprintf(bbuf, BBUF_SZ, "%d.%d %s",
-                 orig_request->http_ver.major,
-                 orig_request->http_ver.minor, ThisCache);
+                 request->http_ver.major,
+                 request->http_ver.minor, ThisCache);
         strListAdd(&strVia, bbuf, ',');
         hdr_out->putStr(HDR_VIA, strVia.termedBuf());
         strVia.clean();
     }
 
-#if USE_SQUID_ESI
-    if (orig_request->flags.accelerated) {
+    if (request->flags.accelerated) {
         /* Append Surrogate-Capabilities */
-        String strSurrogate (hdr_in->getList(HDR_SURROGATE_CAPABILITY));
-        snprintf(bbuf, BBUF_SZ, "%s=\"Surrogate/1.0 ESI/1.0\"",
-                 Config.Accel.surrogate_id);
+        String strSurrogate(hdr_in->getList(HDR_SURROGATE_CAPABILITY));
+#if USE_SQUID_ESI
+        snprintf(bbuf, BBUF_SZ, "%s=\"Surrogate/1.0 ESI/1.0\"", Config.Accel.surrogate_id);
+#else
+        snprintf(bbuf, BBUF_SZ, "%s=\"Surrogate/1.0\"", Config.Accel.surrogate_id);
+#endif
         strListAdd(&strSurrogate, bbuf, ',');
         hdr_out->putStr(HDR_SURROGATE_CAPABILITY, strSurrogate.termedBuf());
     }
-#endif
 
     /** \pre Handle X-Forwarded-For */
     if (strcmp(opt_forwarded_for, "delete") != 0) {
 
         String strFwd = hdr_in->getList(HDR_X_FORWARDED_FOR);
 
