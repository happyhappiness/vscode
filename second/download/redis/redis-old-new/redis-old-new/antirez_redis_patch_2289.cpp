@@ -1660,6 +1660,7 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
         snprintf(seldb,sizeof(seldb),"%d",dictid);
         buf = sdscatprintf(buf,"*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
             strlen(seldb),seldb);
+        server.appendseldb = dictid;
     }
     /* Append the actual command */
     buf = sdscatprintf(buf,"*%d\r\n",argc);