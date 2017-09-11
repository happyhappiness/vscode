@@ -280,6 +280,8 @@ void debugCommand(client *c) {
         blen++; addReplyStatus(c,
         "sdslen <key> -- Show low level SDS string info representing key and value.");
         blen++; addReplyStatus(c,
+        "ziplist <key> -- Show low level info about the ziplist encoding.");
+        blen++; addReplyStatus(c,
         "populate <count> [prefix] -- Create <count> string keys named key:<num>. If a prefix is specified is used instead of the 'key' prefix.");
         blen++; addReplyStatus(c,
         "digest   -- Outputs an hex signature representing the current DB content.");
@@ -418,6 +420,18 @@ void debugCommand(client *c) {
                 (long long) sdsavail(val->ptr),
                 (long long) getStringObjectSdsUsedMemory(val));
         }
+    } else if (!strcasecmp(c->argv[1]->ptr,"ziplist") && c->argc == 3) {
+        robj *o;
+
+        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nokeyerr))
+                == NULL) return;
+
+        if (o->encoding != OBJ_ENCODING_ZIPLIST) {
+            addReplyError(c,"Not an sds encoded string.");
+        } else {
+            ziplistRepr(o->ptr);
+            addReplyStatus(c,"Ziplist structure printed on stdout");
+        }
     } else if (!strcasecmp(c->argv[1]->ptr,"populate") &&
                (c->argc == 3 || c->argc == 4)) {
         long keys, j;