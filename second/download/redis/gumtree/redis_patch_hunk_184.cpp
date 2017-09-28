             comma = 1;
 
         /* table, key, value */
         keytype = lua_type(l, -2);
         if (keytype == LUA_TNUMBER) {
             strbuf_append_char(json, '"');
-            json_append_number(l, json, -2, cfg);
+            json_append_number(l, cfg, json, -2);
             strbuf_append_mem(json, "\":", 2);
         } else if (keytype == LUA_TSTRING) {
             json_append_string(l, json, -2);
             strbuf_append_char(json, ':');
         } else {
-            json_encode_exception(l, cfg, -2,
+            json_encode_exception(l, cfg, json, -2,
                                   "table key must be a number or string");
             /* never returns */
         }
 
         /* table, key, value */
-        json_append_data(l, cfg, json);
+        json_append_data(l, cfg, current_depth, json);
         lua_pop(l, 1);
         /* table, key */
     }
 
     strbuf_append_char(json, '}');
-
-    cfg->current_depth--;
 }
 
 /* Serialise Lua data into JSON string. */
-static void json_append_data(lua_State *l, json_config_t *cfg, strbuf_t *json)
+static void json_append_data(lua_State *l, json_config_t *cfg,
+                             int current_depth, strbuf_t *json)
 {
     int len;
 
     switch (lua_type(l, -1)) {
     case LUA_TSTRING:
         json_append_string(l, json, -1);
         break;
     case LUA_TNUMBER:
-        json_append_number(l, json, -1, cfg);
+        json_append_number(l, cfg, json, -1);
         break;
     case LUA_TBOOLEAN:
         if (lua_toboolean(l, -1))
             strbuf_append_mem(json, "true", 4);
         else
             strbuf_append_mem(json, "false", 5);
         break;
     case LUA_TTABLE:
-        len = lua_array_length(l, cfg);
+        current_depth++;
+        json_check_encode_depth(l, cfg, current_depth, json);
+        len = lua_array_length(l, cfg, json);
         if (len > 0)
-            json_append_array(l, cfg, json, len);
+            json_append_array(l, cfg, current_depth, json, len);
         else
-            json_append_object(l, cfg, json);
+            json_append_object(l, cfg, current_depth, json);
         break;
     case LUA_TNIL:
         strbuf_append_mem(json, "null", 4);
         break;
     case LUA_TLIGHTUSERDATA:
         if (lua_touserdata(l, -1) == NULL) {
             strbuf_append_mem(json, "null", 4);
             break;
         }
     default:
         /* Remaining types (LUA_TFUNCTION, LUA_TUSERDATA, LUA_TTHREAD,
          * and LUA_TLIGHTUSERDATA) cannot be serialised */
-        json_encode_exception(l, cfg, -1, "type not supported");
+        json_encode_exception(l, cfg, json, -1, "type not supported");
         /* never returns */
     }
 }
 
 static int json_encode(lua_State *l)
 {
-    json_config_t *cfg;
+    json_config_t *cfg = json_fetch_config(l);
+    strbuf_t local_encode_buf;
+    strbuf_t *encode_buf;
     char *json;
     int len;
 
-    /* Can't use json_verify_arg_count() since we need to ensure
-     * there is only 1 argument */
     luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");
 
-    cfg = json_fetch_config(l);
-    cfg->current_depth = 0;
-
-    /* Reset the persistent buffer if it exists.
-     * Otherwise allocate a new buffer. */
-    if (strbuf_allocated(&cfg->encode_buf))
-        strbuf_reset(&cfg->encode_buf);
-    else
-        strbuf_init(&cfg->encode_buf, 0);
+    if (!cfg->encode_keep_buffer) {
+        /* Use private buffer */
+        encode_buf = &local_encode_buf;
+        strbuf_init(encode_buf, 0);
+    } else {
+        /* Reuse existing buffer */
+        encode_buf = &cfg->encode_buf;
+        strbuf_reset(encode_buf);
+    }
 
-    json_append_data(l, cfg, &cfg->encode_buf);
-    json = strbuf_string(&cfg->encode_buf, &len);
+    json_append_data(l, cfg, 0, encode_buf);
+    json = strbuf_string(encode_buf, &len);
 
     lua_pushlstring(l, json, len);
 
     if (!cfg->encode_keep_buffer)
-        strbuf_free(&cfg->encode_buf);
+        strbuf_free(encode_buf);
 
     return 1;
 }
 
 /* ===== DECODING ===== */
 
