                       "Unable to find entry function '%s' in %s (not a valid function)",
                       prov_spec->function_name, prov_spec->file_name);
         ap_lua_release_state(L, spec, r);
         return AUTHZ_GENERAL_ERROR;
     }
     ap_lua_run_lua_request(L, r);
-    if (prov_spec->args) {
+    if (prov_func->args) {
         int i;
-        if (!lua_checkstack(L, prov_spec->args->nelts)) {
+        if (!lua_checkstack(L, prov_func->args->nelts)) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02315)
                           "Error: authz provider %s: too many arguments", prov_spec->name);
             ap_lua_release_state(L, spec, r);
             return AUTHZ_GENERAL_ERROR;
         }
-        for (i = 0; i < prov_spec->args->nelts; i++) {
-            const char *arg = APR_ARRAY_IDX(prov_spec->args, i, const char *);
+        for (i = 0; i < prov_func->args->nelts; i++) {
+            const char *arg = APR_ARRAY_IDX(prov_func->args, i, const char *);
             lua_pushstring(L, arg);
         }
-        nargs = prov_spec->args->nelts;
+        nargs = prov_func->args->nelts;
     }
     if (lua_pcall(L, 1 + nargs, 1, 0)) {
         const char *err = lua_tostring(L, -1);
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02316)
                       "Error executing authz provider %s: %s", prov_spec->name, err);
         ap_lua_release_state(L, spec, r);
