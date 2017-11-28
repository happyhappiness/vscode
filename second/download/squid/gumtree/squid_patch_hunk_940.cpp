 {
     char ntoabuf[MAX_IPSTRLEN];
     /*
      * XXX These should use HttpHdr interfaces instead of Printfs
      */
     const Adaptation::ServiceConfig &s = service().cfg();
-    buf.Printf("%s " SQUIDSTRINGPH " ICAP/1.0\r\n", s.methodStr(), SQUIDSTRINGPRINT(s.uri));
-    buf.Printf("Host: " SQUIDSTRINGPH ":%d\r\n", SQUIDSTRINGPRINT(s.host), s.port);
-    buf.Printf("Date: %s\r\n", mkrfc1123(squid_curtime));
+    buf.appendf("%s " SQUIDSTRINGPH " ICAP/1.0\r\n", s.methodStr(), SQUIDSTRINGPRINT(s.uri));
+    buf.appendf("Host: " SQUIDSTRINGPH ":%d\r\n", SQUIDSTRINGPRINT(s.host), s.port);
+    buf.appendf("Date: %s\r\n", mkrfc1123(squid_curtime));
 
     if (!TheConfig.reuse_connections)
-        buf.Printf("Connection: close\r\n");
+        buf.appendf("Connection: close\r\n");
 
     const HttpRequest *request = &virginRequest();
 
     // we must forward "Proxy-Authenticate" and "Proxy-Authorization"
     // as ICAP headers.
-    if (virgin.header->header.has(HDR_PROXY_AUTHENTICATE)) {
-        String vh=virgin.header->header.getByName("Proxy-Authenticate");
-        buf.Printf("Proxy-Authenticate: " SQUIDSTRINGPH "\r\n",SQUIDSTRINGPRINT(vh));
+    if (virgin.header->header.has(Http::HdrType::PROXY_AUTHENTICATE)) {
+        String vh=virgin.header->header.getById(Http::HdrType::PROXY_AUTHENTICATE);
+        buf.appendf("Proxy-Authenticate: " SQUIDSTRINGPH "\r\n",SQUIDSTRINGPRINT(vh));
     }
 
-    if (virgin.header->header.has(HDR_PROXY_AUTHORIZATION)) {
-        String vh=virgin.header->header.getByName("Proxy-Authorization");
-        buf.Printf("Proxy-Authorization: " SQUIDSTRINGPH "\r\n", SQUIDSTRINGPRINT(vh));
+    if (virgin.header->header.has(Http::HdrType::PROXY_AUTHORIZATION)) {
+        String vh=virgin.header->header.getById(Http::HdrType::PROXY_AUTHORIZATION);
+        buf.appendf("Proxy-Authorization: " SQUIDSTRINGPH "\r\n", SQUIDSTRINGPRINT(vh));
     } else if (request->extacl_user.size() > 0 && request->extacl_passwd.size() > 0) {
-        char loginbuf[256];
-        snprintf(loginbuf, sizeof(loginbuf), SQUIDSTRINGPH ":" SQUIDSTRINGPH,
-                 SQUIDSTRINGPRINT(request->extacl_user),
-                 SQUIDSTRINGPRINT(request->extacl_passwd));
-        buf.Printf("Proxy-Authorization: Basic %s\r\n", old_base64_encode(loginbuf));
+        struct base64_encode_ctx ctx;
+        base64_encode_init(&ctx);
+        uint8_t base64buf[base64_encode_len(MAX_LOGIN_SZ)];
+        size_t resultLen = base64_encode_update(&ctx, base64buf, request->extacl_user.size(), reinterpret_cast<const uint8_t*>(request->extacl_user.rawBuf()));
+        resultLen += base64_encode_update(&ctx, base64buf+resultLen, 1, reinterpret_cast<const uint8_t*>(":"));
+        resultLen += base64_encode_update(&ctx, base64buf+resultLen, request->extacl_passwd.size(), reinterpret_cast<const uint8_t*>(request->extacl_passwd.rawBuf()));
+        resultLen += base64_encode_final(&ctx, base64buf+resultLen);
+        buf.appendf("Proxy-Authorization: Basic %.*s\r\n", (int)resultLen, base64buf);
     }
 
     // share the cross-transactional database records if needed
     if (Adaptation::Config::masterx_shared_name) {
         Adaptation::History::Pointer ah = request->adaptHistory(false);
         if (ah != NULL) {
             String name, value;
             if (ah->getXxRecord(name, value)) {
-                buf.Printf(SQUIDSTRINGPH ": " SQUIDSTRINGPH "\r\n",
-                           SQUIDSTRINGPRINT(name), SQUIDSTRINGPRINT(value));
+                buf.appendf(SQUIDSTRINGPH ": " SQUIDSTRINGPH "\r\n", SQUIDSTRINGPRINT(name), SQUIDSTRINGPRINT(value));
             }
         }
     }
 
-    buf.Printf("Encapsulated: ");
+    buf.append("Encapsulated: ", 14);
 
     MemBuf httpBuf;
 
     httpBuf.init();
 
     // build HTTP request header, if any
     ICAP::Method m = s.method;
 
     // to simplify, we could assume that request is always available
 
-    String urlPath;
     if (request) {
-        urlPath = request->urlpath;
         if (ICAP::methodRespmod == m)
             encapsulateHead(buf, "req-hdr", httpBuf, request);
         else if (ICAP::methodReqmod == m)
             encapsulateHead(buf, "req-hdr", httpBuf, virgin.header);
     }
 
     if (ICAP::methodRespmod == m)
         if (const HttpMsg *prime = virgin.header)
             encapsulateHead(buf, "res-hdr", httpBuf, prime);
 
     if (!virginBody.expected())
-        buf.Printf("null-body=%d", (int) httpBuf.contentSize());
+        buf.appendf("null-body=%d", (int) httpBuf.contentSize());
     else if (ICAP::methodReqmod == m)
-        buf.Printf("req-body=%d", (int) httpBuf.contentSize());
+        buf.appendf("req-body=%d", (int) httpBuf.contentSize());
     else
-        buf.Printf("res-body=%d", (int) httpBuf.contentSize());
+        buf.appendf("res-body=%d", (int) httpBuf.contentSize());
 
     buf.append(ICAP::crlf, 2); // terminate Encapsulated line
 
     if (preview.enabled()) {
-        buf.Printf("Preview: %d\r\n", (int)preview.ad());
+        buf.appendf("Preview: %d\r\n", (int)preview.ad());
         if (!virginBody.expected()) // there is no body to preview
             finishNullOrEmptyBodyPreview(httpBuf);
     }
 
     makeAllowHeader(buf);
 
