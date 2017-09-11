@@ -2172,11 +2172,12 @@ void ldbTrace(lua_State *lua) {
 
     while(lua_getstack(lua,level,&ar)) {
         lua_getinfo(lua,"Snl",&ar);
-        if(strstr(ar.short_src,"user_script") == NULL) continue;
-        ldbLog(sdscatprintf(sdsempty(),"%s %s:",
-            (level == 0) ? "In" : "From",
-            ar.name ? ar.name : "top level"));
-        ldbLogSourceLine(ar.currentline);
+        if(strstr(ar.short_src,"user_script") != NULL) {
+            ldbLog(sdscatprintf(sdsempty(),"%s %s:",
+                (level == 0) ? "In" : "From",
+                ar.name ? ar.name : "top level"));
+            ldbLogSourceLine(ar.currentline);
+        }
         level++;
     }
     if (level == 0) {