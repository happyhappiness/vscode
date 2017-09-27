 
     if ((result = ap_xml_parse_input(r, &doc)) != OK)
         return result;
 
     depth = dav_get_depth(r, DAV_INFINITY);
     if (depth != 0 && depth != DAV_INFINITY) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00595)
                       "Depth must be 0 or \"infinity\" for LOCK.");
         return HTTP_BAD_REQUEST;
     }
 
     /* Ask repository module to resolve the resource */
     err = dav_get_resource(r, 0 /* label_allowed */, 0 /* use_checked_in */,
