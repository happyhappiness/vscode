@@ -15,6 +15,7 @@ char *redisProtocolToLuaType_Error(lua_State *lua, char *reply);
 char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply);
 int redis_math_random (lua_State *L);
 int redis_math_randomseed (lua_State *L);
+void sha1hex(char *digest, char *script, size_t len);
 
 /* Take a Redis reply in the Redis protocol format and convert it into a
  * Lua type. Thanks to this function, and the introduction of not connected
@@ -306,6 +307,25 @@ int luaRedisPCallCommand(lua_State *lua) {
     return luaRedisGenericCommand(lua,0);
 }
 
+/* This adds redis.sha1hex(string) to Lua scripts using the same hashing
+ * function used for sha1ing lua scripts. */
+int luaRedisSha1hexCommand(lua_State *lua) {
+    int argc = lua_gettop(lua);
+    char digest[41];
+    size_t len;
+    char *s;
+
+    if (argc != 1) {
+        luaPushError(lua, "wrong number of arguments");
+        return 1;
+    }
+
+    s = (char*)lua_tolstring(lua,1,&len);
+    sha1hex(digest,s,len);
+    lua_pushstring(lua,digest);
+    return 1;
+}
+
 int luaLogCommand(lua_State *lua) {
     int j, argc = lua_gettop(lua);
     int level;
@@ -439,6 +459,11 @@ void scriptingInit(void) {
     lua_pushnumber(lua,REDIS_WARNING);
     lua_settable(lua,-3);
 
+    /* redis.sha1hex */
+    lua_pushstring(lua, "sha1hex");
+    lua_pushcfunction(lua, luaRedisSha1hexCommand);
+    lua_settable(lua, -3);
+
     /* Finally set the table as 'redis' global var. */
     lua_setglobal(lua,"redis");
 
@@ -491,10 +516,13 @@ void scriptingReset(void) {
     scriptingInit();
 }
 
-/* Hash the scripit into a SHA1 digest. We use this as Lua function name.
- * Digest should point to a 41 bytes buffer: 40 for SHA1 converted into an
+/* Perform the SHA1 of the input string. We use this both for hasing script
+ * bodies in order to obtain the Lua function name, and in the implementation
+ * of redis.sha1().
+ *
+ * 'digest' should point to a 41 bytes buffer: 40 for SHA1 converted into an
  * hexadecimal number, plus 1 byte for null term. */
-void hashScript(char *digest, char *script, size_t len) {
+void sha1hex(char *digest, char *script, size_t len) {
     SHA1_CTX ctx;
     unsigned char hash[20];
     char *cset = "0123456789abcdef";
@@ -667,7 +695,7 @@ void evalGenericCommand(redisClient *c, int evalsha) {
     funcname[1] = '_';
     if (!evalsha) {
         /* Hash the code if this is an EVAL call */
-        hashScript(funcname+2,c->argv[1]->ptr,sdslen(c->argv[1]->ptr));
+        sha1hex(funcname+2,c->argv[1]->ptr,sdslen(c->argv[1]->ptr));
     } else {
         /* We already have the SHA if it is a EVALSHA */
         int j;
@@ -841,7 +869,7 @@ void scriptCommand(redisClient *c) {
 
         funcname[0] = 'f';
         funcname[1] = '_';
-        hashScript(funcname+2,c->argv[2]->ptr,sdslen(c->argv[2]->ptr));
+        sha1hex(funcname+2,c->argv[2]->ptr,sdslen(c->argv[2]->ptr));
         sha = sdsnewlen(funcname+2,40);
         if (dictFind(server.lua_scripts,sha) == NULL) {
             if (luaCreateFunction(c,server.lua,funcname,c->argv[2])