 
     /* Nothing to do here for PASSTHRU */
     if (strcmp(request->peer_login, "PASSTHRU") == 0)
         return;
 
     /* PROXYPASS is a special case, single-signon to servers with the proxy password (basic only) */
-    if (flags.originpeer && strcmp(request->peer_login, "PROXYPASS") == 0 && hdr_in->has(HDR_PROXY_AUTHORIZATION)) {
-        const char *auth = hdr_in->getStr(HDR_PROXY_AUTHORIZATION);
+    if (flags.originpeer && strcmp(request->peer_login, "PROXYPASS") == 0 && hdr_in->has(Http::HdrType::PROXY_AUTHORIZATION)) {
+        const char *auth = hdr_in->getStr(Http::HdrType::PROXY_AUTHORIZATION);
 
         if (auth && strncasecmp(auth, "basic ", 6) == 0) {
             hdr_out->putStr(header, auth);
             return;
         }
     }
 
+    uint8_t loginbuf[base64_encode_len(MAX_LOGIN_SZ)];
+    size_t blen;
+    struct base64_encode_ctx ctx;
+    base64_encode_init(&ctx);
+
     /* Special mode to pass the username to the upstream cache */
     if (*request->peer_login == '*') {
-        char loginbuf[256];
         const char *username = "-";
 
         if (request->extacl_user.size())
             username = request->extacl_user.termedBuf();
 #if USE_AUTH
         else if (request->auth_user_request != NULL)
             username = request->auth_user_request->username();
 #endif
 
-        snprintf(loginbuf, sizeof(loginbuf), "%s%s", username, request->peer_login + 1);
-
-        httpHeaderPutStrf(hdr_out, header, "Basic %s",
-                          old_base64_encode(loginbuf));
+        blen = base64_encode_update(&ctx, loginbuf, strlen(username), reinterpret_cast<const uint8_t*>(username));
+        blen += base64_encode_update(&ctx, loginbuf+blen, strlen(request->peer_login +1), reinterpret_cast<const uint8_t*>(request->peer_login +1));
+        blen += base64_encode_final(&ctx, loginbuf+blen);
+        httpHeaderPutStrf(hdr_out, header, "Basic %.*s", (int)blen, loginbuf);
         return;
     }
 
     /* external_acl provided credentials */
     if (request->extacl_user.size() && request->extacl_passwd.size() &&
             (strcmp(request->peer_login, "PASS") == 0 ||
              strcmp(request->peer_login, "PROXYPASS") == 0)) {
-        char loginbuf[256];
-        snprintf(loginbuf, sizeof(loginbuf), SQUIDSTRINGPH ":" SQUIDSTRINGPH,
-                 SQUIDSTRINGPRINT(request->extacl_user),
-                 SQUIDSTRINGPRINT(request->extacl_passwd));
-        httpHeaderPutStrf(hdr_out, header, "Basic %s",
-                          old_base64_encode(loginbuf));
+
+        blen = base64_encode_update(&ctx, loginbuf, request->extacl_user.size(), reinterpret_cast<const uint8_t*>(request->extacl_user.rawBuf()));
+        blen += base64_encode_update(&ctx, loginbuf+blen, 1, reinterpret_cast<const uint8_t*>(":"));
+        blen += base64_encode_update(&ctx, loginbuf+blen, request->extacl_passwd.size(), reinterpret_cast<const uint8_t*>(request->extacl_passwd.rawBuf()));
+        blen += base64_encode_final(&ctx, loginbuf+blen);
+        httpHeaderPutStrf(hdr_out, header, "Basic %.*s", (int)blen, loginbuf);
         return;
     }
     // if no external user credentials are available to fake authentication with PASS acts like PASSTHRU
     if (strcmp(request->peer_login, "PASS") == 0)
         return;
 
     /* Kerberos login to peer */
 #if HAVE_AUTH_MODULE_NEGOTIATE && HAVE_KRB5 && HAVE_GSSAPI
     if (strncmp(request->peer_login, "NEGOTIATE",strlen("NEGOTIATE")) == 0) {
         char *Token=NULL;
         char *PrincipalName=NULL,*p;
+        int negotiate_flags = 0;
+
         if ((p=strchr(request->peer_login,':')) != NULL ) {
             PrincipalName=++p;
         }
-        Token = peer_proxy_negotiate_auth(PrincipalName, request->peer_host);
+        if (request->flags.auth_no_keytab) {
+            negotiate_flags |= PEER_PROXY_NEGOTIATE_NOKEYTAB;
+        }
+        Token = peer_proxy_negotiate_auth(PrincipalName, request->peer_host, negotiate_flags);
         if (Token) {
             httpHeaderPutStrf(hdr_out, header, "Negotiate %s",Token);
         }
         return;
     }
 #endif /* HAVE_KRB5 && HAVE_GSSAPI */
 
-    httpHeaderPutStrf(hdr_out, header, "Basic %s",
-                      old_base64_encode(request->peer_login));
+    blen = base64_encode_update(&ctx, loginbuf, strlen(request->peer_login), reinterpret_cast<const uint8_t*>(request->peer_login));
+    blen += base64_encode_final(&ctx, loginbuf+blen);
+    httpHeaderPutStrf(hdr_out, header, "Basic %.*s", (int)blen, loginbuf);
     return;
 }
 
 /*
  * build request headers and append them to a given MemBuf
  * used by buildRequestPrefix()
