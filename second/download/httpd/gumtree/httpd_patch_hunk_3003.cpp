         }
 
         envlen += vallen;
 
 	/* The cast of bodylen is safe since FCGI_MAX_ENV_SIZE is for sure an int */
         if (envlen > FCGI_MAX_ENV_SIZE) {
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                          "proxy: FCGI: truncating environment to %d bytes and %d elements",
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01063)
+                          "truncating environment to %d bytes and %d elements",
                           (int)bodylen, i);
             break;
         }
 
         bodylen = envlen;
     }
