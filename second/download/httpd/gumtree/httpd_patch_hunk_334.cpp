 
         if (readlen != 1) {
             rv = APR_EOF;
             break;
         }
         
-        if (str[i] == '\r' || str[i] == '\x1A')
-            i--;
-        else if (str[i] == '\n') {
+        if (str[i] == '\n') {
             i++;
             break;
         }
     }
     str[i] = 0;
+    if (i > 0) {
+        /* we stored chars; don't report EOF or any other errors;
+         * the app will find out about that on the next call
+         */
+        return APR_SUCCESS;
+    }
     return rv;
 }
 
 
 
 APR_DECLARE_NONSTD(int) apr_file_printf(apr_file_t *fptr, 
