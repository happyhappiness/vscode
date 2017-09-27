 static void pstack_dump(lua_State *L, apr_pool_t *r, int level,
                         const char *msg)
 {
     int i;
     int top = lua_gettop(L);
 
-    ap_log_perror(APLOG_MARK, level, 0, r, "Lua Stack Dump: [%s]", msg);
+    ap_log_perror(APLOG_MARK, level, 0, r, APLOGNO(03211)
+                  "Lua Stack Dump: [%s]", msg);
 
     for (i = 1; i <= top; i++) {
         int t = lua_type(L, i);
         switch (t) {
         case LUA_TSTRING:{
-                ap_log_perror(APLOG_MARK, level, 0, r,
+                ap_log_perror(APLOG_MARK, level, 0, r, APLOGNO(03212)
                               "%d:  '%s'", i, lua_tostring(L, i));
                 break;
             }
         case LUA_TUSERDATA:{
-                ap_log_perror(APLOG_MARK, level, 0, r, "%d:  userdata", i);
+                ap_log_perror(APLOG_MARK, level, 0, r, APLOGNO(03213)
+                              "%d:  userdata", i);
                 break;
             }
         case LUA_TLIGHTUSERDATA:{
-                ap_log_perror(APLOG_MARK, level, 0, r, "%d:  lightuserdata",
-                              i);
+                ap_log_perror(APLOG_MARK, level, 0, r, APLOGNO(03214)
+                              "%d:  lightuserdata", i);
                 break;
             }
         case LUA_TNIL:{
-                ap_log_perror(APLOG_MARK, level, 0, r, "%d:  NIL", i);
+                ap_log_perror(APLOG_MARK, level, 0, r, APLOGNO(03215)
+                              "%d:  NIL", i);
                 break;
             }
         case LUA_TNONE:{
-                ap_log_perror(APLOG_MARK, level, 0, r, "%d:  None", i);
+                ap_log_perror(APLOG_MARK, level, 0, r, APLOGNO(03216)
+                              "%d:  None", i);
                 break;
             }
         case LUA_TBOOLEAN:{
-                ap_log_perror(APLOG_MARK, level, 0, r,
-                              "%d:  %s", i, lua_toboolean(L,
-                                                          i) ? "true" :
-                              "false");
+                ap_log_perror(APLOG_MARK, level, 0, r, APLOGNO(03217)
+                              "%d:  %s",
+                              i, lua_toboolean(L, i) ? "true" : "false");
                 break;
             }
         case LUA_TNUMBER:{
-                ap_log_perror(APLOG_MARK, level, 0, r,
+                ap_log_perror(APLOG_MARK, level, 0, r, APLOGNO(03218)
                               "%d:  %g", i, lua_tonumber(L, i));
                 break;
             }
         case LUA_TTABLE:{
-                ap_log_perror(APLOG_MARK, level, 0, r, "%d:  <table>", i);
+                ap_log_perror(APLOG_MARK, level, 0, r, APLOGNO(03219)
+                              "%d:  <table>", i);
                 break;
             }
         case LUA_TTHREAD:{
-                ap_log_perror(APLOG_MARK, level, 0, r, "%d:  <thread>", i);
+                ap_log_perror(APLOG_MARK, level, 0, r, APLOGNO(03220)
+                              "%d:  <thread>", i);
                 break;
             }
         case LUA_TFUNCTION:{
-                ap_log_perror(APLOG_MARK, level, 0, r, "%d:  <function>", i);
+                ap_log_perror(APLOG_MARK, level, 0, r, APLOGNO(03221)
+                              "%d:  <function>", i);
                 break;
             }
         default:{
-                ap_log_perror(APLOG_MARK, level, 0, r,
+                ap_log_perror(APLOG_MARK, level, 0, r, APLOGNO(03222)
                               "%d:  unknown: [%s]", i, lua_typename(L, i));
                 break;
             }
         }
     }
 }
