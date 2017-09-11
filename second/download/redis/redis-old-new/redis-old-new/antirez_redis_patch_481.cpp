@@ -57,12 +57,12 @@ slowlogEntry *slowlogCreateEntry(robj **argv, int argc, long long duration) {
          * at SLOWLOG_ENTRY_MAX_ARGC, but use the last argument to specify
          * how many remaining arguments there were in the original command. */
         if (slargc != argc && j == slargc-1) {
-            se->argv[j] = createObject(REDIS_STRING,
+            se->argv[j] = createObject(OBJ_STRING,
                 sdscatprintf(sdsempty(),"... (%d more arguments)",
                 argc-slargc+1));
         } else {
             /* Trim too long strings as well... */
-            if (argv[j]->type == REDIS_STRING &&
+            if (argv[j]->type == OBJ_STRING &&
                 sdsEncodedObject(argv[j]) &&
                 sdslen(argv[j]->ptr) > SLOWLOG_ENTRY_MAX_STRING)
             {
@@ -71,7 +71,7 @@ slowlogEntry *slowlogCreateEntry(robj **argv, int argc, long long duration) {
                 s = sdscatprintf(s,"... (%lu more bytes)",
                     (unsigned long)
                     sdslen(argv[j]->ptr) - SLOWLOG_ENTRY_MAX_STRING);
-                se->argv[j] = createObject(REDIS_STRING,s);
+                se->argv[j] = createObject(OBJ_STRING,s);
             } else {
                 se->argv[j] = argv[j];
                 incrRefCount(argv[j]);