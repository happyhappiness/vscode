@@ -215,6 +215,7 @@ struct redisCommand redisCommandTable[] = {
     {"exec",execCommand,1,"s",0,NULL,0,0,0,0,0},
     {"discard",discardCommand,1,"rs",0,NULL,0,0,0,0,0},
     {"sync",syncCommand,1,"ars",0,NULL,0,0,0,0,0},
+    {"replconf",replconfCommand,-1,"ars",0,NULL,0,0,0,0,0},
     {"flushdb",flushdbCommand,1,"w",0,NULL,0,0,0,0,0},
     {"flushall",flushallCommand,1,"w",0,NULL,0,0,0,0,0},
     {"sort",sortCommand,-2,"wmS",0,NULL,1,1,1,0,0},
@@ -2119,7 +2120,7 @@ sds genRedisInfoString(char *section) {
                 }
                 if (state == NULL) continue;
                 info = sdscatprintf(info,"slave%d:%s,%d,%s\r\n",
-                    slaveid,ip,port,state);
+                    slaveid,ip,slave->slave_listening_port,state);
                 slaveid++;
             }
         }