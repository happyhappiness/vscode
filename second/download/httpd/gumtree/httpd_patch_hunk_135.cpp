 
             if ((nLogFD != NULL) && 
                 (apr_file_info_get(&finfo, APR_FINFO_SIZE, nLogFD) == APR_SUCCESS)) {
                 current_size = finfo.size;
             }
 
-            if (current_size > sRotation || nRead < 0) {
+            if (current_size > sRotation) {
                 nLogFDprev = nLogFD;
                 nLogFD = NULL;
             }
         }
         else {
             fprintf(stderr, "No rotation time or size specified\n");
