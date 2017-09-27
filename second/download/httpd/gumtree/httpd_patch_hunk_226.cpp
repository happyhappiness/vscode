         }
         ++str;
     }
     /* We must store a terminating '\0' if we've stored any chars. We can
      * get away with storing it if we hit an error first. 
      */
-    *str = '\0'; 
+    *str = '\0';
+    if (str > str_start) {
+        /* we stored chars; don't report EOF or any other errors;
+         * the app will find out about that on the next call
+         */
+        return APR_SUCCESS;
+    }
     return rv;
 }
 
 APR_DECLARE_NONSTD(int) apr_file_printf(apr_file_t *fptr, 
                                         const char *format, ...)
 {
