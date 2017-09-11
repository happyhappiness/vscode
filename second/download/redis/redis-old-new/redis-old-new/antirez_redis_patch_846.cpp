@@ -1346,27 +1346,72 @@ void clientCommand(redisClient *c) {
     redisClient *client;
 
     if (!strcasecmp(c->argv[1]->ptr,"list") && c->argc == 2) {
+        /* CLIENT LIST */
         sds o = getAllClientsInfoString();
         addReplyBulkCBuffer(c,o,sdslen(o));
         sdsfree(o);
-    } else if (!strcasecmp(c->argv[1]->ptr,"kill") && c->argc == 3) {
+    } else if (!strcasecmp(c->argv[1]->ptr,"kill")) {
+        /* CLIENT KILL <ip:port>
+         * CLIENT KILL <attrib> <value> */
+        char *addr = NULL;
+        int type = -1;
+        uint64_t id = 0;
+        int killed = 0;
+
+        /* Parse arguments. */
+        if (c->argc == 3) {
+            addr = c->argv[2]->ptr;
+        } else if (c->argc == 4) {
+            if (!strcasecmp(c->argv[2]->ptr,"id")) {
+                long long tmp;
+
+                if (getLongLongFromObjectOrReply(c,c->argv[3],&tmp,NULL)
+                    != REDIS_OK) return;
+                id = tmp;
+            } else if (!strcasecmp(c->argv[2]->ptr,"type")) {
+                type = getClientTypeByName(c->argv[3]->ptr);
+                if (type == -1) {
+                    addReplyErrorFormat(c,"Unknown client type '%s'",
+                        (char*) c->argv[3]->ptr);
+                    return;
+                }
+            } else if (!strcasecmp(c->argv[2]->ptr,"addr")) {
+                addr = c->argv[3]->ptr;
+            } else {
+                addReply(c,shared.syntaxerr);
+                return;
+            }
+        } else {
+            addReply(c,shared.syntaxerr);
+            return;
+        }
+
+        /* Iterate clients killing all the matching clients. */
         listRewind(server.clients,&li);
         while ((ln = listNext(&li)) != NULL) {
-            char *peerid;
-
             client = listNodeValue(ln);
-            peerid = getClientPeerId(client);
-            if (strcmp(peerid,c->argv[2]->ptr) == 0) {
-                addReply(c,shared.ok);
-                if (c == client) {
-                    client->flags |= REDIS_CLOSE_AFTER_REPLY;
-                } else {
-                    freeClient(client);
-                }
-                return;
+            if (addr && strcmp(getClientPeerId(client),addr) != 0) continue;
+            if (type != -1 && getClientType(client) != type) continue;
+            if (id != 0 && client->id != id) continue;
+
+            /* Kill it. */
+            if (c == client) {
+                client->flags |= REDIS_CLOSE_AFTER_REPLY;
+            } else {
+                freeClient(client);
             }
+            killed++;
+        }
+
+        /* Reply according to old/new format. */
+        if (c->argc == 3) {
+            if (killed == 0)
+                addReplyError(c,"No such client");
+            else
+                addReply(c,shared.ok);
+        } else {
+            addReplyLongLong(c,killed);
         }
-        addReplyError(c,"No such client");
     } else if (!strcasecmp(c->argv[1]->ptr,"setname") && c->argc == 3) {
         int j, len = sdslen(c->argv[2]->ptr);
         char *p = c->argv[2]->ptr;