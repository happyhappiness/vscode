     if ((*overwrite == 'T' || *overwrite == 't') && overwrite[1] == '\0') {
         return 1;
     }
 
     /* The caller will return an HTTP_BAD_REQUEST. This will augment the
      * default message that Apache provides. */
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00581)
                   "An invalid Overwrite header was specified.");
     return -1;
 }
 
 /* resolve a request URI to a resource descriptor.
  *
