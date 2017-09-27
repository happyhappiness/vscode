 
     if ((result = ap_xml_parse_input(r, &doc)) != OK)
         return result;
 
     if (doc == NULL || !dav_validate_root(doc, "merge")) {
         /* This supplies additional information for the default msg. */
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00616)
                       "The request body must be present and must be a "
                       "DAV:merge element.");
         return HTTP_BAD_REQUEST;
     }
 
     if ((source_elem = dav_find_child(doc->root, "source")) == NULL) {
         /* This supplies additional information for the default msg. */
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00617)
                       "The DAV:merge element must contain a DAV:source "
                       "element.");
         return HTTP_BAD_REQUEST;
     }
     if ((href_elem = dav_find_child(source_elem, "href")) == NULL) {
         /* This supplies additional information for the default msg. */
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00618)
                       "The DAV:source element must contain a DAV:href "
                       "element.");
         return HTTP_BAD_REQUEST;
     }
     source = dav_xml_get_cdata(href_elem, r->pool, 1 /* strip_white */);
 
     /* get a subrequest for the source, so that we can get a dav_resource
        for that source. */
     lookup = dav_lookup_uri(source, r, 0 /* must_be_absolute */);
     if (lookup.rnew == NULL) {
         if (lookup.err.status == HTTP_BAD_REQUEST) {
             /* This supplies additional information for the default message. */
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00619)
                           "%s", lookup.err.desc);
             return HTTP_BAD_REQUEST;
         }
 
         /* ### this assumes that dav_lookup_uri() only generates a status
          * ### that Apache can provide a status line for!! */
