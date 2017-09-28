         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"pending-scripts")) {
         /* SENTINEL PENDING-SCRIPTS */
 
         if (c->argc != 2) goto numargserr;
         sentinelPendingScriptsCommand(c);
+    } else if (!strcasecmp(c->argv[1]->ptr,"monitor")) {
+        /* SENTINEL MONITOR <name> <ip> <port> <quorum> */
+        long quorum, port;
+        char buf[32];
+
+        if (c->argc != 6) goto numargserr;
+        if (getLongFromObjectOrReply(c,c->argv[5],&quorum,"Invalid quorum")
+            != REDIS_OK) return;
+        if (getLongFromObjectOrReply(c,c->argv[4],&port,"Invalid port")
+            != REDIS_OK) return;
+        /* Make sure the IP field is actually a valid IP before passing it
+         * to createSentinelRedisInstance(), otherwise we may trigger a
+         * DNS lookup at runtime. */
+        if (anetResolveIP(NULL,c->argv[3]->ptr,buf,sizeof(buf)) == ANET_ERR) {
+            addReplyError(c,"Invalid IP address specified");
+            return;
+        }
+        if (createSentinelRedisInstance(c->argv[2]->ptr,SRI_MASTER,
+                c->argv[3]->ptr,port,quorum,NULL) == NULL)
+        {
+            switch(errno) {
+            case EBUSY:
+                addReplyError(c,"Duplicated master name");
+                break;
+            case EINVAL:
+                addReplyError(c,"Invalid port number");
+                break;
+            default:
+                addReplyError(c,"Unspecified error adding the instance");
+                break;
+            }
+        } else {
+            sentinelFlushConfig();
+            addReply(c,shared.ok);
+        }
+    } else if (!strcasecmp(c->argv[1]->ptr,"remove")) {
+        /* SENTINEL REMOVE <name> */
+        sentinelRedisInstance *ri;
+
+        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
+            == NULL) return;
+        dictDelete(sentinel.masters,c->argv[2]->ptr);
+        sentinelFlushConfig();
+        addReply(c,shared.ok);
+    } else if (!strcasecmp(c->argv[1]->ptr,"set")) {
+        if (c->argc < 3 || c->argc % 2 == 0) goto numargserr;
+        sentinelSetCommand(c);
     } else {
         addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                                (char*)c->argv[1]->ptr);
     }
     return;
 
 numargserr:
-    addReplyErrorFormat(c,"Wrong number of commands for 'sentinel %s'",
+    addReplyErrorFormat(c,"Wrong number of arguments for 'sentinel %s'",
                           (char*)c->argv[1]->ptr);
 }
 
+/* SENTINEL INFO [section] */
 void sentinelInfoCommand(redisClient *c) {
     char *section = c->argc == 2 ? c->argv[1]->ptr : "default";
     sds info = sdsempty();
     int defsections = !strcasecmp(section,"default");
     int sections = 0;
 
