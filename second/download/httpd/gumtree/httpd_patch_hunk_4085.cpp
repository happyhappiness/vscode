     if (lua_isboolean(L, 3)) {
         raw = lua_toboolean(L, 3);
     }
     string = lua_tolstring(L, 2, &len);
     
     if (raw != 1) {
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, 
-                        "Websocket: Writing framed message to client");
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03013) 
+                      "Websocket: Writing framed message to client");
         
         prelude = 0x81; /* text frame, FIN */
         ap_rputc(prelude, r);
         if (len < 126) {
             ap_rputc(len, r);
         } 
