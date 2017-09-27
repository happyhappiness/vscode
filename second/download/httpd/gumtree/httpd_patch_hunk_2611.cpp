         return result;
     }
     /* note: doc == NULL if no request body */
 
     if (doc && !dav_validate_root(doc, "propfind")) {
         /* This supplies additional information for the default message. */
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00585)
                       "The \"propfind\" element was not found.");
         return HTTP_BAD_REQUEST;
     }
 
     /* ### validate that only one of these three elements is present */
 
