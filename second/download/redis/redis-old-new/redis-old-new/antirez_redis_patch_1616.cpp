@@ -79,7 +79,10 @@ char *redisProtocolToLuaType_Bulk(lua_State *lua, char *reply) {
 char *redisProtocolToLuaType_Status(lua_State *lua, char *reply) {
     char *p = strchr(reply+1,'\r');
 
+    lua_newtable(lua);
+    lua_pushstring(lua,"ok");
     lua_pushlstring(lua,reply+1,p-reply-1);
+    lua_settable(lua,-3);
     return p+2;
 }
 
@@ -246,20 +249,32 @@ void luaReplyToRedisReply(redisClient *c, lua_State *lua) {
         addReplyLongLong(c,(long long)lua_tonumber(lua,1));
         break;
     case LUA_TTABLE:
-        /* We need to check if it is an array or an error.
-         * Error are returned as a single element table with 'err' field. */
+        /* We need to check if it is an array, an error, or a status reply.
+         * Error are returned as a single element table with 'err' field.
+         * Status replies are returned as single elment table with 'ok' field */
         lua_pushstring(lua,"err");
         lua_gettable(lua,-2);
         t = lua_type(lua,-1);
         if (t == LUA_TSTRING) {
             addReplySds(c,sdscatprintf(sdsempty(),
                     "-%s\r\n",(char*)lua_tostring(lua,-1)));
+            lua_pop(lua,2);
+            return;
+        }
+
+        lua_pop(lua,1);
+        lua_pushstring(lua,"ok");
+        lua_gettable(lua,-2);
+        t = lua_type(lua,-1);
+        if (t == LUA_TSTRING) {
+            addReplySds(c,sdscatprintf(sdsempty(),
+                    "+%s\r\n",(char*)lua_tostring(lua,-1)));
             lua_pop(lua,1);
         } else {
             void *replylen = addDeferredMultiBulkLength(c);
             int j = 1, mbulklen = 0;
 
-            lua_pop(lua,1); /* Discard the 'err' field value we popped */
+            lua_pop(lua,1); /* Discard the 'ok' field value we popped */
             while(1) {
                 lua_pushnumber(lua,j++);
                 lua_gettable(lua,-2);