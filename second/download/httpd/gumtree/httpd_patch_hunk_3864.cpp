      * handler.  Leave INFO notes here for module debugging.
      */
     if (r->filename == NULL) {
         ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00029)
                       "Module bug?  Request filename is missing for URI %s",
                       r->uri);
-       return OK;
+        return OK;
     }
 
     /* Canonicalize the file path without resolving filename case or aliases
      * so we can begin by checking the cache for a recent directory walk.
      * This call will ensure we have an absolute path in the same pass.
      */
