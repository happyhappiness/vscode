@@ -1352,35 +1352,52 @@ void clientCommand(redisClient *c) {
         sdsfree(o);
     } else if (!strcasecmp(c->argv[1]->ptr,"kill")) {
         /* CLIENT KILL <ip:port>
-         * CLIENT KILL <attrib> <value> */
+         * CLIENT KILL <option> [value] ... <option> [value] */
         char *addr = NULL;
         int type = -1;
         uint64_t id = 0;
-        int killed = 0;
-        int close_this_client = 0;
+        int skipme = 1;
+        int killed = 0, close_this_client = 0;
 
-        /* Parse arguments. */
         if (c->argc == 3) {
+            /* Old style syntax: CLIENT KILL <addr> */
             addr = c->argv[2]->ptr;
-        } else if (c->argc == 4) {
-            if (!strcasecmp(c->argv[2]->ptr,"id")) {
-                long long tmp;
-
-                if (getLongLongFromObjectOrReply(c,c->argv[3],&tmp,NULL)
-                    != REDIS_OK) return;
-                id = tmp;
-            } else if (!strcasecmp(c->argv[2]->ptr,"type")) {
-                type = getClientTypeByName(c->argv[3]->ptr);
-                if (type == -1) {
-                    addReplyErrorFormat(c,"Unknown client type '%s'",
-                        (char*) c->argv[3]->ptr);
+        } else if (c->argc > 3) {
+            int i = 2; /* Next option index. */
+
+            /* New style syntax: parse options. */
+            while(i < c->argc) {
+                int moreargs = c->argc > i+1;
+
+                if (!strcasecmp(c->argv[i]->ptr,"id") && moreargs) {
+                    long long tmp;
+
+                    if (getLongLongFromObjectOrReply(c,c->argv[i+1],&tmp,NULL)
+                        != REDIS_OK) return;
+                    id = tmp;
+                } else if (!strcasecmp(c->argv[i]->ptr,"type") && moreargs) {
+                    type = getClientTypeByName(c->argv[i+1]->ptr);
+                    if (type == -1) {
+                        addReplyErrorFormat(c,"Unknown client type '%s'",
+                            (char*) c->argv[i+1]->ptr);
+                        return;
+                    }
+                } else if (!strcasecmp(c->argv[i]->ptr,"addr") && moreargs) {
+                    addr = c->argv[i+1]->ptr;
+                } else if (!strcasecmp(c->argv[i]->ptr,"skipme") && moreargs) {
+                    if (!strcasecmp(c->argv[i+1]->ptr,"yes")) {
+                        skipme = 1;
+                    } else if (!strcasecmp(c->argv[i+1]->ptr,"no")) {
+                        skipme = 0;
+                    } else {
+                        addReply(c,shared.syntaxerr);
+                        return;
+                    }
+                } else {
+                    addReply(c,shared.syntaxerr);
                     return;
                 }
-            } else if (!strcasecmp(c->argv[2]->ptr,"addr")) {
-                addr = c->argv[3]->ptr;
-            } else {
-                addReply(c,shared.syntaxerr);
-                return;
+                i += 2;
             }
         } else {
             addReply(c,shared.syntaxerr);
@@ -1394,6 +1411,7 @@ void clientCommand(redisClient *c) {
             if (addr && strcmp(getClientPeerId(client),addr) != 0) continue;
             if (type != -1 && getClientType(client) != type) continue;
             if (id != 0 && client->id != id) continue;
+            if (c == client && skipme) continue;
 
             /* Kill it. */
             if (c == client) {