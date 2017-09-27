         case LUA_TFUNCTION:{
                 ap_log_perror(APLOG_MARK, level, 0, r, "%d:  <function>", i);
                 break;
             }
         default:{
                 ap_log_perror(APLOG_MARK, level, 0, r,
-                              "%d:  unkown: [%s]", i, lua_typename(L, i));
+                              "%d:  unknown: [%s]", i, lua_typename(L, i));
                 break;
             }
         }
     }
 }
 #endif
