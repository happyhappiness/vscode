                                     function_name,
                                     "mapped handler");
             L = ap_lua_get_lua_state(pool, spec, r);
 
             if (!L) {
                 ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(02330)
-                                "lua: Failed to obtain lua interpreter for %s %s",
+                                "lua: Failed to obtain Lua interpreter for entry function '%s' in %s",
                                 function_name, filename);
                 ap_lua_release_state(L, spec, r);
                 return HTTP_INTERNAL_SERVER_ERROR;
             }
 
             if (function_name != NULL) {
                 lua_getglobal(L, function_name);
                 if (!lua_isfunction(L, -1)) {
                     ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(02331)
-                                    "lua: Unable to find function %s in %s",
+                                    "lua: Unable to find entry function '%s' in %s (not a valid function)",
                                     function_name,
                                     filename);
                     ap_lua_release_state(L, spec, r);
                     return HTTP_INTERNAL_SERVER_ERROR;
                 }
 
