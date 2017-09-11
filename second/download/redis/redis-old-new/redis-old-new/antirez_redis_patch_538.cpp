@@ -88,30 +88,37 @@ static inline int decodeGeohash(double bits, double *latlong) {
 }
 
 /* Input Argument Helper */
-/* Take a pointer to the latitude arg then use the next arg for longitude */
+/* Take a pointer to the latitude arg then use the next arg for longitude.
+ * On parse error REDIS_ERR is returned, otherwise REDIS_OK. */
 static inline int extractLatLongOrReply(redisClient *c, robj **argv,
                                          double *latlong) {
     for (int i = 0; i < 2; i++) {
         if (getDoubleFromObjectOrReply(c, argv[i], latlong + i, NULL) !=
             REDIS_OK) {
-            return 0;
+            return REDIS_ERR;
         }
     }
-    return 1;
+    return REDIS_OK;
 }
 
 /* Input Argument Helper */
 /* Decode lat/long from a zset member's score.
- * Returns non-zero on successful decoding. */
+ * Returns REDIS_OK on successful decoding, otherwise REDIS_ERR is returned. */
 static int latLongFromMember(robj *zobj, robj *member, double *latlong) {
     double score = 0;
 
-    if (zsetScore(zobj, member, &score) == REDIS_ERR) return 0;
-    if (!decodeGeohash(score, latlong)) return 0;
-    return 1;
+    if (zsetScore(zobj, member, &score) == REDIS_ERR) return REDIS_ERR;
+    if (!decodeGeohash(score, latlong)) return REDIS_ERR;
+    return REDIS_OK;
 }
 
-/* Input Argument Helper */
+/* Input Argument Helper.
+ * Extract the dinstance from the specified two arguments starting at 'argv'
+ * that shouldbe in the form: <number> <unit> and return the dinstance in the
+ * specified unit on success. *conversino is populated with the coefficient
+ * to use in order to convert meters to the unit.
+ *
+ * On error a value less than zero is returned. */
 static double extractDistanceOrReply(redisClient *c, robj **argv,
                                      double *conversion) {
     double distance;
@@ -351,7 +358,7 @@ void geoAddCommand(redisClient *c) {
     for (i = 0; i < elements; i++) {
         double latlong[elements * 2];
 
-        if (!extractLatLongOrReply(c, (c->argv+2)+(i*3),latlong)) {
+        if (extractLatLongOrReply(c, (c->argv+2)+(i*3),latlong) == REDIS_ERR) {
             for (i = 0; i < argc; i++)
                 if (argv[i]) decrRefCount(argv[i]);
             zfree(argv);
@@ -405,12 +412,12 @@ static void geoRadiusGeneric(redisClient *c, int type) {
     double latlong[2] = { 0 };
     if (type == RADIUS_COORDS) {
         base_args = 6;
-        if (!extractLatLongOrReply(c, c->argv + 2, latlong))
+        if (extractLatLongOrReply(c, c->argv + 2, latlong) == REDIS_ERR)
             return;
     } else if (type == RADIUS_MEMBER) {
         base_args = 5;
         robj *member = c->argv[2];
-        if (!latLongFromMember(zobj, member, latlong)) {
+        if (latLongFromMember(zobj, member, latlong) == REDIS_ERR) {
             addReplyError(c, "could not decode requested zset member");
             return;
         }
@@ -587,7 +594,7 @@ void geoEncodeCommand(redisClient *c) {
     }
 
     double latlong[2];
-    if (!extractLatLongOrReply(c, c->argv + 1, latlong)) return;
+    if (extractLatLongOrReply(c, c->argv + 1, latlong) == REDIS_ERR) return;
 
     /* Encode lat/long into our geohash */
     GeoHashBits geohash;