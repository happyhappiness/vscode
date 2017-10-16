                  */
                 retry = RETRY_FTP;
             }
 
             if(retry) {
               static const char * const m[]={
-                NULL, "timeout", "HTTP error", "FTP error"
+                NULL,
+                "timeout",
+                "connection refused",
+                "HTTP error",
+                "FTP error"
               };
 
               warnf(config->global, "Transient problem: %s "
                     "Will retry in %ld seconds. "
                     "%ld retries left.\n",
                     m[retry], retry_sleep/1000L, retry_numretries);
