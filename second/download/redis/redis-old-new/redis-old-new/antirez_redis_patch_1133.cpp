@@ -2344,7 +2344,7 @@ sds genRedisInfoString(char *section) {
 
                 info = sdscatprintf(info,
                     "slave%d:ip=%s,port=%d,state=%s,"
-                    "repl_offset=%lld,lag=%ld\r\n",
+                    "offset=%lld,lag=%ld\r\n",
                     slaveid,ip,slave->slave_listening_port,state,
                     slave->repl_ack_off, lag);
                 slaveid++;