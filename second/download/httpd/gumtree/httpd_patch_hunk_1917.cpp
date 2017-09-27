      */
     if (!file_req) {
         if ((access_status = ap_location_walk(r))) {
             return access_status;
         }
 
+        d = ap_get_module_config(r->per_dir_config, &core_module);
+        if (d->log) {
+            r->log = d->log;
+        }
+
         if ((access_status = ap_run_translate_name(r))) {
             return decl_die(access_status, "translate", r);
         }
     }
 
     /* Reset to the server default config prior to running map_to_storage
