             // If we do nothing, String will assert on overflow soon.
             // TODO: Terminate all transactions with huge XFF?
             strFwd = "error";
 
             static int warnedCount = 0;
             if (warnedCount++ < 100) {
-                const char *url = entry ? entry->url() : urlCanonical(orig_request);
+                const char *url = entry ? entry->url() : urlCanonical(request);
                 debugs(11, 1, "Warning: likely forwarding loop with " << url);
             }
         }
 
         if (strcmp(opt_forwarded_for, "on") == 0) {
             /** If set to ON - append client IP or 'unknown'. */
-            if ( orig_request->client_addr.IsNoAddr() )
+            if ( request->client_addr.IsNoAddr() )
                 strListAdd(&strFwd, "unknown", ',');
             else
-                strListAdd(&strFwd, orig_request->client_addr.NtoA(ntoabuf, MAX_IPSTRLEN), ',');
+                strListAdd(&strFwd, request->client_addr.NtoA(ntoabuf, MAX_IPSTRLEN), ',');
         } else if (strcmp(opt_forwarded_for, "off") == 0) {
             /** If set to OFF - append 'unknown'. */
             strListAdd(&strFwd, "unknown", ',');
         } else if (strcmp(opt_forwarded_for, "transparent") == 0) {
             /** If set to TRANSPARENT - pass through unchanged. */
         } else if (strcmp(opt_forwarded_for, "truncate") == 0) {
             /** If set to TRUNCATE - drop existing list and replace with client IP or 'unknown'. */
-            if ( orig_request->client_addr.IsNoAddr() )
+            if ( request->client_addr.IsNoAddr() )
                 strFwd = "unknown";
             else
-                strFwd = orig_request->client_addr.NtoA(ntoabuf, MAX_IPSTRLEN);
+                strFwd = request->client_addr.NtoA(ntoabuf, MAX_IPSTRLEN);
         }
         if (strFwd.size() > 0)
             hdr_out->putStr(HDR_X_FORWARDED_FOR, strFwd.termedBuf());
     }
     /** If set to DELETE - do not copy through. */
 
     /* append Host if not there already */
     if (!hdr_out->has(HDR_HOST)) {
-        if (orig_request->peer_domain) {
-            hdr_out->putStr(HDR_HOST, orig_request->peer_domain);
-        } else if (orig_request->port == urlDefaultPort(orig_request->protocol)) {
+        if (request->peer_domain) {
+            hdr_out->putStr(HDR_HOST, request->peer_domain);
+        } else if (request->port == urlDefaultPort(request->protocol)) {
             /* use port# only if not default */
-            hdr_out->putStr(HDR_HOST, orig_request->GetHost());
+            hdr_out->putStr(HDR_HOST, request->GetHost());
         } else {
             httpHeaderPutStrf(hdr_out, HDR_HOST, "%s:%d",
-                              orig_request->GetHost(),
-                              (int) orig_request->port);
+                              request->GetHost(),
+                              (int) request->port);
         }
     }
 
     /* append Authorization if known in URL, not in header and going direct */
     if (!hdr_out->has(HDR_AUTHORIZATION)) {
-        if (!request->flags.proxying && *request->login) {
+        if (!request->flags.proxying && request->login && *request->login) {
             httpHeaderPutStrf(hdr_out, HDR_AUTHORIZATION, "Basic %s",
-                              base64_encode(request->login));
+                              old_base64_encode(request->login));
         }
     }
 
