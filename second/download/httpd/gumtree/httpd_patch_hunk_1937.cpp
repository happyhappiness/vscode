     }
     else {
         /* Header overridden, no need to add, as it is already in hdrs */
     }
 
     /* setup request */
-    if (posting <= 0) {
+    if (!send_body) {
         snprintf_res = apr_snprintf(request, sizeof(_request),
             "%s %s HTTP/1.0\r\n"
             "%s" "%s" "%s"
             "%s" "\r\n",
-            (posting == 0) ? "GET" : "HEAD",
+            method_str[method],
             (isproxy) ? fullurl : path,
             keepalive ? "Connection: Keep-Alive\r\n" : "",
             cookie, auth, hdrs);
     }
     else {
         snprintf_res = apr_snprintf(request,  sizeof(_request),
             "%s %s HTTP/1.0\r\n"
             "%s" "%s" "%s"
             "Content-length: %" APR_SIZE_T_FMT "\r\n"
             "Content-type: %s\r\n"
             "%s"
             "\r\n",
-            (posting == 1) ? "POST" : "PUT",
+            method_str[method],
             (isproxy) ? fullurl : path,
             keepalive ? "Connection: Keep-Alive\r\n" : "",
             cookie, auth,
             postlen,
             (content_type[0]) ? content_type : "text/plain", hdrs);
     }
     if (snprintf_res >= sizeof(_request)) {
         err("Request too long\n");
     }
 
     if (verbosity >= 2)
         printf("INFO: %s header == \n---\n%s\n---\n", 
-                (posting == 2) ? "PUT" : "POST", request);
+               method_str[method], request);
 
     reqlen = strlen(request);
 
     /*
-     * Combine headers and (optional) post file into one contineous buffer
+     * Combine headers and (optional) post file into one continuous buffer
      */
-    if (posting >= 1) {
+    if (send_body) {
         char *buff = malloc(postlen + reqlen + 1);
         if (!buff) {
             fprintf(stderr, "error creating request buffer: out of memory\n");
             return;
         }
         strcpy(buff, request);
