     if (err) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                       "error parsing URL %s: %s",
                       url, err);
         return HTTP_BAD_REQUEST;
     }
-    /* now parse path/search args, according to rfc1738 */
-    /* N.B. if this isn't a true proxy request, then the URL _path_
-     * has already been decoded.  True proxy requests have r->uri
-     * == r->unparsed_uri, and no others have that property.
+    /*
+     * now parse path/search args, according to rfc1738:
+     * process the path. With proxy-noncanon set (by
+     * mod_proxy) we use the raw, unparsed uri
      */
-    if (r->uri == r->unparsed_uri) {
-        search = strchr(url, '?');
-        if (search != NULL)
-            *(search++) = '\0';
+    if (apr_table_get(r->notes, "proxy-nocanon")) {
+        path = url;   /* this is the raw path */
     }
-    else
+    else {
+        path = ap_proxy_canonenc(r->pool, url, strlen(url), enc_path, 0,
+                                 r->proxyreq);
         search = r->args;
-
-    /* process path */
-    path = ap_proxy_canonenc(r->pool, url, strlen(url), enc_path, 0, r->proxyreq);
+    }
     if (path == NULL)
         return HTTP_BAD_REQUEST;
 
     r->filename = apr_pstrcat(r->pool, "proxy:balancer://", host,
             "/", path, (search) ? "?" : "", (search) ? search : "", NULL);
     return OK;
