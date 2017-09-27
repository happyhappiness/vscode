      */
     if ((access_status = ap_run_type_checker(r)) != OK) {
         return decl_die(access_status, "find types", r);
     }
 
     if ((access_status = ap_run_fixups(r)) != OK) {
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, "fixups hook gave %d: %s",
+                      access_status, r->uri);
         return access_status;
     }
 
     return OK;
 }
 
