@@ -320,7 +320,7 @@ void hmsetCommand(redisClient *c) {
 }
 
 void hincrbyCommand(redisClient *c) {
-    long long value, incr;
+    long long value, incr, oldvalue;
     robj *o, *current, *new;
 
     if (getLongLongFromObjectOrReply(c,c->argv[3],&incr,NULL) != REDIS_OK) return;
@@ -336,7 +336,12 @@ void hincrbyCommand(redisClient *c) {
         value = 0;
     }
 
+    oldvalue = value;
     value += incr;
+    if ((incr < 0 && value > oldvalue) || (incr > 0 && value < oldvalue)) {
+        addReplyError(c,"increment or decrement would overflow");
+        return;
+    }
     new = createStringObjectFromLongLong(value);
     hashTypeTryObjectEncoding(o,&c->argv[2],NULL);
     hashTypeSet(o,c->argv[2],new);