@@ -337,11 +337,12 @@ void hincrbyCommand(redisClient *c) {
     }
 
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
     hashTypeTryObjectEncoding(o,&c->argv[2],NULL);
     hashTypeSet(o,c->argv[2],new);