-    /* append Proxy-Authorization if configured for peer, and proxying */
-    if (request->flags.proxying && orig_request->peer_login &&
-            !hdr_out->has(HDR_PROXY_AUTHORIZATION)) {
-        if (*orig_request->peer_login == '*') {
-            /* Special mode, to pass the username to the upstream cache */
-            char loginbuf[256];
-            const char *username = "-";
-
-            if (orig_request->extacl_user.size())
-                username = orig_request->extacl_user.termedBuf();
-            else if (orig_request->auth_user_request)
-                username = orig_request->auth_user_request->username();
-
-            snprintf(loginbuf, sizeof(loginbuf), "%s%s", username, orig_request->peer_login + 1);
-
-            httpHeaderPutStrf(hdr_out, HDR_PROXY_AUTHORIZATION, "Basic %s",
-                              base64_encode(loginbuf));
-        } else if (strcmp(orig_request->peer_login, "PASS") == 0) {
-            if (orig_request->extacl_user.size() && orig_request->extacl_passwd.size()) {
-                char loginbuf[256];
-                snprintf(loginbuf, sizeof(loginbuf), SQUIDSTRINGPH ":" SQUIDSTRINGPH,
-                         SQUIDSTRINGPRINT(orig_request->extacl_user),
-                         SQUIDSTRINGPRINT(orig_request->extacl_passwd));
-                httpHeaderPutStrf(hdr_out, HDR_PROXY_AUTHORIZATION, "Basic %s",
-                                  base64_encode(loginbuf));
-            }
-        } else if (strcmp(orig_request->peer_login, "PROXYPASS") == 0) {
-            /* Nothing to do */
-        } else {
-            httpHeaderPutStrf(hdr_out, HDR_PROXY_AUTHORIZATION, "Basic %s",
-                              base64_encode(orig_request->peer_login));
-        }
-    }
-
-    /* append WWW-Authorization if configured for peer */
-    if (flags.originpeer && orig_request->peer_login &&
-            !hdr_out->has(HDR_AUTHORIZATION)) {
-        if (strcmp(orig_request->peer_login, "PASS") == 0) {
-            /* No credentials to forward.. (should have been done above if available) */
-        } else if (strcmp(orig_request->peer_login, "PROXYPASS") == 0) {
-            /* Special mode, convert proxy authentication to WWW authentication
-            * (also applies to authentication provided by external acl)
-             */
-            const char *auth = hdr_in->getStr(HDR_PROXY_AUTHORIZATION);
-
-            if (auth && strncasecmp(auth, "basic ", 6) == 0) {
-                hdr_out->putStr(HDR_AUTHORIZATION, auth);
-            } else if (orig_request->extacl_user.size() && orig_request->extacl_passwd.size()) {
-                char loginbuf[256];
-                snprintf(loginbuf, sizeof(loginbuf), SQUIDSTRINGPH ":" SQUIDSTRINGPH,
-                         SQUIDSTRINGPRINT(orig_request->extacl_user),
-                         SQUIDSTRINGPRINT(orig_request->extacl_passwd));
-                httpHeaderPutStrf(hdr_out, HDR_AUTHORIZATION, "Basic %s",
-                                  base64_encode(loginbuf));
-            }
-        } else if (*orig_request->peer_login == '*') {
-            /* Special mode, to pass the username to the upstream cache */
-            char loginbuf[256];
-            const char *username = "-";
-
-            if (orig_request->auth_user_request)
-                username = orig_request->auth_user_request->username();
-            else if (orig_request->extacl_user.size())
-                username = orig_request->extacl_user.termedBuf();
+    /* Fixup (Proxy-)Authorization special cases. Plain relaying dealt with above */
+    httpFixupAuthentication(request, hdr_in, hdr_out, flags);
 
-            snprintf(loginbuf, sizeof(loginbuf), "%s%s", username, orig_request->peer_login + 1);
-
-            httpHeaderPutStrf(hdr_out, HDR_AUTHORIZATION, "Basic %s",
-                              base64_encode(loginbuf));
-        } else {
-            /* Fixed login string */
-            httpHeaderPutStrf(hdr_out, HDR_AUTHORIZATION, "Basic %s",
-                              base64_encode(orig_request->peer_login));
-        }
-    }
-
-    /* append Cache-Control, add max-age if not there already */ {
+    /* append Cache-Control, add max-age if not there already */
+    {
         HttpHdrCc *cc = hdr_in->getCc();
 
         if (!cc)
-            cc = httpHdrCcCreate();
+            cc = new HttpHdrCc();
 
 #if 0 /* see bug 2330 */
         /* Set no-cache if determined needed but not found */
-        if (orig_request->flags.nocache)
+        if (request->flags.nocache)
             EBIT_SET(cc->mask, CC_NO_CACHE);
 #endif
 
         /* Add max-age only without no-cache */
-        if (!EBIT_TEST(cc->mask, CC_MAX_AGE) && !EBIT_TEST(cc->mask, CC_NO_CACHE)) {
+        if (!cc->hasMaxAge() && !cc->hasNoCache()) {
             const char *url =
-                entry ? entry->url() : urlCanonical(orig_request);
-            httpHdrCcSetMaxAge(cc, getMaxAge(url));
+                entry ? entry->url() : urlCanonical(request);
+            cc->maxAge(getMaxAge(url));
 
-            if (request->urlpath.size())
-                assert(strstr(url, request->urlpath.termedBuf()));
         }
 
         /* Enforce sibling relations */
         if (flags.only_if_cached)
-            EBIT_SET(cc->mask, CC_ONLY_IF_CACHED);
+            cc->onlyIfCached(true);
 
         hdr_out->putCc(cc);
 
-        httpHdrCcDestroy(cc);
+        delete cc;
     }
 
     /* maybe append Connection: keep-alive */
     if (flags.keepalive) {
         hdr_out->putStr(HDR_CONNECTION, "keep-alive");
     }
 
     /* append Front-End-Https */
     if (flags.front_end_https) {
-        if (flags.front_end_https == 1 || request->protocol == PROTO_HTTPS)
+        if (flags.front_end_https == 1 || request->protocol == AnyP::PROTO_HTTPS)
             hdr_out->putStr(HDR_FRONT_END_HTTPS, "On");
     }
 
+    if (flags.chunked_request) {
+        // Do not just copy the original value so that if the client-side
+        // starts decode other encodings, this code may remain valid.
+        hdr_out->putStr(HDR_TRANSFER_ENCODING, "chunked");
+    }
+
     /* Now mangle the headers. */
     if (Config2.onoff.mangle_request_headers)
         httpHdrMangleList(hdr_out, request, ROR_REQUEST);
 
     strConnection.clean();
 }
 
 /**
  * Decides whether a particular header may be cloned from the received Clients request
  * to our outgoing fetch request.
  */
 void
-copyOneHeaderFromClientsideRequestToUpstreamRequest(const HttpHeaderEntry *e, const String strConnection, HttpRequest * request, const HttpRequest * orig_request, HttpHeader * hdr_out, const int we_do_ranges, const http_state_flags flags)
+copyOneHeaderFromClientsideRequestToUpstreamRequest(const HttpHeaderEntry *e, const String strConnection, const HttpRequest * request, HttpHeader * hdr_out, const int we_do_ranges, const http_state_flags flags)
 {
     debugs(11, 5, "httpBuildRequestHeader: " << e->name << ": " << e->value );
 
     switch (e->id) {
 
         /** \par RFC 2616 sect 13.5.1 - Hop-by-Hop headers which Squid should not pass on. */
 
     case HDR_PROXY_AUTHORIZATION:
         /** \par Proxy-Authorization:
          * Only pass on proxy authentication to peers for which
          * authentication forwarding is explicitly enabled
          */
-
-        if (flags.proxying && orig_request->peer_login &&
-                (strcmp(orig_request->peer_login, "PASS") == 0 ||
-                 strcmp(orig_request->peer_login, "PROXYPASS") == 0)) {
+        if (!flags.originpeer && flags.proxying && request->peer_login &&
+                (strcmp(request->peer_login, "PASS") == 0 ||
+                 strcmp(request->peer_login, "PROXYPASS") == 0 ||
+                 strcmp(request->peer_login, "PASSTHRU") == 0)) {
             hdr_out->addEntry(e->clone());
         }
-
         break;
 
         /** \par RFC 2616 sect 13.5.1 - Hop-by-Hop headers which Squid does not pass on. */
 
     case HDR_CONNECTION:          /** \par Connection: */
     case HDR_TE:                  /** \par TE: */
