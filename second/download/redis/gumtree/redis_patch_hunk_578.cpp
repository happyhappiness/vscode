     } else {
         lua_pushstring(lua, error);
     }
     lua_settable(lua,-3);
 }
 
+/* In case the error set into the Lua stack by luaPushError() was generated
+ * by the non-error-trapping version of redis.pcall(), which is redis.call(),
+ * this function will raise the Lua error so that the execution of the
+ * script will be halted. */
+int luaRaiseError(lua_State *lua) {
+    lua_pushstring(lua,"err");
+    lua_gettable(lua,-2);
+    return lua_error(lua);
+}
+
 /* Sort the array currently in the stack. We do this to make the output
  * of commands like KEYS or SMEMBERS something deterministic when called
  * from Lua (to play well with AOf/replication).
  *
  * The array is sorted using table.sort itself, and assuming all the
  * list elements are strings. */
