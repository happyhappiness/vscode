@@ -2797,12 +2797,10 @@ void sentinelCommand(redisClient *c) {
         dictType copy_keeper = instancesDictType;
         copy_keeper.valDestructor = NULL;
         dict *masters_local = NULL;
-        int needs_cleanup = 0;
         if (c->argc == 2) {
             masters_local = sentinel.masters;
         } else {
             masters_local = dictCreate(&copy_keeper, NULL);
-            needs_cleanup = 1;
 
             for (int i = 2; i < c->argc; i++) {
                 sentinelRedisInstance *ri;
@@ -2841,7 +2839,7 @@ void sentinelCommand(redisClient *c) {
             dictReleaseIterator(sdi);
         }
         dictReleaseIterator(di);
-        if (needs_cleanup) dictRelease(masters_local);
+        if (masters_local != sentinel.masters) dictRelease(masters_local);
     } else {
         addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                                (char*)c->argv[1]->ptr);