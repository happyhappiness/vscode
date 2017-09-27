             }
             apr_socket_close(sd);
         }
     }
 
     if (sa == NULL) {
-        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
+        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01974)
                       "could not connect to OCSP responder '%s'",
                       uri->hostinfo);
         apr_socket_close(sd);
         return NULL;
     }
 
-    /* send the request and get a response */ 
-    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, 
+    /* send the request and get a response */
+    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01975)
                  "sending request to OCSP responder");
 
     while ((len = BIO_read(request, buf, sizeof buf)) > 0) {
         char *wbuf = buf;
         apr_size_t remain = len;
-        
+
         do {
             apr_size_t wlen = remain;
 
             rv = apr_socket_send(sd, wbuf, &wlen);
             wbuf += remain;
             remain -= wlen;
         } while (rv == APR_SUCCESS && remain > 0);
 
         if (rv) {
             apr_socket_close(sd);
-            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
+            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01976)
                           "failed to send request to OCSP responder '%s'",
                           uri->hostinfo);
             return NULL;
         }
     }
 
