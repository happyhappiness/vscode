     }
     ap_add_output_filter("MOD_EXPIRES", NULL, r, r->connection);
     return;
 }
 static void register_hooks(apr_pool_t *p)
 {
+    /* mod_expires needs to run *before* the cache save filter which is
+     * AP_FTYPE_CONTENT_SET-1.  Otherwise, our expires won't be honored.
+     */
     ap_register_output_filter("MOD_EXPIRES", expires_filter, NULL,
-                              AP_FTYPE_CONTENT_SET);
+                              AP_FTYPE_CONTENT_SET-2);
     ap_hook_insert_error_filter(expires_insert_filter, NULL, NULL, APR_HOOK_MIDDLE);
     ap_hook_insert_filter(expires_insert_filter, NULL, NULL, APR_HOOK_MIDDLE);
 }
 
 module AP_MODULE_DECLARE_DATA expires_module =
 {
