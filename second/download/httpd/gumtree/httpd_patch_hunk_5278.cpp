                       "Unable to compile VM for authz provider %s", prov_spec->name);
         return AUTHZ_GENERAL_ERROR;
     }
     lua_getglobal(L, prov_spec->function_name);
     if (!lua_isfunction(L, -1)) {
         ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(02319)
-                      "Unable to find function %s in %s",
+                      "Unable to find entry function '%s' in %s (not a valid function)",
                       prov_spec->function_name, prov_spec->file_name);
         ap_lua_release_state(L, spec, r);
         return AUTHZ_GENERAL_ERROR;
     }
     ap_lua_run_lua_request(L, r);
     if (prov_spec->args) {
