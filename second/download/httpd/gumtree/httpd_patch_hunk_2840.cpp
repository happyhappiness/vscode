 }
 
 static void *create_server_config(apr_pool_t *p, server_rec *s)
 {
 
     ap_lua_server_cfg *cfg = apr_pcalloc(p, sizeof(ap_lua_server_cfg));
-    cfg->code_cache = apr_pcalloc(p, sizeof(ap_lua_code_cache));
-    apr_thread_rwlock_create(&cfg->code_cache->compiled_files_lock, p);
-    cfg->code_cache->compiled_files = apr_hash_make(p);
     cfg->vm_reslists = apr_hash_make(p);
     apr_thread_rwlock_create(&cfg->vm_reslists_lock, p);
-    cfg->code_cache->pool = p;
     cfg->root_path = NULL;
 
     return cfg;
 }
 
 static int lua_request_hook(lua_State *L, request_rec *r)
 {
     ap_lua_push_request(L, r);
     return OK;
 }
 
+static int lua_post_config(apr_pool_t *pconf, apr_pool_t *plog,
+                             apr_pool_t *ptemp, server_rec *s)
+{
+    lua_ssl_val = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
+    lua_ssl_is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);
+    return OK;
+}
+static void *overlay_hook_specs(apr_pool_t *p,
+                                        const void *key,
+                                        apr_ssize_t klen,
+                                        const void *overlay_val,
+                                        const void *base_val,
+                                        const void *data)
+{
+    const apr_array_header_t *overlay_info = (const apr_array_header_t*)overlay_val;
+    const apr_array_header_t *base_info = (const apr_array_header_t*)base_val;
+    return apr_array_append(p, base_info, overlay_info);
+}
+
+static void *merge_dir_config(apr_pool_t *p, void *basev, void *overridesv)
+{
+    ap_lua_dir_cfg *a, *base, *overrides;
+
+    a         = (ap_lua_dir_cfg *)apr_pcalloc(p, sizeof(ap_lua_dir_cfg));
+    base      = (ap_lua_dir_cfg*)basev;
+    overrides = (ap_lua_dir_cfg*)overridesv;
+
+    a->pool = overrides->pool;
+    a->dir = apr_pstrdup(p, overrides->dir);
+
+    a->vm_scope = (overrides->vm_scope == AP_LUA_SCOPE_UNSET) ? base->vm_scope: overrides->vm_scope;
+    a->inherit = (overrides->inherit== AP_LUA_INHERIT_UNSET) ? base->inherit : overrides->inherit;
+
+    if (a->inherit == AP_LUA_INHERIT_UNSET || a->inherit == AP_LUA_INHERIT_PARENT_FIRST) { 
+        a->package_paths = apr_array_append(p, base->package_paths, overrides->package_paths);
+        a->package_cpaths = apr_array_append(p, base->package_cpaths, overrides->package_cpaths);
+        a->mapped_handlers = apr_array_append(p, base->mapped_handlers, overrides->mapped_handlers);
+        a->hooks = apr_hash_merge(p, overrides->hooks, base->hooks, overlay_hook_specs, NULL);
+    }
+    else if (a->inherit == AP_LUA_INHERIT_PARENT_LAST) { 
+        a->package_paths = apr_array_append(p, overrides->package_paths, base->package_paths);
+        a->package_cpaths = apr_array_append(p, overrides->package_cpaths, base->package_cpaths);
+        a->mapped_handlers = apr_array_append(p, overrides->mapped_handlers, base->mapped_handlers);
+        a->hooks = apr_hash_merge(p, base->hooks, overrides->hooks, overlay_hook_specs, NULL);
+    }
+    else { 
+        a->package_paths = overrides->package_paths;
+        a->package_cpaths = overrides->package_cpaths;
+        a->mapped_handlers= overrides->mapped_handlers;
+        a->hooks= overrides->hooks;
+    }
+
+    return a;
+}
+
 static void lua_register_hooks(apr_pool_t *p)
 {
     /* ap_register_output_filter("luahood", luahood, NULL, AP_FTYPE_RESOURCE); */
     ap_hook_handler(lua_handler, NULL, NULL, APR_HOOK_MIDDLE);
     ap_hook_create_request(create_request_config, NULL, NULL,
                            APR_HOOK_MIDDLE);
 
     /* http_request.h hooks */
+    ap_hook_translate_name(lua_translate_name_harness_first, NULL, NULL,
+                           AP_LUA_HOOK_FIRST);
     ap_hook_translate_name(lua_translate_name_harness, NULL, NULL,
                            APR_HOOK_MIDDLE);
+    ap_hook_translate_name(lua_translate_name_harness_last, NULL, NULL,
+                           AP_LUA_HOOK_LAST);
+
     ap_hook_fixups(lua_fixup_harness, NULL, NULL, APR_HOOK_MIDDLE);
     ap_hook_map_to_storage(lua_map_to_storage_harness, NULL, NULL,
                            APR_HOOK_MIDDLE);
+
+    ap_hook_check_user_id(lua_check_user_id_harness_first, NULL, NULL,
+                          AP_LUA_HOOK_FIRST);
     ap_hook_check_user_id(lua_check_user_id_harness, NULL, NULL,
-                          APR_HOOK_MIDDLE);
+                           APR_HOOK_MIDDLE);
+    ap_hook_check_user_id(lua_check_user_id_harness_last, NULL, NULL,
+                          AP_LUA_HOOK_LAST);
+
     ap_hook_type_checker(lua_type_checker_harness, NULL, NULL,
                          APR_HOOK_MIDDLE);
