     ap_rputs("<b>Error!</b>\n", r);
     ap_rputs("<p>", r);
     lua_response = lua_tostring(L, -1);
     ap_rputs(lua_response, r);
     ap_rputs("</p>\n", r);
 
-    ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, r->pool, "Lua error: %s",
+    ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, r->pool, APLOGNO(01471) "Lua error: %s",
                   lua_response);
 }
 
 static void lua_open_callback(lua_State *L, apr_pool_t *p, void *ctx)
 {
     ap_lua_init(L, p);
