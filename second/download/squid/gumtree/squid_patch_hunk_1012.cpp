         break;
         }
     }
 }
 
 static void
-prepareAcceleratedURL(ConnStateData * conn, ClientHttpRequest *http, char *url, const char *req_hdr)
+prepareAcceleratedURL(ConnStateData * conn, ClientHttpRequest *http, const Http1::RequestParserPointer &hp)
 {
     int vhost = conn->port->vhost;
     int vport = conn->port->vport;
-    char *host;
-    char ipbuf[MAX_IPSTRLEN];
+    static char ipbuf[MAX_IPSTRLEN];
 
     http->flags.accel = true;
 
     /* BUG: Squid cannot deal with '*' URLs (RFC2616 5.1.2) */
 
-    if (strncasecmp(url, "cache_object://", 15) == 0)
+    static const SBuf cache_object("cache_object://");
+    if (hp->requestUri().startsWith(cache_object))
         return; /* already in good shape */
 
-    if (*url != '/') {
+    // XXX: re-use proper URL parser for this
+    SBuf url = hp->requestUri(); // use full provided URI if we abort
+    do { // use a loop so we can break out of it
+        ::Parser::Tokenizer tok(url);
+        if (tok.skip('/')) // origin-form URL already.
+            break;
+
         if (conn->port->vhost)
             return; /* already in good shape */
 
-        /* else we need to ignore the host name */
-        url = strstr(url, "//");
-
-#if SHOULD_REJECT_UNKNOWN_URLS
+        // skip the URI scheme
+        static const CharacterSet uriScheme = CharacterSet("URI-scheme","+-.") + CharacterSet::ALPHA + CharacterSet::DIGIT;
+        static const SBuf uriSchemeEnd("://");
+        if (!tok.skipAll(uriScheme) || !tok.skip(uriSchemeEnd))
+            break;
 
-        if (!url) {
-            hp->request_parse_status = Http::scBadRequest;
-            return conn->abortRequestParsing("error:invalid-request");
-        }
-#endif
+        // skip the authority segment
+        // RFC 3986 complex nested ABNF for "authority" boils down to this:
+        static const CharacterSet authority = CharacterSet("authority","-._~%:@[]!$&'()*+,;=") +
+                                              CharacterSet::HEXDIG + CharacterSet::ALPHA + CharacterSet::DIGIT;
+        if (!tok.skipAll(authority))
+            break;
 
-        if (url)
-            url = strchr(url + 2, '/');
+        static const SBuf slashUri("/");
+        const SBuf t = tok.remaining();
+        if (t.isEmpty())
+            url = slashUri;
+        else if (t[0]=='/') // looks like path
+            url = t;
+        else if (t[0]=='?' || t[0]=='#') { // looks like query or fragment. fix '/'
+            url = slashUri;
+            url.append(t);
+        } // else do nothing. invalid path
 
-        if (!url)
-            url = (char *) "/";
+    } while(false);
+
+#if SHOULD_REJECT_UNKNOWN_URLS
+    // reject URI which are not well-formed even after the processing above
+    if (url.isEmpty() || url[0] != '/') {
+        hp->parseStatusCode = Http::scBadRequest;
+        return conn->abortRequestParsing("error:invalid-request");
     }
+#endif
 
     if (vport < 0)
         vport = http->getConn()->clientConnection->local.port();
 
     const bool switchedToHttps = conn->switchedToHttps();
     const bool tryHostHeader = vhost || switchedToHttps;
-    if (tryHostHeader && (host = mime_get_header(req_hdr, "Host")) != NULL) {
+    char *host = NULL;
+    if (tryHostHeader && (host = hp->getHeaderField("Host"))) {
         debugs(33, 5, "ACCEL VHOST REWRITE: vhost=" << host << " + vport=" << vport);
         char thost[256];
         if (vport > 0) {
             thost[0] = '\0';
             char *t = NULL;
             if (host[strlen(host)] != ']' && (t = strrchr(host,':')) != NULL) {
