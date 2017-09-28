     json_next_token(&json, &token);
 
     if (token.type != T_END)
         json_throw_parse_error(l, &json, "the end", &token);
 
     strbuf_free(json.tmp);
+
+    return 1;
 }
 
-static int json_decode(lua_State *l)
+/* ===== INITIALISATION ===== */
+
+#if !defined(LUA_VERSION_NUM) || LUA_VERSION_NUM < 502
+/* Compatibility for Lua 5.1.
+ *
+ * luaL_setfuncs() is used to create a module table where the functions have
+ * json_config_t as their first upvalue. Code borrowed from Lua 5.2 source. */
+static void luaL_setfuncs (lua_State *l, const luaL_Reg *reg, int nup)
 {
-    const char *json;
-    size_t len;
+    int i;
 
-    json_verify_arg_count(l, 1);
+    luaL_checkstack(l, nup, "too many upvalues");
+    for (; reg->name != NULL; reg++) {  /* fill the table with given functions */
+        for (i = 0; i < nup; i++)  /* copy upvalues to the top */
+            lua_pushvalue(l, -nup);
+        lua_pushcclosure(l, reg->func, nup);  /* closure with those upvalues */
+        lua_setfield(l, -(nup + 2), reg->name);
+    }
+    lua_pop(l, nup);  /* remove upvalues */
+}
+#endif
 
-    json = luaL_checklstring(l, 1, &len);
+/* Call target function in protected mode with all supplied args.
+ * Assumes target function only returns a single non-nil value.
+ * Convert and return thrown errors as: nil, "error message" */
+static int json_protect_conversion(lua_State *l)
+{
+    int err;
 
-    /* Detect Unicode other than UTF-8 (see RFC 4627, Sec 3)
-     *
-     * CJSON can support any simple data type, hence only the first
-     * character is guaranteed to be ASCII (at worst: '"'). This is
-     * still enough to detect whether the wrong encoding is in use. */
-    if (len >= 2 && (!json[0] || !json[1]))
-        luaL_error(l, "JSON parser does not support UTF-16 or UTF-32");
+    /* Deliberately throw an error for invalid arguments */
+    luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");
 
-    lua_json_decode(l, json, len);
+    /* pcall() the function stored as upvalue(1) */
+    lua_pushvalue(l, lua_upvalueindex(1));
+    lua_insert(l, 1);
+    err = lua_pcall(l, 1, 1, 0);
+    if (!err)
+        return 1;
 
-    return 1;
-}
+    if (err == LUA_ERRRUN) {
+        lua_pushnil(l);
+        lua_insert(l, -2);
+        return 2;
+    }
 
-/* ===== INITIALISATION ===== */
+    /* Since we are not using a custom error handler, the only remaining
+     * errors are memory related */
+    return luaL_error(l, "Memory allocation error in CJSON protected call");
+}
 
-int luaopen_cjson(lua_State *l)
+/* Return cjson module table */
+static int lua_cjson_new(lua_State *l)
 {
     luaL_Reg reg[] = {
         { "encode", json_encode },
         { "decode", json_decode },
         { "encode_sparse_array", json_cfg_encode_sparse_array },
         { "encode_max_depth", json_cfg_encode_max_depth },
+        { "decode_max_depth", json_cfg_decode_max_depth },
         { "encode_number_precision", json_cfg_encode_number_precision },
         { "encode_keep_buffer", json_cfg_encode_keep_buffer },
-        { "refuse_invalid_numbers", json_cfg_refuse_invalid_numbers },
+        { "encode_invalid_numbers", json_cfg_encode_invalid_numbers },
+        { "decode_invalid_numbers", json_cfg_decode_invalid_numbers },
+        { "new", lua_cjson_new },
         { NULL, NULL }
     };
 
-    /* Use json_fetch_config as a pointer.
-     * It's faster than using a config string, and more unique */
-    lua_pushlightuserdata(l, &json_config_key);
-    json_create_config(l);
-    lua_settable(l, LUA_REGISTRYINDEX);
+    /* Initialise number conversions */
+    fpconv_init();
 
-    luaL_register(l, "cjson", reg);
+    /* cjson module table */
+    lua_newtable(l);
+
+    /* Register functions with config data as upvalue */
+    json_create_config(l);
+    luaL_setfuncs(l, reg, 1);
 
     /* Set cjson.null */
     lua_pushlightuserdata(l, NULL);
     lua_setfield(l, -2, "null");
 
-    /* Set cjson.version */
-    lua_pushliteral(l, VERSION);
-    lua_setfield(l, -2, "version");
+    /* Set module name / version fields */
+    lua_pushliteral(l, CJSON_MODNAME);
+    lua_setfield(l, -2, "_NAME");
+    lua_pushliteral(l, CJSON_VERSION);
+    lua_setfield(l, -2, "_VERSION");
+
+    return 1;
+}
+
+/* Return cjson.safe module table */
+static int lua_cjson_safe_new(lua_State *l)
+{
+    const char *func[] = { "decode", "encode", NULL };
+    int i;
+
+    lua_cjson_new(l);
+
+    /* Fix new() method */
+    lua_pushcfunction(l, lua_cjson_safe_new);
+    lua_setfield(l, -2, "new");
+
+    for (i = 0; func[i]; i++) {
+        lua_getfield(l, -1, func[i]);
+        lua_pushcclosure(l, json_protect_conversion, 1);
+        lua_setfield(l, -2, func[i]);
+    }
+
+    return 1;
+}
+
+int luaopen_cjson(lua_State *l)
+{
+    lua_cjson_new(l);
+
+#ifdef ENABLE_CJSON_GLOBAL
+    /* Register a global "cjson" table. */
+    lua_pushvalue(l, -1);
+    lua_setglobal(l, CJSON_MODNAME);
+#endif
 
     /* Return cjson table */
     return 1;
 }
 
+int luaopen_cjson_safe(lua_State *l)
+{
+    lua_cjson_safe_new(l);
+
+    /* Return cjson.safe table */
+    return 1;
+}
+
 /* vi:ai et sw=4 ts=4:
  */
