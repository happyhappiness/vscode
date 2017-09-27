     if (rv == APR_SUCCESS) {
         unsigned char opcode = prelude[0];
         unsigned char len = prelude[1];
         unsigned char mask = len >> 7;
         if (mask) len -= 128;
         plen = len;
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, 
-                        "Websocket: Got PONG opcode: %x", opcode);
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03015) 
+                      "Websocket: Got PONG opcode: %x", opcode);
         if (opcode == 0x8A) {
             lua_pushboolean(L, 1);
         }
         else {
             lua_pushboolean(L, 0);
         }
         if (plen > 0) {
             ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, 
-                        "Websocket: Reading %" APR_SIZE_T_FMT " bytes of PONG", plen);
+                          "Websocket: Reading %" APR_SIZE_T_FMT " bytes of PONG", plen);
             return 1;
         }
         if (mask) {
             plen = 2;
             apr_socket_recv(sock, prelude, &plen);
             plen = 2;
