      * otherwise let translate_name kill the request.
      */
     if (!file_req) {
         if ((access_status = ap_location_walk(r))) {
             return access_status;
         }
+        if ((access_status = ap_if_walk(r))) {
+            return access_status;
+        }
 
-        d = ap_get_module_config(r->per_dir_config, &core_module);
+        d = ap_get_core_module_config(r->per_dir_config);
         if (d->log) {
             r->log = d->log;
         }
 
         if ((access_status = ap_run_translate_name(r))) {
             return decl_die(access_status, "translate", r);
