      *  Initialise list of loaded modules
      */
     ap_loaded_modules = (module **)apr_palloc(process->pool,
         sizeof(module *) * (total_modules + DYNAMIC_MODULE_LIMIT + 1));
 
     if (ap_loaded_modules == NULL) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     "Ouch!  Out of memory in ap_setup_prelinked_modules()!");
+        return "Ouch! Out of memory in ap_setup_prelinked_modules()!";
     }
 
     for (m = ap_preloaded_modules, m2 = ap_loaded_modules; *m != NULL; )
         *m2++ = *m++;
 
     *m2 = NULL;
 
     /*
      *   Initialize chain of linked (=activate) modules
      */
-    for (m = ap_prelinked_modules; *m != NULL; m++)
-        ap_add_module(*m, process->pconf);
+    for (m = ap_prelinked_modules; *m != NULL; m++) {
+        error = ap_add_module(*m, process->pconf);
+        if (error) {
+            return error;
+        }
+    }
 
     apr_hook_sort_all();
+
+    return NULL;
 }
 
 AP_DECLARE(const char *) ap_find_module_name(module *m)
 {
     return m->name;
 }
