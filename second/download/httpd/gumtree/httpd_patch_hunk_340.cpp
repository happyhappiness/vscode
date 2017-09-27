 
     now = apr_time_now();
 
     con = calloc(concurrency * sizeof(struct connection), 1);
     
     stats = calloc(requests * sizeof(struct data), 1);
-    apr_pollset_create(&readbits, concurrency, cntxt, 0);
+
+    if ((status = apr_pollset_create(&readbits, concurrency, cntxt, 0)) != APR_SUCCESS) {
+        apr_err("apr_pollset_create failed", status);
+    }
 
     /* setup request */
     if (posting <= 0) {
 	sprintf(request, "%s %s HTTP/1.0\r\n"
 		"User-Agent: ApacheBench/%s\r\n"
 		"%s" "%s" "%s"
