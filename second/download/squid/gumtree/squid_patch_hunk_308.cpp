  */
 static void
 make_pub_auth(cachemgr_request * req)
 {
     static char buf[1024];
     safe_free(req->pub_auth);
-    debug(3) fprintf(stderr, "cmgr: encoding for pub...\n");
+    debug("cmgr: encoding for pub...\n");
 
     if (!req->passwd || !strlen(req->passwd))
         return;
 
     /* host | time | user | passwd */
-    snprintf(buf, sizeof(buf), "%s|%d|%s|%s",
-             req->hostname,
-             (int) now,
-             req->user_name ? req->user_name : "",
-             req->passwd);
-
-    debug(3) fprintf(stderr, "cmgr: pre-encoded for pub: %s\n", buf);
-
-    debug(3) fprintf(stderr, "cmgr: encoded: '%s'\n", base64_encode(buf));
-
-    req->pub_auth = xstrdup(base64_encode(buf));
+    const int bufLen = snprintf(buf, sizeof(buf), "%s|%d|%s|%s",
+                                req->hostname,
+                                (int) now,
+                                req->user_name ? req->user_name : "",
+                                req->passwd);
+    debug("cmgr: pre-encoded for pub: %s\n", buf);
+
+    const int encodedLen = base64_encode_len(bufLen);
+    req->pub_auth = (char *) xmalloc(encodedLen);
+    base64_encode_str(req->pub_auth, encodedLen, buf, bufLen);
+    debug("cmgr: encoded: '%s'\n", req->pub_auth);
 }
 
 static void
 decode_pub_auth(cachemgr_request * req)
 {
     char *buf;
     const char *host_name;
     const char *time_str;
     const char *user_name;
     const char *passwd;
 
-    debug(2) fprintf(stderr, "cmgr: decoding pub: '%s'\n", safe_str(req->pub_auth));
+    debug("cmgr: decoding pub: '%s'\n", safe_str(req->pub_auth));
     safe_free(req->passwd);
 
     if (!req->pub_auth || strlen(req->pub_auth) < 4 + strlen(safe_str(req->hostname)))
         return;
 
-    buf = xstrdup(base64_decode(req->pub_auth));
+    const int decodedLen = base64_decode_len(req->pub_auth);
+    buf = (char*)xmalloc(decodedLen);
+    base64_decode(buf, decodedLen, req->pub_auth);
 
-    debug(3) fprintf(stderr, "cmgr: length ok\n");
+    debug("cmgr: length ok\n");
 
     /* parse ( a lot of memory leaks, but that is cachemgr style :) */
     if ((host_name = strtok(buf, "|")) == NULL) {
         xfree(buf);
         return;
     }
 
-    debug(3) fprintf(stderr, "cmgr: decoded host: '%s'\n", host_name);
+    debug("cmgr: decoded host: '%s'\n", host_name);
 
     if ((time_str = strtok(NULL, "|")) == NULL) {
         xfree(buf);
         return;
     }
 
-    debug(3) fprintf(stderr, "cmgr: decoded time: '%s' (now: %d)\n", time_str, (int) now);
+    debug("cmgr: decoded time: '%s' (now: %d)\n", time_str, (int) now);
 
     if ((user_name = strtok(NULL, "|")) == NULL) {
         xfree(buf);
         return;
     }
 
-    debug(3) fprintf(stderr, "cmgr: decoded uname: '%s'\n", user_name);
+    debug("cmgr: decoded uname: '%s'\n", user_name);
 
     if ((passwd = strtok(NULL, "|")) == NULL) {
         xfree(buf);
         return;
     }
 
-    debug(2) fprintf(stderr, "cmgr: decoded passwd: '%s'\n", passwd);
+    debug("cmgr: decoded passwd: '%s'\n", passwd);
 
     /* verify freshness and validity */
     if (atoi(time_str) + passwd_ttl < now) {
         xfree(buf);
         return;
     }
 
     if (strcasecmp(host_name, req->hostname)) {
         xfree(buf);
         return;
     }
 
-    debug(1) fprintf(stderr, "cmgr: verified auth. info.\n");
+    debug("cmgr: verified auth. info.\n");
 
     /* ok, accept */
     safe_free(req->user_name);
 
     req->user_name = xstrdup(user_name);
 
