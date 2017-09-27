 
 /* r:addoutputfilter(name|function) */
 static int req_add_output_filter(lua_State *L)
 {
     request_rec *r = ap_lua_check_request_rec(L, 1);
     const char *name = luaL_checkstring(L, 2);
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "adding output filter %s",
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01485) "adding output filter %s",
                   name);
     ap_add_output_filter(name, L, r, r->connection);
     return 0;
 }
 
+/* wrap ap_construct_url as r:construct_url(String) */
+static int req_construct_url(lua_State *L)
+{
+    request_rec *r = ap_lua_check_request_rec(L, 1);
+    const char *name = luaL_checkstring(L, 2);
+    lua_pushstring(L, ap_construct_url(r->pool, name, r));
+    return 1;
+}
+
+/* wrap ap_escape_html r:escape_html(String) */
+static int req_escape_html(lua_State *L)
+{
+    request_rec *r = ap_lua_check_request_rec(L, 1);
+    const char *s = luaL_checkstring(L, 2);
+    lua_pushstring(L, ap_escape_html(r->pool, s));
+    return 1;
+}
+/* wrap optional ssl_var_lookup as  r:ssl_var_lookup(String) */
+static int req_ssl_var_lookup(lua_State *L)
+{
+    request_rec *r = ap_lua_check_request_rec(L, 1);
+    const char *s = luaL_checkstring(L, 2);
+    const char *res = ap_lua_ssl_val(r->pool, r->server, r->connection, r, 
+                                     (char *)s);
+    lua_pushstring(L, res);
+    return 1;
+}
 /* BEGIN dispatch mathods for request_rec fields */
 
 /* not really a field, but we treat it like one */
 static const char *req_document_root(request_rec *r)
 {
     return ap_document_root(r);
