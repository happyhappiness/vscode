     printf("Write errors:           %d\n", epipe);
     if (err_response)
         printf("Non-2xx responses:      %d\n", err_response);
     if (keepalive)
         printf("Keep-Alive requests:    %d\n", doneka);
     printf("Total transferred:      %" APR_INT64_T_FMT " bytes\n", totalread);
-    if (posting > 0)
+    if (posting == 1)
         printf("Total POSTed:           %" APR_INT64_T_FMT "\n", totalposted);
+    if (posting == 2)
+        printf("Total PUT:              %" APR_INT64_T_FMT "\n", totalposted);
     printf("HTML transferred:       %" APR_INT64_T_FMT " bytes\n", totalbread);
 
     /* avoid divide by zero */
     if (timetaken && done) {
         printf("Requests per second:    %.2f [#/sec] (mean)\n",
                (double) done / timetaken);
