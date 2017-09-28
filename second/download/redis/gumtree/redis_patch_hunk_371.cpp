             dictDelete(server.migrate_cached_sockets,dictGetKey(de));
         }
     }
     dictReleaseIterator(di);
 }
 
-/* MIGRATE host port key dbid timeout [COPY | REPLACE] */
+/* MIGRATE host port key dbid timeout [COPY | REPLACE]
+ *
+ * On in the multiple keys form:
+ *
+ * MIGRATE host port "" dbid timeout [COPY | REPLACE] KEYS key1 key2 ... keyN */
 void migrateCommand(redisClient *c) {
     migrateCachedSocket *cs;
     int copy, replace, j;
     long timeout;
     long dbid;
     long long ttl, expireat;
-    robj *o;
+    robj **ov = zmalloc(sizeof(robj*)); /* Objects to migrate. */
+    robj **kv = zmalloc(sizeof(robj*)); /* Key names. */
     rio cmd, payload;
     int retry_num = 0;
+    int write_error = 0;
+
+    /* To support the KEYS option we need the following additional state. */
+    int first_key = 3; /* Argument index of the first key. */
+    int num_keys = 1;  /* By default only migrate the 'key' argument. */
 
-try_again:
     /* Initialization */
     copy = 0;
     replace = 0;
     ttl = 0;
 
     /* Parse additional options */
     for (j = 6; j < c->argc; j++) {
         if (!strcasecmp(c->argv[j]->ptr,"copy")) {
             copy = 1;
         } else if (!strcasecmp(c->argv[j]->ptr,"replace")) {
             replace = 1;
+        } else if (!strcasecmp(c->argv[j]->ptr,"keys")) {
+            if (sdslen(c->argv[3]->ptr) != 0) {
+                addReplyError(c,
+                    "When using MIGRATE KEYS option, the key argument"
+                    " must be set to the empty string");
+                zfree(ov); zfree(kv);
+                return;
+            }
+            first_key = j+1;
+            num_keys = c->argc - j - 1;
+            ov = zrealloc(ov,sizeof(robj*)*num_keys);
+            kv = zrealloc(kv,sizeof(robj*)*num_keys);
+            break; /* All the remaining args are keys. */
         } else {
             addReply(c,shared.syntaxerr);
             return;
         }
     }
 
