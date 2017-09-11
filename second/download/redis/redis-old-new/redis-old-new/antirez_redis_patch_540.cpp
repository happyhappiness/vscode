@@ -159,11 +159,13 @@ static inline void addReplyDoubleDistance(redisClient *c, double d) {
  * only if the point is within the search area.
  *
  * returns REDIS_OK if the point is included, or REIDS_ERR if it is outside. */
-int geoAppendIfWithinRadius(geoArray *ga, double x, double y, double radius, double score, sds member) {
+int geoAppendIfWithinRadius(geoArray *ga, double lat, double lon, double radius, double score, sds member) {
     double distance, latlong[2];
 
     if (!decodeGeohash(score,latlong)) return REDIS_ERR; /* Can't decode. */
-    if (!geohashGetDistanceIfInRadiusWGS84(x,y,latlong[1], latlong[0],
+    /* Note that geohashGetDistanceIfInRadiusWGS84() takes arguments in
+     * reverse order: longitude first, latitude later. */
+    if (!geohashGetDistanceIfInRadiusWGS84(lon,lat,latlong[1], latlong[0],
                                            radius, &distance))
     {
         return REDIS_ERR;
@@ -191,7 +193,7 @@ int geoAppendIfWithinRadius(geoArray *ga, double x, double y, double radius, dou
  * using multiple queries to the sorted set, that we later need to sort
  * via qsort. Similarly we need to be able to reject points outside the search
  * radius area ASAP in order to allocate and process more points than needed. */
-int geoGetPointsInRange(robj *zobj, double min, double max, double x, double y, double radius, geoArray *ga) {
+int geoGetPointsInRange(robj *zobj, double min, double max, double lat, double lon, double radius, geoArray *ga) {
     /* minex 0 = include min in range; maxex 1 = exclude max in range */
     /* That's: min <= val < max */
     zrangespec range = { .min = min, .max = max, .minex = 0, .maxex = 1 };
@@ -223,7 +225,7 @@ int geoGetPointsInRange(robj *zobj, double min, double max, double x, double y,
             ziplistGet(eptr, &vstr, &vlen, &vlong);
             member = (vstr == NULL) ? sdsfromlonglong(vlong) :
                                       sdsnewlen(vstr,vlen);
-            if (geoAppendIfWithinRadius(ga,x,y,radius,score,member)
+            if (geoAppendIfWithinRadius(ga,lat,lon,radius,score,member)
                 == REDIS_ERR) sdsfree(member);
             zzlNext(zl, &eptr, &sptr);
         }
@@ -246,7 +248,7 @@ int geoGetPointsInRange(robj *zobj, double min, double max, double x, double y,
             member = (o->encoding == REDIS_ENCODING_INT) ?
                         sdsfromlonglong((long)o->ptr) :
                         sdsdup(o->ptr);
-            if (geoAppendIfWithinRadius(ga,x,y,radius,ln->score,member)
+            if (geoAppendIfWithinRadius(ga,lat,lon,radius,ln->score,member)
                 == REDIS_ERR) sdsfree(member);
             ln = ln->level[0].forward;
         }
@@ -257,18 +259,18 @@ int geoGetPointsInRange(robj *zobj, double min, double max, double x, double y,
 /* Obtain all members between the min/max of this geohash bounding box.
  * Populate a geoArray of GeoPoints by calling geoGetPointsInRange().
  * Return the number of points added to the array. */
-int membersOfGeoHashBox(robj *zobj, GeoHashBits hash, geoArray *ga, double x, double y, double radius) {
+int membersOfGeoHashBox(robj *zobj, GeoHashBits hash, geoArray *ga, double lat, double lon, double radius) {
     GeoHashFix52Bits min, max;
 
     min = geohashAlign52Bits(hash);
     hash.bits++;
     max = geohashAlign52Bits(hash);
 
-    return geoGetPointsInRange(zobj, min, max, x, y, radius, ga);
+    return geoGetPointsInRange(zobj, min, max, lat, lon, radius, ga);
 }
 
 /* Search all eight neighbors + self geohash box */
-int membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double x, double y, double radius, geoArray *ga) {
+int membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double lat, double lon, double radius, geoArray *ga) {
     GeoHashBits neighbors[9];
     unsigned int i, count = 0;
 
@@ -287,7 +289,7 @@ int membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double x, double y, doubl
     for (i = 0; i < sizeof(neighbors) / sizeof(*neighbors); i++) {
         if (HASHISZERO(neighbors[i]))
             continue;
-        count += membersOfGeoHashBox(zobj, neighbors[i], ga, x, y, radius);
+        count += membersOfGeoHashBox(zobj, neighbors[i], ga, lat, lon, radius);
     }
     return count;
 }
@@ -468,13 +470,10 @@ static void geoRadiusGeneric(redisClient *c, int type) {
 #ifdef DEBUG
     printf("Searching with step size: %d\n", georadius.hash.step);
 #endif
-    /* {Lat, Long} = {y, x} */
-    double y = latlong[0];
-    double x = latlong[1];
 
     /* Search the zset for all matching points */
     geoArray *ga = geoArrayCreate();
-    membersOfAllNeighbors(zobj, georadius, x, y, radius_meters, ga);
+    membersOfAllNeighbors(zobj, georadius, latlong[0], latlong[1], radius_meters, ga);
 
     /* If no matching results, the user gets an empty reply. */
     if (ga->used == 0) {