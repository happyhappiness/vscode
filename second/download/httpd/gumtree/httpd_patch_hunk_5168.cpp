         url += 6;
         scheme = "https";
     }
     else {
         return DECLINED;
     }
-    def_port = apr_uri_port_of_scheme(scheme);
+    port = def_port = ap_proxy_port_of_scheme(scheme);
 
     ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                   "HTTP: canonicalising URL %s", url);
 
     /* do syntatic check.
      * We break the URL into host, port, path, search
      */
-    port = def_port;
     err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
     if (err) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01083)
                       "error parsing URL %s: %s", url, err);
         return HTTP_BAD_REQUEST;
     }
