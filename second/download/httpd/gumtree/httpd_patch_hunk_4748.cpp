 {
     return lua_ssl_is_https ? lua_ssl_is_https(c) : 0;
 }
 
 /*******************************/
 
+static const char *lua_authz_parse(cmd_parms *cmd, const char *require_line,
+                                   const void **parsed_require_line)
+{
+    const char *provider_name;
+    lua_authz_provider_spec *spec;
+
+    apr_pool_userdata_get((void**)&provider_name, AUTHZ_PROVIDER_NAME_NOTE,
+                          cmd->temp_pool);
+    ap_assert(provider_name != NULL);
+
+    spec = apr_hash_get(lua_authz_providers, provider_name, APR_HASH_KEY_STRING);
+    ap_assert(spec != NULL);
+
+    if (require_line && *require_line) {
+        const char *arg;
+        spec->args = apr_array_make(cmd->pool, 2, sizeof(const char *));
+        while ((arg = ap_getword_conf(cmd->pool, &require_line)) && *arg) {
+            APR_ARRAY_PUSH(spec->args, const char *) = arg;
+        }
+    }
+
+    *parsed_require_line = spec;
+    return NULL;
+}
+
+static authz_status lua_authz_check(request_rec *r, const char *require_line,
+                                    const void *parsed_require_line)
+{
+    apr_pool_t *pool;
+    ap_lua_vm_spec *spec;
+    lua_State *L;
+    ap_lua_server_cfg *server_cfg = ap_get_module_config(r->server->module_config,
+                                                         &lua_module);
+    const ap_lua_dir_cfg *cfg = ap_get_module_config(r->per_dir_config,
+                                                     &lua_module);
+    const lua_authz_provider_spec *prov_spec = parsed_require_line;
+    int result;
+    int nargs = 0;
+
+    spec = create_vm_spec(&pool, r, cfg, server_cfg, prov_spec->file_name,
+                          NULL, 0, prov_spec->function_name, "authz provider");
+
+    L = ap_lua_get_lua_state(pool, spec);
+    if (L == NULL) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02314)
+                      "Unable to compile VM for authz provider %s", prov_spec->name);
+        return AUTHZ_GENERAL_ERROR;
+    }
+    lua_getglobal(L, prov_spec->function_name);
+    if (!lua_isfunction(L, -1)) {
+        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(02319)
+                      "Unable to find function %s in %s",
+                      prov_spec->function_name, prov_spec->file_name);
+        return AUTHZ_GENERAL_ERROR;
+    }
+    ap_lua_run_lua_request(L, r);
+    if (prov_spec->args) {
+        int i;
+        if (!lua_checkstack(L, prov_spec->args->nelts)) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02315)
+                          "Error: authz provider %s: too many arguments", prov_spec->name);
+            return AUTHZ_GENERAL_ERROR;
+        }
+        for (i = 0; i < prov_spec->args->nelts; i++) {
+            const char *arg = APR_ARRAY_IDX(prov_spec->args, i, const char *);
+            lua_pushstring(L, arg);
+        }
+        nargs = prov_spec->args->nelts;
+    }
+    if (lua_pcall(L, 1 + nargs, 1, 0)) {
+        const char *err = lua_tostring(L, -1);
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02316)
+                      "Error executing authz provider %s: %s", prov_spec->name, err);
+        return AUTHZ_GENERAL_ERROR;
+    }
+    if (!lua_isnumber(L, -1)) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02317)
+                      "Error: authz provider %s did not return integer", prov_spec->name);
+        return AUTHZ_GENERAL_ERROR;
+    }
+    result = lua_tointeger(L, -1);
+    switch (result) {
+        case AUTHZ_DENIED:
+        case AUTHZ_GRANTED:
+        case AUTHZ_NEUTRAL:
+        case AUTHZ_GENERAL_ERROR:
+        case AUTHZ_DENIED_NO_USER:
+            return result;
+        default:
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02318)
+                          "Error: authz provider %s: invalid return value %d",
+                          prov_spec->name, result);
+    }
+    return AUTHZ_GENERAL_ERROR;
+}
+
+static const authz_provider lua_authz_provider =
+{
+    &lua_authz_check,
+    &lua_authz_parse,
+};
+
+static const char *register_authz_provider(cmd_parms *cmd, void *_cfg,
+                                           const char *name, const char *file,
+                                           const char *function)
+{
+    lua_authz_provider_spec *spec;
+    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
+    if (err)
+        return err;
+
+    spec = apr_pcalloc(cmd->pool, sizeof(*spec));
+    spec->name = name;
+    spec->file_name = file;
+    spec->function_name = function;
+
+    apr_hash_set(lua_authz_providers, name, APR_HASH_KEY_STRING, spec);
+    ap_register_auth_provider(cmd->pool, AUTHZ_PROVIDER_GROUP, name,
+                              AUTHZ_PROVIDER_VERSION,
+                              &lua_authz_provider,
+                              AP_AUTH_INTERNAL_PER_CONF);
+    return NULL;
+}
+
+
 command_rec lua_commands[] = {
 
     AP_INIT_TAKE1("LuaRoot", register_lua_root, NULL, OR_ALL,
                   "Specify the base path for resolving relative paths for mod_lua directives"),
 
     AP_INIT_TAKE1("LuaPackagePath", register_package_dir, NULL, OR_ALL,
                   "Add a directory to lua's package.path"),
 
     AP_INIT_TAKE1("LuaPackageCPath", register_package_cdir, NULL, OR_ALL,
                   "Add a directory to lua's package.cpath"),
 
+    AP_INIT_TAKE3("LuaAuthzProvider", register_authz_provider, NULL, RSRC_CONF|EXEC_ON_READ,
+                  "Provide an authorization provider"),
 
     AP_INIT_TAKE23("LuaHookTranslateName", register_translate_name_hook, NULL,
                   OR_ALL,
                   "Provide a hook for the translate name phase of request processing"),
 
     AP_INIT_RAW_ARGS("<LuaHookTranslateName", register_translate_name_block,
