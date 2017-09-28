         break;;
     default:
         json_throw_parse_error(l, json, "value", token);
     }
 }
 
-/* json_text must be null terminated string */
-static void lua_json_decode(lua_State *l, const char *json_text, int json_len)
+static int json_decode(lua_State *l)
 {
     json_parse_t json;
     json_token_t token;
+    size_t json_len;
+
+    luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");
 
     json.cfg = json_fetch_config(l);
-    json.data = json_text;
-    json.index = 0;
+    json.data = luaL_checklstring(l, 1, &json_len);
+    json.current_depth = 0;
+    json.ptr = json.data;
+
+    /* Detect Unicode other than UTF-8 (see RFC 4627, Sec 3)
+     *
+     * CJSON can support any simple data type, hence only the first
+     * character is guaranteed to be ASCII (at worst: '"'). This is
+     * still enough to detect whether the wrong encoding is in use. */
+    if (json_len >= 2 && (!json.data[0] || !json.data[1]))
+        luaL_error(l, "JSON parser does not support UTF-16 or UTF-32");
 
     /* Ensure the temporary buffer can hold the entire string.
      * This means we no longer need to do length checks since the decoded
      * string must be smaller than the entire json string */
     json.tmp = strbuf_new(json_len);
 
