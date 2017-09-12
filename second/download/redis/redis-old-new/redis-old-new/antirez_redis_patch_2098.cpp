@@ -8068,9 +8068,41 @@ static void flushAppendOnlyFile(void) {
     }
 }
 
+static sds catAppendOnlyGenericCommand(sds buf, int argc, robj **argv) {
+    int j;
+    buf = sdscatprintf(buf,"*%d\r\n",argc);
+    for (j = 0; j < argc; j++) {
+        robj *o = getDecodedObject(argv[j]);
+        buf = sdscatprintf(buf,"$%lu\r\n",(unsigned long)sdslen(o->ptr));
+        buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
+        buf = sdscatlen(buf,"\r\n",2);
+        decrRefCount(o);
+    }
+    return buf;
+}
+
+static sds catAppendOnlyExpireAtCommand(sds buf, robj *key, robj *seconds) {
+    int argc = 3;
+    long when;
+    robj *argv[3];
+
+    /* Make sure we can use strtol */
+    seconds = getDecodedObject(seconds);
+    when = time(NULL)+strtol(seconds->ptr,NULL,10);
+    decrRefCount(seconds);
+
+    argv[0] = createStringObject("EXPIREAT",8);
+    argv[1] = key;
+    argv[2] = createObject(REDIS_STRING,
+        sdscatprintf(sdsempty(),"%ld",when));
+    buf = catAppendOnlyGenericCommand(buf, argc, argv);
+    decrRefCount(argv[0]);
+    decrRefCount(argv[2]);
+    return buf;
+}
+
 static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc) {
     sds buf = sdsempty();
-    int j;
     robj *tmpargv[3];
 
     /* The DB this command was targetting is not the same as the last command
@@ -8084,36 +8116,19 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
         server.appendseldb = dictid;
     }
 
-    /* "Fix" the argv vector if the command is EXPIRE. We want to translate
-     * EXPIREs into EXPIREATs calls */
     if (cmd->proc == expireCommand) {
-        long when;
-
-        tmpargv[0] = createStringObject("EXPIREAT",8);
+        /* Translate EXPIRE into EXPIREAT */
+        buf = catAppendOnlyExpireAtCommand(buf,argv[1],argv[2]);
+    } else if (cmd->proc == setexCommand) {
+        /* Translate SETEX to SET and EXPIREAT */
+        tmpargv[0] = createStringObject("SET",3);
         tmpargv[1] = argv[1];
-        incrRefCount(argv[1]);
-        when = time(NULL)+strtol(argv[2]->ptr,NULL,10);
-        tmpargv[2] = createObject(REDIS_STRING,
-            sdscatprintf(sdsempty(),"%ld",when));
-        argv = tmpargv;
-    }
-
-    /* Append the actual command */
-    buf = sdscatprintf(buf,"*%d\r\n",argc);
-    for (j = 0; j < argc; j++) {
-        robj *o = argv[j];
-
-        o = getDecodedObject(o);
-        buf = sdscatprintf(buf,"$%lu\r\n",(unsigned long)sdslen(o->ptr));
-        buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
-        buf = sdscatlen(buf,"\r\n",2);
-        decrRefCount(o);
-    }
-
-    /* Free the objects from the modified argv for EXPIREAT */
-    if (cmd->proc == expireCommand) {
-        for (j = 0; j < 3; j++)
-            decrRefCount(argv[j]);
+        tmpargv[2] = argv[3];
+        buf = catAppendOnlyGenericCommand(buf,3,tmpargv);
+        decrRefCount(tmpargv[0]);
+        buf = catAppendOnlyExpireAtCommand(buf,argv[1],argv[2]);
+    } else {
+        buf = catAppendOnlyGenericCommand(buf,argc,argv);
     }
 
     /* Append to the AOF buffer. This will be flushed on disk just before