     }
     else {
         return DECLINED;
     }
     def_port = apr_uri_port_of_scheme("ftp");
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
                  "proxy: FTP: canonicalising URL %s", url);
 
     port = def_port;
     err = ap_proxy_canon_netloc(p, &url, &user, &password, &host, &port);
     if (err)
         return HTTP_BAD_REQUEST;
