     }
 
     /* All right... try and run the sucker */
     rv = (*isa->HttpExtensionProc)(cid->ecb);
 
     /* Check for a log message - and log it */
-    if (cid->ecb->lpszLogData && *cid->ecb->lpszLogData)
+    if (*cid->ecb->lpszLogData) {
         ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02113)
                       "%s: %s", r->filename, cid->ecb->lpszLogData);
+    }
 
     switch(rv) {
         case 0:  /* Strange, but MS isapi accepts this as success */
         case HSE_STATUS_SUCCESS:
         case HSE_STATUS_SUCCESS_AND_KEEP_CONN:
             /* Ignore the keepalive stuff; Apache handles it just fine without
