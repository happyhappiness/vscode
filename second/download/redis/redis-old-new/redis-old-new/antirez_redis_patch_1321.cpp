@@ -16,13 +16,36 @@
  * this function. */
 slowlogEntry *slowlogCreateEntry(robj **argv, int argc, long long duration) {
     slowlogEntry *se = zmalloc(sizeof(*se));
-    int j;
+    int j, slargc = argc;
+
+    if (slargc > SLOWLOG_ENTRY_MAX_ARGC) slargc = SLOWLOG_ENTRY_MAX_ARGC;
+    se->argc = slargc;
+    se->argv = zmalloc(sizeof(robj*)*slargc);
+    for (j = 0; j < slargc; j++) {
+        /* Logging too many arguments is a useless memory waste, so we stop
+         * at SLOWLOG_ENTRY_MAX_ARGC, but use the last argument to specify
+         * how many remaining arguments there were in the original command. */
+        if (slargc != argc && j == slargc-1) {
+            se->argv[j] = createObject(REDIS_STRING,
+                sdscatprintf(sdsempty(),"... (%d more arguments)",
+                argc-slargc+1));
+        } else {
+            /* Trim too long strings as well... */
+            if (argv[j]->type == REDIS_STRING &&
+                argv[j]->encoding == REDIS_ENCODING_RAW &&
+                sdslen(argv[j]->ptr) > SLOWLOG_ENTRY_MAX_STRING)
+            {
+                sds s = sdsnewlen(argv[j]->ptr, SLOWLOG_ENTRY_MAX_STRING);
 
-    se->argc = argc;
-    se->argv = zmalloc(sizeof(robj*)*argc);
-    for (j = 0; j < argc; j++) {
-        se->argv[j] = argv[j];
-        incrRefCount(argv[j]);
+                s = sdscatprintf(s,"... (%lu more bytes)",
+                    (unsigned long)
+                    sdslen(argv[j]->ptr) - SLOWLOG_ENTRY_MAX_STRING);
+                se->argv[j] = createObject(REDIS_STRING,s);
+            } else {
+                se->argv[j] = argv[j];
+                incrRefCount(argv[j]);
+            }
+        }
     }
     se->time = time(NULL);
     se->duration = duration;