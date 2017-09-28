 
     /* Encode excessively sparse arrays as objects (if enabled) */
     if (cfg->encode_sparse_ratio > 0 &&
         max > items * cfg->encode_sparse_ratio &&
         max > cfg->encode_sparse_safe) {
         if (!cfg->encode_sparse_convert)
-            json_encode_exception(l, cfg, -1, "excessively sparse array");
+            json_encode_exception(l, cfg, json, -1, "excessively sparse array");
 
         return -1;
     }
 
     return max;
 }
 
-static void json_encode_descend(lua_State *l, json_config_t *cfg)
+static void json_check_encode_depth(lua_State *l, json_config_t *cfg,
+                                    int current_depth, strbuf_t *json)
 {
-    cfg->current_depth++;
+    /* Ensure there are enough slots free to traverse a table (key,
+     * value) and push a string for a potential error message.
+     *
+     * Unlike "decode", the key and value are still on the stack when
+     * lua_checkstack() is called.  Hence an extra slot for luaL_error()
+     * below is required just in case the next check to lua_checkstack()
+     * fails.
+     *
+     * While this won't cause a crash due to the EXTRA_STACK reserve
+     * slots, it would still be an improper use of the API. */
+    if (current_depth <= cfg->encode_max_depth && lua_checkstack(l, 3))
+        return;
 
-    if (cfg->current_depth > cfg->encode_max_depth) {
-        if (!cfg->encode_keep_buffer)
-            strbuf_free(&cfg->encode_buf);
-        luaL_error(l, "Cannot serialise, excessive nesting (%d)",
-                   cfg->current_depth);
-    }
+    if (!cfg->encode_keep_buffer)
+        strbuf_free(json);
+
+    luaL_error(l, "Cannot serialise, excessive nesting (%d)",
+               current_depth);
 }
 
-static void json_append_data(lua_State *l, json_config_t *cfg, strbuf_t *json);
+static void json_append_data(lua_State *l, json_config_t *cfg,
+                             int current_depth, strbuf_t *json);
 
 /* json_append_array args:
  * - lua_State
  * - JSON strbuf
  * - Size of passwd Lua array (top of stack) */
-static void json_append_array(lua_State *l, json_config_t *cfg, strbuf_t *json,
-                              int array_length)
+static void json_append_array(lua_State *l, json_config_t *cfg, int current_depth,
+                              strbuf_t *json, int array_length)
 {
     int comma, i;
 
-    json_encode_descend(l, cfg);
-
     strbuf_append_char(json, '[');
 
     comma = 0;
     for (i = 1; i <= array_length; i++) {
         if (comma)
             strbuf_append_char(json, ',');
         else
             comma = 1;
 
         lua_rawgeti(l, -1, i);
-        json_append_data(l, cfg, json);
+        json_append_data(l, cfg, current_depth, json);
         lua_pop(l, 1);
     }
 
     strbuf_append_char(json, ']');
-
-    cfg->current_depth--;
 }
 
-static void json_append_number(lua_State *l, strbuf_t *json, int index,
-                               json_config_t *cfg)
+static void json_append_number(lua_State *l, json_config_t *cfg,
+                               strbuf_t *json, int lindex)
 {
-    double num = lua_tonumber(l, index);
+    double num = lua_tonumber(l, lindex);
+    int len;
 
-    if (cfg->encode_refuse_badnum && (isinf(num) || isnan(num)))
-        json_encode_exception(l, cfg, index, "must not be NaN or Inf");
+    if (cfg->encode_invalid_numbers == 0) {
+        /* Prevent encoding invalid numbers */
+        if (isinf(num) || isnan(num))
+            json_encode_exception(l, cfg, json, lindex, "must not be NaN or Inf");
+    } else if (cfg->encode_invalid_numbers == 1) {
+        /* Encode invalid numbers, but handle "nan" separately
+         * since some platforms may encode as "-nan". */
+        if (isnan(num)) {
+            strbuf_append_mem(json, "nan", 3);
+            return;
+        }
+    } else {
+        /* Encode invalid numbers as "null" */
+        if (isinf(num) || isnan(num)) {
+            strbuf_append_mem(json, "null", 4);
+            return;
+        }
+    }
 
-    /* Lowest double printed with %.14g is 21 characters long:
-     * -1.7976931348623e+308
-     *
-     * Use 32 to include the \0, and a few extra just in case..
-     */
-    strbuf_append_fmt(json, 32, cfg->number_fmt, num);
+    strbuf_ensure_empty_length(json, FPCONV_G_FMT_BUFSIZE);
+    len = fpconv_g_fmt(strbuf_empty_ptr(json), num, cfg->encode_number_precision);
+    strbuf_extend_length(json, len);
 }
 
 static void json_append_object(lua_State *l, json_config_t *cfg,
-                               strbuf_t *json)
+                               int current_depth, strbuf_t *json)
 {
     int comma, keytype;
 
-    json_encode_descend(l, cfg);
-
     /* Object */
     strbuf_append_char(json, '{');
 
     lua_pushnil(l);
     /* table, startkey */
     comma = 0;
