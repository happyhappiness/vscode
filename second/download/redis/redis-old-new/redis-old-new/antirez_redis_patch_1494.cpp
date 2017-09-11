@@ -181,21 +181,38 @@ sds catAppendOnlyGenericCommand(sds dst, int argc, robj **argv) {
     return dst;
 }
 
-sds catAppendOnlyExpireAtCommand(sds buf, robj *key, robj *seconds) {
-    int argc = 3;
-    long when;
+/* Create the sds representation of an PEXPIREAT command, using
+ * 'seconds' as time to live and 'cmd' to understand what command
+ * we are translating into a PEXPIREAT.
+ *
+ * This command is used in order to translate EXPIRE and PEXPIRE commands
+ * into PEXPIREAT command so that we retain precision in the append only
+ * file, and the time is always absolute and not relative. */
+sds catAppendOnlyExpireAtCommand(sds buf, struct redisCommand *cmd, robj *key, robj *seconds) {
+    long long when;
     robj *argv[3];
 
     /* Make sure we can use strtol */
     seconds = getDecodedObject(seconds);
-    when = time(NULL)+strtol(seconds->ptr,NULL,10);
+    when = strtoll(seconds->ptr,NULL,10);
+    /* Convert argument into milliseconds for EXPIRE, SETEX, EXPIREAT */
+    if (cmd->proc == expireCommand || cmd->proc == setexCommand ||
+        cmd->proc == expireatCommand)
+    {
+        when *= 1000;
+    }
+    /* Convert into absolute time for EXPIRE, PEXPIRE, SETEX, PSETEX */
+    if (cmd->proc == expireCommand || cmd->proc == pexpireCommand ||
+        cmd->proc == setexCommand || cmd->proc == psetexCommand)
+    {
+        when += mstime();
+    }
     decrRefCount(seconds);
 
-    argv[0] = createStringObject("EXPIREAT",8);
+    argv[0] = createStringObject("PEXPIREAT",9);
     argv[1] = key;
-    argv[2] = createObject(REDIS_STRING,
-        sdscatprintf(sdsempty(),"%ld",when));
-    buf = catAppendOnlyGenericCommand(buf, argc, argv);
+    argv[2] = createStringObjectFromLongLong(when);
+    buf = catAppendOnlyGenericCommand(buf, 3, argv);
     decrRefCount(argv[0]);
     decrRefCount(argv[2]);
     return buf;
@@ -216,18 +233,22 @@ void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int a
         server.appendseldb = dictid;
     }
 
-    if (cmd->proc == expireCommand) {
-        /* Translate EXPIRE into EXPIREAT */
-        buf = catAppendOnlyExpireAtCommand(buf,argv[1],argv[2]);
-    } else if (cmd->proc == setexCommand) {
-        /* Translate SETEX to SET and EXPIREAT */
+    if (cmd->proc == expireCommand || cmd->proc == pexpireCommand ||
+        cmd->proc == expireatCommand) {
+        /* Translate EXPIRE/PEXPIRE/EXPIREAT into PEXPIREAT */
+        buf = catAppendOnlyExpireAtCommand(buf,cmd,argv[1],argv[2]);
+    } else if (cmd->proc == setexCommand || cmd->proc == psetexCommand) {
+        /* Translate SETEX/PSETEX to SET and PEXPIREAT */
         tmpargv[0] = createStringObject("SET",3);
         tmpargv[1] = argv[1];
         tmpargv[2] = argv[3];
         buf = catAppendOnlyGenericCommand(buf,3,tmpargv);
         decrRefCount(tmpargv[0]);
-        buf = catAppendOnlyExpireAtCommand(buf,argv[1],argv[2]);
+        buf = catAppendOnlyExpireAtCommand(buf,cmd,argv[1],argv[2]);
     } else {
+        /* All the other commands don't need translation or need the
+         * same translation already operated in the command vector
+         * for the replication itself. */
         buf = catAppendOnlyGenericCommand(buf,argc,argv);
     }
 
@@ -608,13 +629,12 @@ int rewriteAppendOnlyFile(char *filename) {
             }
             /* Save the expire time */
             if (expiretime != -1) {
-                char cmd[]="*4\r\n$8\r\nEXPIREAT\r\n";
+                char cmd[]="*3\r\n$9\r\nPEXPIREAT\r\n";
                 /* If this key is already expired skip it */
                 if (expiretime < now) continue;
                 if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
                 if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
                 if (rioWriteBulkLongLong(&aof,expiretime) == 0) goto werr;
-                if (rioWriteBulkString(&aof,"ms",2) == 0) goto werr;
             }
         }
         dictReleaseIterator(di);