@@ -282,7 +282,7 @@ void debugCommand(client *c) {
         blen++; addReplyStatus(c,
         "ziplist <key> -- Show low level info about the ziplist encoding.");
         blen++; addReplyStatus(c,
-        "populate <count> [prefix] -- Create <count> string keys named key:<num>. If a prefix is specified is used instead of the 'key' prefix.");
+        "populate <count> [prefix] [size] -- Create <count> string keys named key:<num>. If a prefix is specified is used instead of the 'key' prefix.");
         blen++; addReplyStatus(c,
         "digest   -- Outputs an hex signature representing the current DB content.");
         blen++; addReplyStatus(c,
@@ -433,7 +433,7 @@ void debugCommand(client *c) {
             addReplyStatus(c,"Ziplist structure printed on stdout");
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"populate") &&
-               (c->argc == 3 || c->argc == 4)) {
+               c->argc >= 3 && c->argc <= 5) {
         long keys, j;
         robj *key, *val;
         char buf[128];
@@ -442,15 +442,24 @@ void debugCommand(client *c) {
             return;
         dictExpand(c->db->dict,keys);
         for (j = 0; j < keys; j++) {
+            long valsize = 0;
             snprintf(buf,sizeof(buf),"%s:%lu",
                 (c->argc == 3) ? "key" : (char*)c->argv[3]->ptr, j);
             key = createStringObject(buf,strlen(buf));
+            if (c->argc == 5)
+                if (getLongFromObjectOrReply(c, c->argv[4], &valsize, NULL) != C_OK)
+                    return;
             if (lookupKeyWrite(c->db,key) != NULL) {
                 decrRefCount(key);
                 continue;
             }
             snprintf(buf,sizeof(buf),"value:%lu",j);
-            val = createStringObject(buf,strlen(buf));
+            if (valsize==0)
+                val = createStringObject(buf,strlen(buf));
+            else {
+                val = createStringObject(NULL,valsize);
+                memset(val->ptr, 0, valsize);
+            }
             dbAdd(c->db,key,val);
             signalModifiedKey(c->db,key);
             decrRefCount(key);