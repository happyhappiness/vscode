     hp->hdr_start = hp->req.end + 1;
 
     /* Enforce max_request_size */
     if (req_sz >= Config.maxRequestHeaderSize) {
         debugs(33, 5, "parseHttpRequest: Too large request");
         hp->request_parse_status = Http::scHeaderTooLarge;
-        return parseHttpRequestAbort(csd, "error:request-too-large");
+        return csd->abortRequestParsing("error:request-too-large");
     }
 
     /* Set method_p */
     *method_p = HttpRequestMethod(&hp->buf[hp->req.m_start], &hp->buf[hp->req.m_end]+1);
 
     /* deny CONNECT via accelerated ports */
-    if (*method_p == Http::METHOD_CONNECT && csd->port && csd->port->flags.accelSurrogate) {
-        debugs(33, DBG_IMPORTANT, "WARNING: CONNECT method received on " << csd->port->protocol << " Accelerator port " << csd->port->s.port() );
+    if (*method_p == Http::METHOD_CONNECT && csd->port != NULL && csd->port->flags.accelSurrogate) {
+        debugs(33, DBG_IMPORTANT, "WARNING: CONNECT method received on " << csd->port->transport.protocol << " Accelerator port " << csd->port->s.port());
         /* XXX need a way to say "this many character length string" */
         debugs(33, DBG_IMPORTANT, "WARNING: for request: " << hp->buf);
         hp->request_parse_status = Http::scMethodNotAllowed;
-        return parseHttpRequestAbort(csd, "error:method-not-allowed");
+        return csd->abortRequestParsing("error:method-not-allowed");
+    }
+
+    /* RFC 7540 section 11.6 registers the method PRI as HTTP/2 specific
+     * Deny "PRI" method if used in HTTP/1.x or 0.9 versions.
+     * If seen it signals a broken client or proxy has corrupted the traffic.
+     */
+    if (*method_p == Http::METHOD_PRI && *http_ver < Http::ProtocolVersion(2,0)) {
+        debugs(33, DBG_IMPORTANT, "WARNING: PRI method received on " << csd->port->transport.protocol << "port " << csd->port->s.port());
+        debugs(33, DBG_IMPORTANT, "WARNING: for request: " << hp->buf);
+        hp->request_parse_status = Http::scMethodNotAllowed;
+        return csd->abortRequestParsing("error:method-not-allowed");
     }
 
     if (*method_p == Http::METHOD_NONE) {
         /* XXX need a way to say "this many character length string" */
         debugs(33, DBG_IMPORTANT, "clientParseRequestMethod: Unsupported method in request '" << hp->buf << "'");
         hp->request_parse_status = Http::scMethodNotAllowed;
-        return parseHttpRequestAbort(csd, "error:unsupported-request-method");
+        return csd->abortRequestParsing("error:unsupported-request-method");
     }
 
     /*
      * Process headers after request line
      * TODO: Use httpRequestParse here.
      */
