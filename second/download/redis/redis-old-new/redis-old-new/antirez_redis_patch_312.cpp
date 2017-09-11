@@ -1911,11 +1911,11 @@ sds ldbCatStackValue(sds s, lua_State *lua, int idx) {
         else if (t == LUA_TUSERDATA) typename = "userdata";
         else if (t == LUA_TTHREAD) typename = "thread";
         else if (t == LUA_TLIGHTUSERDATA) typename = "light-userdata";
-        s = sdscatprintf(s,"%s@%p",typename,p);
+        s = sdscatprintf(s,"\"%s@%p\"",typename,p);
         }
         break;
     default:
-        s = sdscat(s,"<unknown-lua-type>");
+        s = sdscat(s,"\"<unknown-lua-type>\"");
         break;
     }
     return s;