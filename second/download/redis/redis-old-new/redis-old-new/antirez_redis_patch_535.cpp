@@ -344,20 +344,11 @@ static int sort_gp_desc(const void *a, const void *b) {
 
 /* GEOADD key long lat name [long2 lat2 name2 ... longN latN nameN] */
 void geoAddCommand(redisClient *c) {
-    /* Prepare for the three different forms of the add command. */
-    double radius_meters = 0;
-    if (c->argc == 7) {
-        if ((radius_meters = extractDistanceOrReply(c, c->argv + 5, NULL)) <
-            0) {
-            return;
-        }
-    } else if (c->argc == 6) {
-        addReplyError(c, "must provide units when asking for radius encode");
-        return;
-    } else if ((c->argc - 2) % 3 != 0) {
+    /* Check arguments number for sanity. */
+    if ((c->argc - 2) % 3 != 0) {
         /* Need an odd number of arguments if we got this far... */
-        addReplyError(c, "format is: geoadd [key] [x1] [y1] [member1] "
-                         "[x2] [y2] [member2] ... ");
+        addReplyError(c, "syntax error. Try GEOADD key [x1] [y1] [name1] "
+                         "[x2] [y2] [name2] ... ");
         return;
     }
 
@@ -371,7 +362,6 @@ void geoAddCommand(redisClient *c) {
     /* Create the argument vector to call ZADD in order to add all
      * the score,value pairs to the requested zset, where score is actually
      * an encoded version of lat,long. */
-    uint8_t step = geohashEstimateStepsByRadius(radius_meters,0);
     int i;
     for (i = 0; i < elements; i++) {
         double xy[2];
@@ -383,13 +373,9 @@ void geoAddCommand(redisClient *c) {
             return;
         }
 
-#ifdef DEBUG
-        printf("Adding with step size: %d\n", step);
-#endif
-
         /* Turn the coordinates into the score of the element. */
         GeoHashBits hash;
-        geohashEncodeWGS84(xy[0], xy[1], step, &hash);
+        geohashEncodeWGS84(xy[0], xy[1], GEO_STEP_MAX, &hash);
         GeoHashFix52Bits bits = geohashAlign52Bits(hash);
         robj *score = createObject(REDIS_STRING, sdsfromlonglong(bits));
         robj *val = c->argv[2 + i * 3 + 2];