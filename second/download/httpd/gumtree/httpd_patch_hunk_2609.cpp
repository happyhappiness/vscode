      * For non-collections, depth is ignored, unless it is an illegal value (1).
      */
     depth = dav_get_depth(r, DAV_INFINITY);
 
     if (resource->collection && depth != DAV_INFINITY) {
         /* This supplies additional information for the default message. */
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00582)
                       "Depth must be \"infinity\" for DELETE of a collection.");
         return HTTP_BAD_REQUEST;
     }
 
     if (!resource->collection && depth == 1) {
         /* This supplies additional information for the default message. */
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00583)
                       "Depth of \"1\" is not allowed for DELETE.");
         return HTTP_BAD_REQUEST;
     }
 
     /*
     ** If any resources fail the lock/If: conditions, then we must fail
