@@ -156,9 +156,13 @@ double extractDistanceOrReply(client *c, robj **argv,
         return -1;
     }
 
+    if (distance < 0) {
+        addReplyError(c,"radius cannot be negative");
+        return -1;
+    }
+    
     double to_meters = extractUnitOrReply(c,argv[1]);
     if (to_meters < 0) {
-        addReplyError(c,"radius cannot be negative");
         return -1;
     }
 
@@ -465,7 +469,6 @@ void georadiusGeneric(client *c, int type) {
     double radius_meters = 0, conversion = 1;
     if ((radius_meters = extractDistanceOrReply(c, c->argv + base_args - 2,
                                                 &conversion)) < 0) {
-        addReplyError(c,"radius must be >= 0");
         return;
     }
 