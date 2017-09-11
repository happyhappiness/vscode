@@ -2323,6 +2323,7 @@ sds genRedisInfoString(char *section) {
                 char *state = NULL;
                 char ip[32];
                 int port;
+                long lag = 0;
 
                 if (anetPeerToString(slave->fd,ip,&port) == -1) continue;
                 switch(slave->replstate) {
@@ -2338,9 +2339,14 @@ sds genRedisInfoString(char *section) {
                     break;
                 }
                 if (state == NULL) continue;
-                info = sdscatprintf(info,"slave%d:%s,%d,%s,%lld\r\n",
+                if (slave->replstate == REDIS_REPL_ONLINE)
+                    lag = time(NULL) - slave->repl_ack_time;
+
+                info = sdscatprintf(info,
+                    "slave%d:ip=%s,port=%d,state=%s,"
+                    "repl_offset=%lld,lag=%ld\r\n",
                     slaveid,ip,slave->slave_listening_port,state,
-                    slave->repl_ack_off);
+                    slave->repl_ack_off, lag);
                 slaveid++;
             }
         }