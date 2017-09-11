@@ -465,6 +465,7 @@ void georadiusGeneric(client *c, int type) {
     double radius_meters = 0, conversion = 1;
     if ((radius_meters = extractDistanceOrReply(c, c->argv + base_args - 2,
                                                 &conversion)) < 0) {
+        addReplyError(c,"radius must be >= 0");
         return;
     }
 