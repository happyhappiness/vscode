@@ -337,11 +337,21 @@ void incrDecrCommand(redisClient *c, long long incr) {
         return;
     }
     value += incr;
-    new = createStringObjectFromLongLong(value);
-    if (o)
-        dbOverwrite(c->db,c->argv[1],new);
-    else
-        dbAdd(c->db,c->argv[1],new);
+
+    if (o && o->refcount == 1 && o->encoding == REDIS_ENCODING_INT &&
+        (value < 0 || value >= REDIS_SHARED_INTEGERS) &&
+        value >= LONG_MIN && value <= LONG_MAX)
+    {
+        new = o;
+        o->ptr = (void*)((long)value);
+    } else {
+        new = createStringObjectFromLongLong(value);
+        if (o) {
+            dbOverwrite(c->db,c->argv[1],new);
+        } else {
+            dbAdd(c->db,c->argv[1],new);
+        }
+    }
     signalModifiedKey(c->db,c->argv[1]);
     notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"incrby",c->argv[1],c->db->id);
     server.dirty++;