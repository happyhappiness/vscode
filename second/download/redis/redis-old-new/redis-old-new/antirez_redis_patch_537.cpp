@@ -82,18 +82,18 @@ void geoArrayFree(geoArray *ga) {
 /* ====================================================================
  * Helpers
  * ==================================================================== */
-static inline int decodeGeohash(double bits, double *latlong) {
+static inline int decodeGeohash(double bits, double *xy) {
     GeoHashBits hash = { .bits = (uint64_t)bits, .step = GEO_STEP_MAX };
-    return geohashDecodeToLatLongWGS84(hash, latlong);
+    return geohashDecodeToLongLatWGS84(hash, xy);
 }
 
 /* Input Argument Helper */
 /* Take a pointer to the latitude arg then use the next arg for longitude.
  * On parse error REDIS_ERR is returned, otherwise REDIS_OK. */
-static inline int extractLatLongOrReply(redisClient *c, robj **argv,
-                                         double *latlong) {
+static inline int extractLongLatOrReply(redisClient *c, robj **argv,
+                                        double *xy) {
     for (int i = 0; i < 2; i++) {
-        if (getDoubleFromObjectOrReply(c, argv[i], latlong + i, NULL) !=
+        if (getDoubleFromObjectOrReply(c, argv[i], xy + i, NULL) !=
             REDIS_OK) {
             return REDIS_ERR;
         }
@@ -104,11 +104,11 @@ static inline int extractLatLongOrReply(redisClient *c, robj **argv,
 /* Input Argument Helper */
 /* Decode lat/long from a zset member's score.
  * Returns REDIS_OK on successful decoding, otherwise REDIS_ERR is returned. */
-static int latLongFromMember(robj *zobj, robj *member, double *latlong) {
+static int longLatFromMember(robj *zobj, robj *member, double *xy) {
     double score = 0;
 
     if (zsetScore(zobj, member, &score) == REDIS_ERR) return REDIS_ERR;
-    if (!decodeGeohash(score, latlong)) return REDIS_ERR;
+    if (!decodeGeohash(score, xy)) return REDIS_ERR;
     return REDIS_OK;
 }
 
@@ -166,22 +166,22 @@ static inline void addReplyDoubleDistance(redisClient *c, double d) {
  * only if the point is within the search area.
  *
  * returns REDIS_OK if the point is included, or REIDS_ERR if it is outside. */
-int geoAppendIfWithinRadius(geoArray *ga, double lat, double lon, double radius, double score, sds member) {
-    double distance, latlong[2];
+int geoAppendIfWithinRadius(geoArray *ga, double lon, double lat, double radius, double score, sds member) {
+    double distance, xy[2];
 
-    if (!decodeGeohash(score,latlong)) return REDIS_ERR; /* Can't decode. */
+    if (!decodeGeohash(score,xy)) return REDIS_ERR; /* Can't decode. */
     /* Note that geohashGetDistanceIfInRadiusWGS84() takes arguments in
      * reverse order: longitude first, latitude later. */
-    if (!geohashGetDistanceIfInRadiusWGS84(lon,lat,latlong[1], latlong[0],
+    if (!geohashGetDistanceIfInRadiusWGS84(lon,lat, xy[0], xy[1],
                                            radius, &distance))
     {
         return REDIS_ERR;
     }
 
     /* Append the new element. */
     geoPoint *gp = geoArrayAppend(ga);
-    gp->latitude = latlong[0];
-    gp->longitude = latlong[1];
+    gp->longitude = xy[0];
+    gp->latitude = xy[1];
     gp->dist = distance;
     gp->member = member;
     gp->score = score;
@@ -200,7 +200,7 @@ int geoAppendIfWithinRadius(geoArray *ga, double lat, double lon, double radius,
  * using multiple queries to the sorted set, that we later need to sort
  * via qsort. Similarly we need to be able to reject points outside the search
  * radius area ASAP in order to allocate and process more points than needed. */
-int geoGetPointsInRange(robj *zobj, double min, double max, double lat, double lon, double radius, geoArray *ga) {
+int geoGetPointsInRange(robj *zobj, double min, double max, double lon, double lat, double radius, geoArray *ga) {
     /* minex 0 = include min in range; maxex 1 = exclude max in range */
     /* That's: min <= val < max */
     zrangespec range = { .min = min, .max = max, .minex = 0, .maxex = 1 };
@@ -232,7 +232,7 @@ int geoGetPointsInRange(robj *zobj, double min, double max, double lat, double l
             ziplistGet(eptr, &vstr, &vlen, &vlong);
             member = (vstr == NULL) ? sdsfromlonglong(vlong) :
                                       sdsnewlen(vstr,vlen);
-            if (geoAppendIfWithinRadius(ga,lat,lon,radius,score,member)
+            if (geoAppendIfWithinRadius(ga,lon,lat,radius,score,member)
                 == REDIS_ERR) sdsfree(member);
             zzlNext(zl, &eptr, &sptr);
         }
@@ -255,7 +255,7 @@ int geoGetPointsInRange(robj *zobj, double min, double max, double lat, double l
             member = (o->encoding == REDIS_ENCODING_INT) ?
                         sdsfromlonglong((long)o->ptr) :
                         sdsdup(o->ptr);
-            if (geoAppendIfWithinRadius(ga,lat,lon,radius,ln->score,member)
+            if (geoAppendIfWithinRadius(ga,lon,lat,radius,ln->score,member)
                 == REDIS_ERR) sdsfree(member);
             ln = ln->level[0].forward;
         }
@@ -266,7 +266,7 @@ int geoGetPointsInRange(robj *zobj, double min, double max, double lat, double l
 /* Obtain all members between the min/max of this geohash bounding box.
  * Populate a geoArray of GeoPoints by calling geoGetPointsInRange().
  * Return the number of points added to the array. */
-int membersOfGeoHashBox(robj *zobj, GeoHashBits hash, geoArray *ga, double lat, double lon, double radius) {
+int membersOfGeoHashBox(robj *zobj, GeoHashBits hash, geoArray *ga, double lon, double lat, double radius) {
     GeoHashFix52Bits min, max;
 
     /* We want to compute the sorted set scores that will include all the
@@ -293,11 +293,11 @@ int membersOfGeoHashBox(robj *zobj, GeoHashBits hash, geoArray *ga, double lat,
     hash.bits++;
     max = geohashAlign52Bits(hash);
 
-    return geoGetPointsInRange(zobj, min, max, lat, lon, radius, ga);
+    return geoGetPointsInRange(zobj, min, max, lon, lat, radius, ga);
 }
 
 /* Search all eight neighbors + self geohash box */
-int membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double lat, double lon, double radius, geoArray *ga) {
+int membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double lon, double lat, double radius, geoArray *ga) {
     GeoHashBits neighbors[9];
     unsigned int i, count = 0;
 
@@ -316,7 +316,7 @@ int membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double lat, double lon, d
     for (i = 0; i < sizeof(neighbors) / sizeof(*neighbors); i++) {
         if (HASHISZERO(neighbors[i]))
             continue;
-        count += membersOfGeoHashBox(zobj, neighbors[i], ga, lat, lon, radius);
+        count += membersOfGeoHashBox(zobj, neighbors[i], ga, lon, lat, radius);
     }
     return count;
 }
@@ -342,9 +342,9 @@ static int sort_gp_desc(const void *a, const void *b) {
  * Commands
  * ==================================================================== */
 void geoAddCommand(redisClient *c) {
-    /* args 0-4: [cmd, key, lat, lng, val]; optional 5-6: [radius, units]
+    /* args 0-4: [cmd, key, lng, lat, val]; optional 5-6: [radius, units]
      * - OR -
-     * args 0-N: [cmd, key, lat, lng, val, lat2, lng2, val2, ...] */
+     * args 0-N: [cmd, key, lng, lat, val, lng2, lat2, val2, ...] */
 
     /* Prepare for the three different forms of the add command. */
     double radius_meters = 0;
@@ -358,8 +358,8 @@ void geoAddCommand(redisClient *c) {
         return;
     } else if ((c->argc - 2) % 3 != 0) {
         /* Need an odd number of arguments if we got this far... */
-        addReplyError(c, "format is: geoadd [key] [lat1] [long1] [member1] "
-                         "[lat2] [long2] [member2] ... ");
+        addReplyError(c, "format is: geoadd [key] [x1] [y1] [member1] "
+                         "[x2] [y2] [member2] ... ");
         return;
     }
 
@@ -376,9 +376,9 @@ void geoAddCommand(redisClient *c) {
     uint8_t step = geohashEstimateStepsByRadius(radius_meters,0);
     int i;
     for (i = 0; i < elements; i++) {
-        double latlong[elements * 2];
+        double xy[2];
 
-        if (extractLatLongOrReply(c, (c->argv+2)+(i*3),latlong) == REDIS_ERR) {
+        if (extractLongLatOrReply(c, (c->argv+2)+(i*3),xy) == REDIS_ERR) {
             for (i = 0; i < argc; i++)
                 if (argv[i]) decrRefCount(argv[i]);
             zfree(argv);
@@ -391,10 +391,7 @@ void geoAddCommand(redisClient *c) {
 
         /* Turn the coordinates into the score of the element. */
         GeoHashBits hash;
-        double latitude = latlong[0];
-        double longitude = latlong[1];
-        geohashEncodeWGS84(latitude, longitude, step, &hash);
-
+        geohashEncodeWGS84(xy[0], xy[1], step, &hash);
         GeoHashFix52Bits bits = geohashAlign52Bits(hash);
         robj *score = createObject(REDIS_STRING, sdsfromlonglong(bits));
         robj *val = c->argv[2 + i * 3 + 2];
@@ -416,7 +413,7 @@ void geoAddCommand(redisClient *c) {
 #define RADIUS_MEMBER 2
 
 static void geoRadiusGeneric(redisClient *c, int type) {
-    /* type == cords:  [cmd, key, lat, long, radius, units, [optionals]]
+    /* type == cords:  [cmd, key, long, lat, radius, units, [optionals]]
      * type == member: [cmd, key, member,    radius, units, [optionals]] */
     robj *key = c->argv[1];
 
@@ -427,17 +424,17 @@ static void geoRadiusGeneric(redisClient *c, int type) {
         return;
     }
 
-    /* Find lat/long to use for radius search based on inquiry type */
+    /* Find long/lat to use for radius search based on inquiry type */
     int base_args;
-    double latlong[2] = { 0 };
+    double xy[2] = { 0 };
     if (type == RADIUS_COORDS) {
         base_args = 6;
-        if (extractLatLongOrReply(c, c->argv + 2, latlong) == REDIS_ERR)
+        if (extractLongLatOrReply(c, c->argv + 2, xy) == REDIS_ERR)
             return;
     } else if (type == RADIUS_MEMBER) {
         base_args = 5;
         robj *member = c->argv[2];
-        if (latLongFromMember(zobj, member, latlong) == REDIS_ERR) {
+        if (longLatFromMember(zobj, member, xy) == REDIS_ERR) {
             addReplyError(c, "could not decode requested zset member");
             return;
         }
@@ -483,15 +480,15 @@ static void geoRadiusGeneric(redisClient *c, int type) {
 
     /* Get all neighbor geohash boxes for our radius search */
     GeoHashRadius georadius =
-        geohashGetAreasByRadiusWGS84(latlong[0], latlong[1], radius_meters);
+        geohashGetAreasByRadiusWGS84(xy[0], xy[1], radius_meters);
 
 #ifdef DEBUG
     printf("Searching with step size: %d\n", georadius.hash.step);
 #endif
 
     /* Search the zset for all matching points */
     geoArray *ga = geoArrayCreate();
-    membersOfAllNeighbors(zobj, georadius, latlong[0], latlong[1], radius_meters, ga);
+    membersOfAllNeighbors(zobj, georadius, xy[0], xy[1], radius_meters, ga);
 
     /* If no matching results, the user gets an empty reply. */
     if (ga->used == 0) {
@@ -549,15 +546,15 @@ static void geoRadiusGeneric(redisClient *c, int type) {
 
         if (withcoords) {
             addReplyMultiBulkLen(c, 2);
-            addReplyDouble(c, gp->latitude);
             addReplyDouble(c, gp->longitude);
+            addReplyDouble(c, gp->latitude);
         }
     }
     geoArrayFree(ga);
 }
 
 void geoRadiusCommand(redisClient *c) {
-    /* args 0-5: ["georadius", key, lat, long, radius, units];
+    /* args 0-5: ["georadius", key, long, lat, radius, units];
      * optionals: [withdist, withcoords, asc|desc] */
     geoRadiusGeneric(c, RADIUS_COORDS);
 }
@@ -578,30 +575,30 @@ void geoDecodeCommand(redisClient *c) {
     geohash.step = GEO_STEP_MAX;
     geohashDecodeWGS84(geohash, &area);
 
-    double lat = (area.latitude.min + area.latitude.max) / 2;
     double lon = (area.longitude.min + area.longitude.max) / 2;
+    double lat = (area.latitude.min + area.latitude.max) / 2;
 
     /* Returning three nested replies */
     addReplyMultiBulkLen(c, 3);
 
     /* First, the minimum corner */
     addReplyMultiBulkLen(c, 2);
-    addReplyDouble(c, area.latitude.min);
     addReplyDouble(c, area.longitude.min);
+    addReplyDouble(c, area.latitude.min);
 
     /* Next, the maximum corner */
     addReplyMultiBulkLen(c, 2);
-    addReplyDouble(c, area.latitude.max);
     addReplyDouble(c, area.longitude.max);
+    addReplyDouble(c, area.latitude.max);
 
     /* Last, the averaged center of this bounding box */
     addReplyMultiBulkLen(c, 2);
-    addReplyDouble(c, lat);
     addReplyDouble(c, lon);
+    addReplyDouble(c, lat);
 }
 
 void geoEncodeCommand(redisClient *c) {
-    /* args 0-2: ["geoencode", lat, long];
+    /* args 0-2: ["geoencode", long, lat];
      * optionals: [radius, units] */
 
     double radius_meters = 0;
@@ -613,13 +610,13 @@ void geoEncodeCommand(redisClient *c) {
         return;
     }
 
-    double latlong[2];
-    if (extractLatLongOrReply(c, c->argv + 1, latlong) == REDIS_ERR) return;
+    double xy[2];
+    if (extractLongLatOrReply(c, c->argv + 1, xy) == REDIS_ERR) return;
 
     /* Encode lat/long into our geohash */
     GeoHashBits geohash;
     uint8_t step = geohashEstimateStepsByRadius(radius_meters,0);
-    geohashEncodeWGS84(latlong[0], latlong[1], step, &geohash);
+    geohashEncodeWGS84(xy[0], xy[1], step, &geohash);
 
     /* Align the hash to a valid 52-bit integer based on step size */
     GeoHashFix52Bits bits = geohashAlign52Bits(geohash);
@@ -631,8 +628,8 @@ void geoEncodeCommand(redisClient *c) {
     GeoHashArea area;
     geohashDecodeWGS84(geohash, &area);
 
-    double lat = (area.latitude.min + area.latitude.max) / 2;
     double lon = (area.longitude.min + area.longitude.max) / 2;
+    double lat = (area.latitude.min + area.latitude.max) / 2;
 
     /* Return four nested multibulk replies. */
     addReplyMultiBulkLen(c, 4);
@@ -642,18 +639,18 @@ void geoEncodeCommand(redisClient *c) {
 
     /* Return the minimum corner */
     addReplyMultiBulkLen(c, 2);
-    addReplyDouble(c, area.latitude.min);
     addReplyDouble(c, area.longitude.min);
+    addReplyDouble(c, area.latitude.min);
 
     /* Return the maximum corner */
     addReplyMultiBulkLen(c, 2);
-    addReplyDouble(c, area.latitude.max);
     addReplyDouble(c, area.longitude.max);
+    addReplyDouble(c, area.latitude.max);
 
     /* Return the averaged center */
     addReplyMultiBulkLen(c, 2);
-    addReplyDouble(c, lat);
     addReplyDouble(c, lon);
+    addReplyDouble(c, lat);
 }
 
 /* GEOHASH key ele1 ele2 ... eleN
@@ -684,20 +681,20 @@ void geoHashCommand(redisClient *c) {
              * standard ranges in order to output a valid geohash string. */
 
             /* Decode... */
-            double latlong[2];
-            if (!decodeGeohash(score,latlong)) {
+            double xy[2];
+            if (!decodeGeohash(score,xy)) {
                 addReply(c,shared.nullbulk);
                 continue;
             }
 
             /* Re-encode */
             GeoHashRange r[2];
             GeoHashBits hash;
-            r[0].min = -90;
-            r[0].max = 90;
-            r[1].min = -180;
-            r[1].max = 180;
-            geohashEncode(&r[0],&r[1],latlong[0],latlong[1],26,&hash);
+            r[0].min = -180;
+            r[0].max = 180;
+            r[1].min = -90;
+            r[1].max = 90;
+            geohashEncode(&r[0],&r[1],xy[0],xy[1],26,&hash);
 
             char buf[12];
             int i;