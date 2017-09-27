             "\r\n",
             method_str[method],
             (isproxy) ? fullurl : path,
             keepalive ? "Connection: Keep-Alive\r\n" : "",
             cookie, auth,
             postlen,
-            (content_type[0]) ? content_type : "text/plain", hdrs);
+            (content_type != NULL) ? content_type : "text/plain", hdrs);
     }
     if (snprintf_res >= sizeof(_request)) {
         err("Request too long\n");
     }
 
     if (verbosity >= 2)
