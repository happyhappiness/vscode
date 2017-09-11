@@ -121,17 +121,17 @@ int longLatFromMember(robj *zobj, robj *member, double *xy) {
 double extractUnitOrReply(redisClient *c, robj *unit) {
     char *u = unit->ptr;
 
-    if (!strcmp(u, "m") || !strncmp(u, "meter", 5)) {
+    if (!strcmp(u, "m")) {
         return 1;
-    } else if (!strcmp(u, "ft") || !strncmp(u, "feet", 4)) {
+    } else if (!strcmp(u, "km")) {
+        return 1000;
+    } else if (!strcmp(u, "ft")) {
         return 0.3048;
-    } else if (!strcmp(u, "mi") || !strncmp(u, "mile", 4)) {
+    } else if (!strcmp(u, "mi")) {
         return 1609.34;
-    } else if (!strcmp(u, "km") || !strncmp(u, "kilometer", 9)) {
-        return 1000;
     } else {
-        addReplyError(c, "unsupported unit provided. please use meters (m), "
-                         "kilometers (km), miles (mi), or feet (ft)");
+        addReplyError(c,
+            "unsupported unit provided. please use m, km, ft, mi");
         return -1;
     }
 }