+
+    ap_hook_access_checker(lua_access_checker_harness_first, NULL, NULL,
+                           AP_LUA_HOOK_FIRST);
     ap_hook_access_checker(lua_access_checker_harness, NULL, NULL,
                            APR_HOOK_MIDDLE);
+    ap_hook_access_checker(lua_access_checker_harness_last, NULL, NULL,
+                           AP_LUA_HOOK_LAST);
+    ap_hook_auth_checker(lua_auth_checker_harness_first, NULL, NULL,
+                         AP_LUA_HOOK_FIRST);
     ap_hook_auth_checker(lua_auth_checker_harness, NULL, NULL,
                          APR_HOOK_MIDDLE);
+    ap_hook_auth_checker(lua_auth_checker_harness_last, NULL, NULL,
+                         AP_LUA_HOOK_LAST);
+
     ap_hook_insert_filter(lua_insert_filter_harness, NULL, NULL,
                           APR_HOOK_MIDDLE);
     ap_hook_quick_handler(lua_quick_harness, NULL, NULL, APR_HOOK_FIRST);
 
-    /* ap_hook_translate_name(lua_alias_munger, NULL, NULL, APR_HOOK_MIDDLE); */
-    ap_hook_translate_name(lua_alias_munger, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_post_config(lua_post_config, NULL, NULL, APR_HOOK_MIDDLE);
 
     APR_OPTIONAL_HOOK(ap_lua, lua_open, lua_open_hook, NULL, NULL,
                       APR_HOOK_REALLY_FIRST);
 
     APR_OPTIONAL_HOOK(ap_lua, lua_request, lua_request_hook, NULL, NULL,
                       APR_HOOK_REALLY_FIRST);
 }
 
 AP_DECLARE_MODULE(lua) = {
     STANDARD20_MODULE_STUFF,
     create_dir_config,          /* create per-dir    config structures */
-    NULL,                       /* merge  per-dir    config structures */
+    merge_dir_config,           /* merge  per-dir    config structures */
     create_server_config,       /* create per-server config structures */
     NULL,                       /* merge  per-server config structures */
     lua_commands,               /* table of config file commands       */
     lua_register_hooks          /* register hooks                      */
 };
