     do {
         apr_int32_t n;
         const apr_pollfd_t *pollresults;
 
         n = concurrency;
         do {
-        status = apr_pollset_poll(readbits, aprtimeout, &n, &pollresults);
+            status = apr_pollset_poll(readbits, aprtimeout, &n, &pollresults);
         } while (APR_STATUS_IS_EINTR(status));
         if (status != APR_SUCCESS)
             apr_err("apr_poll", status);
 
         if (!n) {
             err("\nServer timed out\n\n");
