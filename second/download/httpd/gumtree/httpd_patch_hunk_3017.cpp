     }
     else {
         return DECLINED;
     }
     def_port = apr_uri_port_of_scheme("ftp");
 
-    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
-                 "proxy: FTP: canonicalising URL %s", url);
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "canonicalising URL %s", url);
 
     port = def_port;
     err = ap_proxy_canon_netloc(p, &url, &user, &password, &host, &port);
     if (err)
         return HTTP_BAD_REQUEST;
     if (user != NULL && !ftp_check_string(user))
