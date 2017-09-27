         printf("[through %s:%d] ", proxyhost, proxyport);
     printf("(be patient)%s",
            (heartbeatres ? "\n" : "..."));
     fflush(stdout);
     }
 
-    now = apr_time_now();
-
     con = calloc(concurrency, sizeof(struct connection));
 
     stats = calloc(requests, sizeof(struct data));
 
     if ((status = apr_pollset_create(&readbits, concurrency, cntxt, 0)) != APR_SUCCESS) {
         apr_err("apr_pollset_create failed", status);
