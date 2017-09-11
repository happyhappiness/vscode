@@ -344,11 +344,12 @@ void incrDecrCommand(redisClient *c, long long incr) {
     if (getLongLongFromObjectOrReply(c,o,&value,NULL) != REDIS_OK) return;
 
     oldvalue = value;
-    value += incr;
-    if ((incr < 0 && value > oldvalue) || (incr > 0 && value < oldvalue)) {
+    if ((incr < 0 && oldvalue < 0 && incr < (LLONG_MIN-oldvalue)) ||
+        (incr > 0 && oldvalue > 0 && incr > (LLONG_MAX-oldvalue))) {
         addReplyError(c,"increment or decrement would overflow");
         return;
     }
+    value += incr;
     new = createStringObjectFromLongLong(value);
     if (o)
         dbOverwrite(c->db,c->argv[1],new);