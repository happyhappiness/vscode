             fprintf(stderr, "No rotation time or size specified\n");
             exit(2);
         }
 
         if (nLogFD == NULL) {
             int tLogStart;
+            apr_status_t rv;
 
             if (tRotation) {
                 tLogStart = (now / tRotation) * tRotation;
             }
             else {
                 tLogStart = (int)apr_time_sec(apr_time_now());
