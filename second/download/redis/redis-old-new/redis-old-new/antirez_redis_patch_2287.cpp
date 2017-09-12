@@ -1036,7 +1036,7 @@ static void initServerConfig() {
     server.glueoutputbuf = 1;
     server.daemonize = 0;
     server.appendonly = 0;
-    server.appendfsync = APPENDFSYNC_NO;
+    server.appendfsync = APPENDFSYNC_ALWAYS;
     server.lastfsync = time(NULL);
     server.appendfd = -1;
     server.appendseldb = -1; /* Make sure the first time will not match */
@@ -1672,6 +1672,7 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
     int j;
     ssize_t nwritten;
     time_t now;
+    robj *tmpargv[3];
 
     /* The DB this command was targetting is not the same as the last command
      * we appendend. To issue a SELECT command is needed. */
@@ -1683,6 +1684,21 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
             strlen(seldb),seldb);
         server.appendseldb = dictid;
     }
+
+    /* "Fix" the argv vector if the command is EXPIRE. We want to translate
+     * EXPIREs into EXPIREATs calls */
+    if (cmd->proc == expireCommand) {
+        long when;
+
+        tmpargv[0] = createStringObject("EXPIREAT",8);
+        tmpargv[1] = argv[1];
+        incrRefCount(argv[1]);
+        when = time(NULL)+strtol(argv[2]->ptr,NULL,10);
+        tmpargv[2] = createObject(REDIS_STRING,
+            sdscatprintf(sdsempty(),"%ld",when));
+        argv = tmpargv;
+    }
+
     /* Append the actual command */
     buf = sdscatprintf(buf,"*%d\r\n",argc);
     for (j = 0; j < argc; j++) {
@@ -1696,6 +1712,13 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
         if (o != argv[j])
             decrRefCount(o);
     }
+
+    /* Free the objects from the modified argv for EXPIREAT */
+    if (cmd->proc == expireCommand) {
+        for (j = 0; j < 3; j++)
+            decrRefCount(argv[j]);
+    }
+
     /* We want to perform a single write. This should be guaranteed atomic
      * at least if the filesystem we are writing is a real physical one.
      * While this will save us against the server being killed I don't think
@@ -5450,6 +5473,7 @@ static struct redisFunctionSym symsTable[] = {
 {"zremCommand",(unsigned long)zremCommand},
 {"rdbSaveDoubleValue",(unsigned long)rdbSaveDoubleValue},
 {"rdbLoadDoubleValue",(unsigned long)rdbLoadDoubleValue},
+{"feedAppendOnlyFile",(unsigned long)feedAppendOnlyFile},
 {NULL,0}
 };
 