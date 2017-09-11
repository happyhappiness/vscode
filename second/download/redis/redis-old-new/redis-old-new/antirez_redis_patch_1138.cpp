@@ -152,9 +152,20 @@ char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply) {
 }
 
 void luaPushError(lua_State *lua, char *error) {
+    lua_Debug dbg;
+
     lua_newtable(lua);
     lua_pushstring(lua,"err");
-    lua_pushstring(lua, error);
+
+    /* Attempt to figure out where this function was called, if possible */
+    if(lua_getstack(lua, 1, &dbg) && lua_getinfo(lua, "nSl", &dbg)) {
+        sds msg = sdscatprintf(sdsempty(), "%s: %d: %s",
+            dbg.source, dbg.currentline, error);
+        lua_pushstring(lua, msg);
+        sdsfree(msg);
+    } else {
+        lua_pushstring(lua, error);
+    }
     lua_settable(lua,-3);
 }
 
@@ -866,9 +877,10 @@ void evalGenericCommand(redisClient *c, int evalsha) {
         delhook = 1;
     }
 
-    /* At this point whatever this script was never seen before or if it was
+    /* At this point whether this script was never seen before or if it was
      * already defined, we can call it. We have zero arguments and expect
      * a single return value. */
+
     err = lua_pcall(lua,0,1,0);
 
     /* Perform some cleanup that we need to do both on error and success. */