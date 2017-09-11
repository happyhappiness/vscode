@@ -332,8 +332,10 @@ void luaReplyToRedisReply(redisClient *c, lua_State *lua) {
         lua_gettable(lua,-2);
         t = lua_type(lua,-1);
         if (t == LUA_TSTRING) {
-            addReplySds(c,sdscatprintf(sdsempty(),
-                    "-%s\r\n",(char*)lua_tostring(lua,-1)));
+            sds err = sdsnew(lua_tostring(lua,-1));
+            sdsmapchars(err,"\r\n","  ",2);
+            addReplySds(c,sdscatprintf(sdsempty(),"-%s\r\n",err));
+            sdsfree(err);
             lua_pop(lua,2);
             return;
         }
@@ -343,8 +345,10 @@ void luaReplyToRedisReply(redisClient *c, lua_State *lua) {
         lua_gettable(lua,-2);
         t = lua_type(lua,-1);
         if (t == LUA_TSTRING) {
-            addReplySds(c,sdscatprintf(sdsempty(),
-                    "+%s\r\n",(char*)lua_tostring(lua,-1)));
+            sds ok = sdsnew(lua_tostring(lua,-1));
+            sdsmapchars(ok,"\r\n","  ",2);
+            addReplySds(c,sdscatprintf(sdsempty(),"+%s\r\n",ok));
+            sdsfree(ok);
             lua_pop(lua,1);
         } else {
             void *replylen = addDeferredMultiBulkLength(c);