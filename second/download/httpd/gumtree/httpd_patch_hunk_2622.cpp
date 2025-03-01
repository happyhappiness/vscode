 
     if (doc != NULL) {
         const apr_xml_elem *aset;
 
         if (!dav_validate_root(doc, "checkout")) {
             /* This supplies additional information for the default msg. */
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00601)
                           "The request body, if present, must be a "
                           "DAV:checkout element.");
             return HTTP_BAD_REQUEST;
         }
 
         if (dav_find_child(doc->root, "apply-to-version") != NULL) {
