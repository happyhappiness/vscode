     ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "canonicalising URL %s", url);
 
     /*
      * do syntactic check.
      * We break the URL into host, port, path, search
      */
+    port = def_port = ap_proxy_port_of_scheme("ajp");
+
     err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
     if (err) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00867) "error parsing URL %s: %s",
                       url, err);
         return HTTP_BAD_REQUEST;
     }
