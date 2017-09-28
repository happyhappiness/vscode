     NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
 };
 
-static int json_config_key;
-
 /* ===== CONFIGURATION ===== */
 
 static json_config_t *json_fetch_config(lua_State *l)
 {
     json_config_t *cfg;
 
-    lua_pushlightuserdata(l, &json_config_key);
-    lua_gettable(l, LUA_REGISTRYINDEX);
-    cfg = lua_touserdata(l, -1);
+    cfg = lua_touserdata(l, lua_upvalueindex(1));
     if (!cfg)
         luaL_error(l, "BUG: Unable to fetch CJSON configuration");
 
-    lua_pop(l, 1);
-
     return cfg;
 }
 
-static void json_verify_arg_count(lua_State *l, int args)
+/* Ensure the correct number of arguments have been provided.
+ * Pad with nil to allow other functions to simply check arg[i]
+ * to find whether an argument was provided */
+static json_config_t *json_arg_init(lua_State *l, int args)
 {
     luaL_argcheck(l, lua_gettop(l) <= args, args + 1,
                   "found too many arguments");
+
+    while (lua_gettop(l) < args)
+        lua_pushnil(l);
+
+    return json_fetch_config(l);
+}
+
+/* Process integer options for configuration functions */
+static int json_integer_option(lua_State *l, int optindex, int *setting,
+                               int min, int max)
+{
+    char errmsg[64];
+    int value;
+
+    if (!lua_isnil(l, optindex)) {
+        value = luaL_checkinteger(l, optindex);
+        snprintf(errmsg, sizeof(errmsg), "expected integer between %d and %d", min, max);
+        luaL_argcheck(l, min <= value && value <= max, 1, errmsg);
+        *setting = value;
+    }
+
+    lua_pushinteger(l, *setting);
+
+    return 1;
+}
+
+/* Process enumerated arguments for a configuration function */
+static int json_enum_option(lua_State *l, int optindex, int *setting,
+                            const char **options, int bool_true)
+{
+    static const char *bool_options[] = { "off", "on", NULL };
+
+    if (!options) {
+        options = bool_options;
+        bool_true = 1;
+    }
+
+    if (!lua_isnil(l, optindex)) {
+        if (bool_true && lua_isboolean(l, optindex))
+            *setting = lua_toboolean(l, optindex) * bool_true;
+        else
+            *setting = luaL_checkoption(l, optindex, NULL, options);
+    }
+
+    if (bool_true && (*setting == 0 || *setting == bool_true))
+        lua_pushboolean(l, *setting);
+    else
+        lua_pushstring(l, options[*setting]);
+
+    return 1;
 }
 
 /* Configures handling of extremely sparse arrays:
  * convert: Convert extremely sparse arrays into objects? Otherwise error.
  * ratio: 0: always allow sparse; 1: never allow sparse; >1: use ratio
  * safe: Always use an array when the max index <= safe */
 static int json_cfg_encode_sparse_array(lua_State *l)
 {
-    json_config_t *cfg;
-    int val;
-
-    json_verify_arg_count(l, 3);
-    cfg = json_fetch_config(l);
+    json_config_t *cfg = json_arg_init(l, 3);
 
-    switch (lua_gettop(l)) {
-    case 3:
-        val = luaL_checkinteger(l, 3);
-        luaL_argcheck(l, val >= 0, 3, "expected integer >= 0");
-        cfg->encode_sparse_safe = val;
-    case 2:
-        val = luaL_checkinteger(l, 2);
-        luaL_argcheck(l, val >= 0, 2, "expected integer >= 0");
-        cfg->encode_sparse_ratio = val;
-    case 1:
-        luaL_argcheck(l, lua_isboolean(l, 1), 1, "expected boolean");
-        cfg->encode_sparse_convert = lua_toboolean(l, 1);
-    }
-
-    lua_pushboolean(l, cfg->encode_sparse_convert);
-    lua_pushinteger(l, cfg->encode_sparse_ratio);
-    lua_pushinteger(l, cfg->encode_sparse_safe);
+    json_enum_option(l, 1, &cfg->encode_sparse_convert, NULL, 1);
+    json_integer_option(l, 2, &cfg->encode_sparse_ratio, 0, INT_MAX);
+    json_integer_option(l, 3, &cfg->encode_sparse_safe, 0, INT_MAX);
 
     return 3;
 }
 
 /* Configures the maximum number of nested arrays/objects allowed when
  * encoding */
 static int json_cfg_encode_max_depth(lua_State *l)
 {
-    json_config_t *cfg;
-    int depth;
-
-    json_verify_arg_count(l, 1);
-    cfg = json_fetch_config(l);
-
-    if (lua_gettop(l)) {
-        depth = luaL_checkinteger(l, 1);
-        luaL_argcheck(l, depth > 0, 1, "expected positive integer");
-        cfg->encode_max_depth = depth;
-    }
-
-    lua_pushinteger(l, cfg->encode_max_depth);
+    json_config_t *cfg = json_arg_init(l, 1);
 
-    return 1;
+    return json_integer_option(l, 1, &cfg->encode_max_depth, 1, INT_MAX);
 }
 
