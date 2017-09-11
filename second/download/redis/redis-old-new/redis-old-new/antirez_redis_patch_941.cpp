@@ -648,7 +648,7 @@ char *strEncoding(int encoding) {
     }
 }
 
-/* Given an object returns the min number of seconds the object was never
+/* Given an object returns the min number of milliseconds the object was never
  * requested, using an approximated LRU algorithm. */
 unsigned long long estimateObjectIdleTime(robj *o) {
     unsigned long long lruclock = LRU_CLOCK();
@@ -692,7 +692,7 @@ void objectCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[1]->ptr,"idletime") && c->argc == 3) {
         if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
                 == NULL) return;
-        addReplyLongLong(c,estimateObjectIdleTime(o));
+        addReplyLongLong(c,estimateObjectIdleTime(o)/1000);
     } else {
         addReplyError(c,"Syntax error. Try OBJECT (refcount|encoding|idletime)");
     }