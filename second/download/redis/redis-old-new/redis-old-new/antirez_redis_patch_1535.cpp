@@ -1,16 +1,20 @@
 #include "redis.h"
 #include "sha1.h"
+#include "rand.h"
 
 #include <lua.h>
 #include <lauxlib.h>
 #include <lualib.h>
 #include <ctype.h>
+#include <math.h>
 
 char *redisProtocolToLuaType_Int(lua_State *lua, char *reply);
 char *redisProtocolToLuaType_Bulk(lua_State *lua, char *reply);
 char *redisProtocolToLuaType_Status(lua_State *lua, char *reply);
 char *redisProtocolToLuaType_Error(lua_State *lua, char *reply);
 char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply);
+int redis_math_random (lua_State *L);
+int redis_math_randomseed (lua_State *L);
 
 /* Take a Redis reply in the Redis protocol format and convert it into a
  * Lua type. Thanks to this function, and the introduction of not connected
@@ -288,6 +292,19 @@ void scriptingInit(void) {
     /* Finally set the table as 'redis' global var. */
     lua_setglobal(lua,"redis");
 
+    /* Replace math.random and math.randomseed with our implementations. */
+    lua_getglobal(lua,"math");
+
+    lua_pushstring(lua,"random");
+    lua_pushcfunction(lua,redis_math_random);
+    lua_settable(lua,-3);
+
+    lua_pushstring(lua,"randomseed");
+    lua_pushcfunction(lua,redis_math_randomseed);
+    lua_settable(lua,-3);
+
+    lua_setglobal(lua,"math");
+
     /* Create the (non connected) client that we use to execute Redis commands
      * inside the Lua interpreter */
     server.lua_client = createClient(-1);
@@ -398,6 +415,10 @@ void evalGenericCommand(redisClient *c, int evalsha) {
     char funcname[43];
     long long numkeys;
 
+    /* We want the same PRNG sequence at every call so that our PRNG is
+     * not affected by external state. */
+    redisSrand48(0);
+
     /* Get the number of arguments that are keys */
     if (getLongLongFromObjectOrReply(c,c->argv[2],&numkeys,NULL) != REDIS_OK)
         return;
@@ -541,3 +562,42 @@ void evalShaCommand(redisClient *c) {
     }
     evalGenericCommand(c,1);
 }
+
+/* We replace math.random() with our implementation that is not affected
+ * by specific libc random() implementations and will output the same sequence
+ * (for the same seed) in every arch. */
+
+/* The following implementation is the one shipped with Lua itself but with
+ * rand() replaced by redisLrand48(). */
+int redis_math_random (lua_State *L) {
+  /* the `%' avoids the (rare) case of r==1, and is needed also because on
+     some systems (SunOS!) `rand()' may return a value larger than RAND_MAX */
+  lua_Number r = (lua_Number)(redisLrand48()%REDIS_LRAND48_MAX) /
+                                (lua_Number)REDIS_LRAND48_MAX;
+  switch (lua_gettop(L)) {  /* check number of arguments */
+    case 0: {  /* no arguments */
+      lua_pushnumber(L, r);  /* Number between 0 and 1 */
+      break;
+    }
+    case 1: {  /* only upper limit */
+      int u = luaL_checkint(L, 1);
+      luaL_argcheck(L, 1<=u, 1, "interval is empty");
+      lua_pushnumber(L, floor(r*u)+1);  /* int between 1 and `u' */
+      break;
+    }
+    case 2: {  /* lower and upper limits */
+      int l = luaL_checkint(L, 1);
+      int u = luaL_checkint(L, 2);
+      luaL_argcheck(L, l<=u, 2, "interval is empty");
+      lua_pushnumber(L, floor(r*(u-l+1))+l);  /* int between `l' and `u' */
+      break;
+    }
+    default: return luaL_error(L, "wrong number of arguments");
+  }
+  return 1;
+}
+
+int redis_math_randomseed (lua_State *L) {
+  redisSrand48(luaL_checkint(L, 1));
+  return 0;
+}