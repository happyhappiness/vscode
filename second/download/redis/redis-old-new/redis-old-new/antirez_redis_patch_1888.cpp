@@ -889,79 +889,6 @@ void call(redisClient *c, struct redisCommand *cmd) {
 int processCommand(redisClient *c) {
     struct redisCommand *cmd;
 
-    /* Handle the multi bulk command type. This is an alternative protocol
-     * supported by Redis in order to receive commands that are composed of
-     * multiple binary-safe "bulk" arguments. The latency of processing is
-     * a bit higher but this allows things like multi-sets, so if this
-     * protocol is used only for MSET and similar commands this is a big win. */
-    if (c->multibulk == 0 && c->argc == 1 && ((char*)(c->argv[0]->ptr))[0] == '*') {
-        c->multibulk = atoi(((char*)c->argv[0]->ptr)+1);
-        if (c->multibulk <= 0) {
-            resetClient(c);
-            return 1;
-        } else {
-            decrRefCount(c->argv[c->argc-1]);
-            c->argc--;
-            return 1;
-        }
-    } else if (c->multibulk) {
-        if (c->bulklen == -1) {
-            if (((char*)c->argv[0]->ptr)[0] != '$') {
-                addReplyError(c,"multi bulk protocol error");
-                resetClient(c);
-                return 1;
-            } else {
-                char *eptr;
-                long bulklen = strtol(((char*)c->argv[0]->ptr)+1,&eptr,10);
-                int perr = eptr[0] != '\0';
-
-                decrRefCount(c->argv[0]);
-                if (perr || bulklen == LONG_MIN || bulklen == LONG_MAX ||
-                    bulklen < 0 || bulklen > 1024*1024*1024)
-                {
-                    c->argc--;
-                    addReplyError(c,"invalid bulk write count");
-                    resetClient(c);
-                    return 1;
-                }
-                c->argc--;
-                c->bulklen = bulklen+2; /* add two bytes for CR+LF */
-                return 1;
-            }
-        } else {
-            c->mbargv = zrealloc(c->mbargv,(sizeof(robj*))*(c->mbargc+1));
-            c->mbargv[c->mbargc] = c->argv[0];
-            c->mbargc++;
-            c->argc--;
-            c->multibulk--;
-            if (c->multibulk == 0) {
-                robj **auxargv;
-                int auxargc;
-
-                /* Here we need to swap the multi-bulk argc/argv with the
-                 * normal argc/argv of the client structure. */
-                auxargv = c->argv;
-                c->argv = c->mbargv;
-                c->mbargv = auxargv;
-
-                auxargc = c->argc;
-                c->argc = c->mbargc;
-                c->mbargc = auxargc;
-
-                /* We need to set bulklen to something different than -1
-                 * in order for the code below to process the command without
-                 * to try to read the last argument of a bulk command as
-                 * a special argument. */
-                c->bulklen = 0;
-                /* continue below and process the command */
-            } else {
-                c->bulklen = -1;
-                return 1;
-            }
-        }
-    }
-    /* -- end of multi bulk commands processing -- */
-
     /* The QUIT command is handled separately. Normal command procs will
      * go through checking for replication and QUIT will cause trouble
      * when FORCE_REPLICATION is enabled and would be implemented in
@@ -970,7 +897,7 @@ int processCommand(redisClient *c) {
     if (!strcasecmp(c->argv[0]->ptr,"quit")) {
         c->flags |= REDIS_QUIT;
         addReply(c,shared.ok);
-        return 0;
+        return REDIS_ERR;
     }
 
     /* Now lookup the command and check ASAP about trivial error conditions
@@ -979,55 +906,22 @@ int processCommand(redisClient *c) {
     if (!cmd) {
         addReplyErrorFormat(c,"unknown command '%s'",
             (char*)c->argv[0]->ptr);
-        resetClient(c);
-        return 1;
+        return REDIS_OK;
     } else if ((cmd->arity > 0 && cmd->arity != c->argc) ||
                (c->argc < -cmd->arity)) {
         addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
             cmd->name);
-        resetClient(c);
-        return 1;
-    } else if (cmd->flags & REDIS_CMD_BULK && c->bulklen == -1) {
-        /* This is a bulk command, we have to read the last argument yet. */
-        char *eptr;
-        long bulklen = strtol(c->argv[c->argc-1]->ptr,&eptr,10);
-        int perr = eptr[0] != '\0';
-
-        decrRefCount(c->argv[c->argc-1]);
-        if (perr || bulklen == LONG_MAX || bulklen == LONG_MIN ||
-            bulklen < 0 || bulklen > 1024*1024*1024)
-        {
-            c->argc--;
-            addReplyError(c,"invalid bulk write count");
-            resetClient(c);
-            return 1;
-        }
-        c->argc--;
-        c->bulklen = bulklen+2; /* add two bytes for CR+LF */
-        /* It is possible that the bulk read is already in the
-         * buffer. Check this condition and handle it accordingly.
-         * This is just a fast path, alternative to call processInputBuffer().
-         * It's a good idea since the code is small and this condition
-         * happens most of the times. */
-        if ((signed)sdslen(c->querybuf) >= c->bulklen) {
-            c->argv[c->argc] = createStringObject(c->querybuf,c->bulklen-2);
-            c->argc++;
-            c->querybuf = sdsrange(c->querybuf,c->bulklen,-1);
-        } else {
-            /* Otherwise return... there is to read the last argument
-             * from the socket. */
-            return 1;
-        }
+        return REDIS_OK;
     }
+
     /* Let's try to encode the bulk object to save space. */
     if (cmd->flags & REDIS_CMD_BULK)
         c->argv[c->argc-1] = tryObjectEncoding(c->argv[c->argc-1]);
 
     /* Check if the user is authenticated */
     if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
         addReplyError(c,"operation not permitted");
-        resetClient(c);
-        return 1;
+        return REDIS_OK;
     }
 
     /* Handle the maxmemory directive.
@@ -1040,8 +934,7 @@ int processCommand(redisClient *c) {
         zmalloc_used_memory() > server.maxmemory)
     {
         addReplyError(c,"command not allowed when used memory > 'maxmemory'");
-        resetClient(c);
-        return 1;
+        return REDIS_OK;
     }
 
     /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */
@@ -1050,8 +943,7 @@ int processCommand(redisClient *c) {
         cmd->proc != subscribeCommand && cmd->proc != unsubscribeCommand &&
         cmd->proc != psubscribeCommand && cmd->proc != punsubscribeCommand) {
         addReplyError(c,"only (P)SUBSCRIBE / (P)UNSUBSCRIBE / QUIT allowed in this context");
-        resetClient(c);
-        return 1;
+        return REDIS_OK;
     }
 
     /* Exec the command */
@@ -1066,10 +958,7 @@ int processCommand(redisClient *c) {
             blockClientOnSwappedKeys(c,cmd)) return 1;
         call(c,cmd);
     }
-
-    /* Prepare the client for the next command */
-    resetClient(c);
-    return 1;
+    return REDIS_OK;
 }
 
 /*================================== Shutdown =============================== */