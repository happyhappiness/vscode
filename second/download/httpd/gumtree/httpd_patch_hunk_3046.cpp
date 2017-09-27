         /* don't want to use r->hostname, as the incoming header might have a
          * port attached
          */
         const char* hostname = apr_table_get(r->headers_in,"Host");
         if (!hostname) {
             hostname =  r->server->server_hostname;
-            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
-                          "proxy: no HTTP 0.9 request (with no host line) "
+            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01092)
+                          "no HTTP 0.9 request (with no host line) "
                           "on incoming request and preserve host set "
                           "forcing hostname to be %s for uri %s",
-                          hostname,
-                          r->uri );
+                          hostname, r->uri);
         }
         buf = apr_pstrcat(p, "Host: ", hostname, CRLF, NULL);
     }
     ap_xlate_proto_to_ascii(buf, strlen(buf));
     e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
     APR_BRIGADE_INSERT_TAIL(header_brigade, e);
