@@ -88,33 +88,33 @@ int decodeGeohash(double bits, double *xy) {
 
 /* Input Argument Helper */
 /* Take a pointer to the latitude arg then use the next arg for longitude.
- * On parse error REDIS_ERR is returned, otherwise REDIS_OK. */
+ * On parse error C_ERR is returned, otherwise C_OK. */
 int extractLongLatOrReply(client *c, robj **argv,
                                         double *xy) {
     for (int i = 0; i < 2; i++) {
         if (getDoubleFromObjectOrReply(c, argv[i], xy + i, NULL) !=
-            REDIS_OK) {
-            return REDIS_ERR;
+            C_OK) {
+            return C_ERR;
         }
         if (xy[0] < GEO_LONG_MIN || xy[0] > GEO_LONG_MAX ||
             xy[1] < GEO_LAT_MIN  || xy[1] > GEO_LAT_MAX) {
             addReplySds(c, sdscatprintf(sdsempty(),
                 "-ERR invalid longitude,latitude pair %f,%f\r\n",xy[0],xy[1]));
-            return REDIS_ERR;
+            return C_ERR;
         }
     }
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Input Argument Helper */
 /* Decode lat/long from a zset member's score.
- * Returns REDIS_OK on successful decoding, otherwise REDIS_ERR is returned. */
+ * Returns C_OK on successful decoding, otherwise C_ERR is returned. */
 int longLatFromMember(robj *zobj, robj *member, double *xy) {
     double score = 0;
 
-    if (zsetScore(zobj, member, &score) == REDIS_ERR) return REDIS_ERR;
-    if (!decodeGeohash(score, xy)) return REDIS_ERR;
-    return REDIS_OK;
+    if (zsetScore(zobj, member, &score) == C_ERR) return C_ERR;
+    if (!decodeGeohash(score, xy)) return C_ERR;
+    return C_OK;
 }
 
 /* Check that the unit argument matches one of the known units, and returns
@@ -152,7 +152,7 @@ double extractDistanceOrReply(client *c, robj **argv,
                                      double *conversion) {
     double distance;
     if (getDoubleFromObjectOrReply(c, argv[0], &distance,
-                                   "need numeric radius") != REDIS_OK) {
+                                   "need numeric radius") != C_OK) {
         return -1;
     }
 
@@ -179,17 +179,17 @@ void addReplyDoubleDistance(client *c, double d) {
  * a radius, appends this entry as a geoPoint into the specified geoArray
  * only if the point is within the search area.
  *
- * returns REDIS_OK if the point is included, or REIDS_ERR if it is outside. */
+ * returns C_OK if the point is included, or REIDS_ERR if it is outside. */
 int geoAppendIfWithinRadius(geoArray *ga, double lon, double lat, double radius, double score, sds member) {
     double distance, xy[2];
 
-    if (!decodeGeohash(score,xy)) return REDIS_ERR; /* Can't decode. */
+    if (!decodeGeohash(score,xy)) return C_ERR; /* Can't decode. */
     /* Note that geohashGetDistanceIfInRadiusWGS84() takes arguments in
      * reverse order: longitude first, latitude later. */
     if (!geohashGetDistanceIfInRadiusWGS84(lon,lat, xy[0], xy[1],
                                            radius, &distance))
     {
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     /* Append the new element. */
@@ -199,7 +199,7 @@ int geoAppendIfWithinRadius(geoArray *ga, double lon, double lat, double radius,
     gp->dist = distance;
     gp->member = member;
     gp->score = score;
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Query a Redis sorted set to extract all the elements between 'min' and
@@ -247,7 +247,7 @@ int geoGetPointsInRange(robj *zobj, double min, double max, double lon, double l
             member = (vstr == NULL) ? sdsfromlonglong(vlong) :
                                       sdsnewlen(vstr,vlen);
             if (geoAppendIfWithinRadius(ga,lon,lat,radius,score,member)
-                == REDIS_ERR) sdsfree(member);
+                == C_ERR) sdsfree(member);
             zzlNext(zl, &eptr, &sptr);
         }
     } else if (zobj->encoding == OBJ_ENCODING_SKIPLIST) {
@@ -270,7 +270,7 @@ int geoGetPointsInRange(robj *zobj, double min, double max, double lon, double l
                         sdsfromlonglong((long)o->ptr) :
                         sdsdup(o->ptr);
             if (geoAppendIfWithinRadius(ga,lon,lat,radius,ln->score,member)
-                == REDIS_ERR) sdsfree(member);
+                == C_ERR) sdsfree(member);
             ln = ln->level[0].forward;
         }
     }
@@ -386,7 +386,7 @@ void geoaddCommand(client *c) {
     for (i = 0; i < elements; i++) {
         double xy[2];
 
-        if (extractLongLatOrReply(c, (c->argv+2)+(i*3),xy) == REDIS_ERR) {
+        if (extractLongLatOrReply(c, (c->argv+2)+(i*3),xy) == C_ERR) {
             for (i = 0; i < argc; i++)
                 if (argv[i]) decrRefCount(argv[i]);
             zfree(argv);
@@ -434,12 +434,12 @@ void georadiusGeneric(client *c, int type) {
     double xy[2] = { 0 };
     if (type == RADIUS_COORDS) {
         base_args = 6;
-        if (extractLongLatOrReply(c, c->argv + 2, xy) == REDIS_ERR)
+        if (extractLongLatOrReply(c, c->argv + 2, xy) == C_ERR)
             return;
     } else if (type == RADIUS_MEMBER) {
         base_args = 5;
         robj *member = c->argv[2];
-        if (longLatFromMember(zobj, member, xy) == REDIS_ERR) {
+        if (longLatFromMember(zobj, member, xy) == C_ERR) {
             addReplyError(c, "could not decode requested zset member");
             return;
         }
@@ -475,7 +475,7 @@ void georadiusGeneric(client *c, int type) {
                 sort = SORT_DESC;
             } else if (!strcasecmp(arg, "count") && remaining > 0) {
                 if (getLongLongFromObjectOrReply(c, c->argv[base_args+i+1],
-                    &count, NULL) != REDIS_OK) return;
+                    &count, NULL) != C_OK) return;
                 if (count <= 0) {
                     addReplyError(c,"COUNT must be > 0");
                     return;
@@ -596,7 +596,7 @@ void geohashCommand(client *c) {
     addReplyMultiBulkLen(c,c->argc-2);
     for (j = 2; j < c->argc; j++) {
         double score;
-        if (zsetScore(zobj, c->argv[j], &score) == REDIS_ERR) {
+        if (zsetScore(zobj, c->argv[j], &score) == C_ERR) {
             addReply(c,shared.nullbulk);
         } else {
             /* The internal format we use for geocoding is a bit different
@@ -650,7 +650,7 @@ void geoposCommand(client *c) {
     addReplyMultiBulkLen(c,c->argc-2);
     for (j = 2; j < c->argc; j++) {
         double score;
-        if (zsetScore(zobj, c->argv[j], &score) == REDIS_ERR) {
+        if (zsetScore(zobj, c->argv[j], &score) == C_ERR) {
             addReply(c,shared.nullmultibulk);
         } else {
             /* Decode... */
@@ -690,8 +690,8 @@ void geodistCommand(client *c) {
 
     /* Get the scores. We need both otherwise NULL is returned. */
     double score1, score2, xyxy[4];
-    if (zsetScore(zobj, c->argv[2], &score1) == REDIS_ERR ||
-        zsetScore(zobj, c->argv[3], &score2) == REDIS_ERR)
+    if (zsetScore(zobj, c->argv[2], &score1) == C_ERR ||
+        zsetScore(zobj, c->argv[3], &score2) == C_ERR)
     {
         addReply(c,shared.nullbulk);
         return;