-static void json_set_number_precision(json_config_t *cfg, int prec)
+/* Configures the maximum number of nested arrays/objects allowed when
+ * encoding */
+static int json_cfg_decode_max_depth(lua_State *l)
 {
-    cfg->encode_number_precision = prec;
-    sprintf(cfg->number_fmt, "%%.%dg", prec);
+    json_config_t *cfg = json_arg_init(l, 1);
+
+    return json_integer_option(l, 1, &cfg->decode_max_depth, 1, INT_MAX);
 }
 
 /* Configures number precision when converting doubles to text */
 static int json_cfg_encode_number_precision(lua_State *l)
 {
-    json_config_t *cfg;
-    int precision;
-
-    json_verify_arg_count(l, 1);
-    cfg = json_fetch_config(l);
-
-    if (lua_gettop(l)) {
-        precision = luaL_checkinteger(l, 1);
-        luaL_argcheck(l, 1 <= precision && precision <= 14, 1,
-                      "expected integer between 1 and 14");
-        json_set_number_precision(cfg, precision);
-    }
-
-    lua_pushinteger(l, cfg->encode_number_precision);
+    json_config_t *cfg = json_arg_init(l, 1);
 
-    return 1;
+    return json_integer_option(l, 1, &cfg->encode_number_precision, 1, 14);
 }
 
 /* Configures JSON encoding buffer persistence */
 static int json_cfg_encode_keep_buffer(lua_State *l)
 {
-    json_config_t *cfg;
+    json_config_t *cfg = json_arg_init(l, 1);
+    int old_value;
 
-    json_verify_arg_count(l, 1);
-    cfg = json_fetch_config(l);
+    old_value = cfg->encode_keep_buffer;
 
-    if (lua_gettop(l)) {
-        luaL_checktype(l, 1, LUA_TBOOLEAN);
-        cfg->encode_keep_buffer = lua_toboolean(l, 1);
-    }
+    json_enum_option(l, 1, &cfg->encode_keep_buffer, NULL, 1);
 
-    lua_pushboolean(l, cfg->encode_keep_buffer);
+    /* Init / free the buffer if the setting has changed */
+    if (old_value ^ cfg->encode_keep_buffer) {
+        if (cfg->encode_keep_buffer)
+            strbuf_init(&cfg->encode_buf, 0);
+        else
+            strbuf_free(&cfg->encode_buf);
+    }
 
     return 1;
 }
 
-/* On argument: decode enum and set config variables
- * **options must point to a NULL terminated array of 4 enums
- * Returns: current enum value */
-static void json_enum_option(lua_State *l, const char **options,
-                             int *opt1, int *opt2)
-{
-    int setting;
-
-    if (lua_gettop(l)) {
-        if (lua_isboolean(l, 1))
-            setting = lua_toboolean(l, 1) * 3;
-        else
-            setting = luaL_checkoption(l, 1, NULL, options);
-
-        *opt1 = setting & 1 ? 1 : 0;
-        *opt2 = setting & 2 ? 1 : 0;
-    } else {
-        setting = *opt1 | (*opt2 << 1);
+#if defined(DISABLE_INVALID_NUMBERS) && !defined(USE_INTERNAL_FPCONV)
+void json_verify_invalid_number_setting(lua_State *l, int *setting)
+{
+    if (*setting == 1) {
+        *setting = 0;
+        luaL_error(l, "Infinity, NaN, and/or hexadecimal numbers are not supported.");
     }
-
-    if (setting)
-        lua_pushstring(l, options[setting]);
-    else
-        lua_pushboolean(l, 0);
 }
+#else
+#define json_verify_invalid_number_setting(l, s)    do { } while(0)
+#endif
+
+static int json_cfg_encode_invalid_numbers(lua_State *l)
+{
+    static const char *options[] = { "off", "on", "null", NULL };
+    json_config_t *cfg = json_arg_init(l, 1);
+
+    json_enum_option(l, 1, &cfg->encode_invalid_numbers, options, 1);
 
+    json_verify_invalid_number_setting(l, &cfg->encode_invalid_numbers);
 
-/* When enabled, rejects: NaN, Infinity, hexidecimal numbers */
-static int json_cfg_refuse_invalid_numbers(lua_State *l)
+    return 1;
+}
+
+static int json_cfg_decode_invalid_numbers(lua_State *l)
 {
-    static const char *options_enc_dec[] = { "none", "encode", "decode",
-                                             "both", NULL };
-    json_config_t *cfg;
+    json_config_t *cfg = json_arg_init(l, 1);
 
-    json_verify_arg_count(l, 1);
-    cfg = json_fetch_config(l);
+    json_enum_option(l, 1, &cfg->decode_invalid_numbers, NULL, 1);
 
-    json_enum_option(l, options_enc_dec,
-                     &cfg->encode_refuse_badnum,
-                     &cfg->decode_refuse_badnum);
+    json_verify_invalid_number_setting(l, &cfg->encode_invalid_numbers);
 
     return 1;
 }
 
 static int json_destroy_config(lua_State *l)
 {
