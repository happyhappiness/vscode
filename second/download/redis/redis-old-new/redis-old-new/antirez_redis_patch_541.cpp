@@ -29,13 +29,15 @@
 
 #include "geo.h"
 #include "geohash_helper.h"
-#include "zset.h"
+
+/* Things exported from t_zset.c only for geo.c, since it is the only other
+ * part of Redis that requires close zset introspection. */
+unsigned char *zzlFirstInRange(unsigned char *zl, zrangespec *range);
+int zslValueLteMax(double value, zrangespec *spec);
 
 /* ====================================================================
- * Redis Add-on Module: geo
- * Provides commands: geoadd, georadius, georadiusbymember,
- *                    geoencode, geodecode
- * Behaviors:
+ * This file implements the following commands:
+ *
  *   - geoadd - add coordinates for value to geoset
  *   - georadius - search radius by coordinates in geoset
  *   - georadiusbymember - search radius based on geoset member position
@@ -44,6 +46,40 @@
  * ==================================================================== */
 
 /* ====================================================================
+ * geoArray implementation
+ * ==================================================================== */
+
+/* Create a new array of geoPoints. */
+geoArray *geoArrayCreate(void) {
+    geoArray *ga = zmalloc(sizeof(*ga));
+    /* It gets allocated on first geoArrayAppend() call. */
+    ga->array = NULL;
+    ga->buckets = 0;
+    ga->used = 0;
+    return ga;
+}
+
+/* Add a new entry and return its pointer so that the caller can populate
+ * it with data. */
+geoPoint *geoArrayAppend(geoArray *ga) {
+    if (ga->used == ga->buckets) {
+        ga->buckets = (ga->buckets == 0) ? 8 : ga->buckets*2;
+        ga->array = zrealloc(ga->array,sizeof(geoPoint)*ga->buckets);
+    }
+    geoPoint *gp = ga->array+ga->used;
+    ga->used++;
+    return gp;
+}
+
+/* Destroy a geoArray created with geoArrayCreate(). */
+void geoArrayFree(geoArray *ga) {
+    size_t i;
+    for (i = 0; i < ga->used; i++) sdsfree(ga->array[i].member);
+    zfree(ga->array);
+    zfree(ga);
+}
+
+/* ====================================================================
  * Helpers
  * ==================================================================== */
 static inline int decodeGeohash(double bits, double *latlong) {
@@ -65,16 +101,13 @@ static inline int extractLatLongOrReply(redisClient *c, robj **argv,
 }
 
 /* Input Argument Helper */
-/* Decode lat/long from a zset member's score */
+/* Decode lat/long from a zset member's score.
+ * Returns non-zero on successful decoding. */
 static int latLongFromMember(robj *zobj, robj *member, double *latlong) {
     double score = 0;
 
-    if (!zsetScore(zobj, member, &score))
-        return 0;
-
-    if (!decodeGeohash(score, latlong))
-        return 0;
-
+    if (zsetScore(zobj, member, &score) == REDIS_ERR) return 0;
+    if (!decodeGeohash(score, latlong)) return 0;
     return 1;
 }
 
@@ -120,25 +153,129 @@ static inline void addReplyDoubleDistance(redisClient *c, double d) {
     addReplyBulkCBuffer(c, dbuf, dlen);
 }
 
-/* geohash range+zset access helper */
-/* Obtain all members between the min/max of this geohash bounding box. */
-/* Returns list of results.  List must be listRelease()'d later. */
-static list *membersOfGeoHashBox(robj *zobj, GeoHashBits hash) {
+/* Helper function for geoGetPointsInRange(): given a sorted set score
+ * representing a point, and another point (the center of our search) and
+ * a radius, appends this entry as a geoPoint into the specified geoArray
+ * only if the point is within the search area.
+ *
+ * returns REDIS_OK if the point is included, or REIDS_ERR if it is outside. */
+int geoAppendIfWithinRadius(geoArray *ga, double x, double y, double radius, double score, sds member) {
+    GeoHashArea area = {{0,0},{0,0},{0,0}};
+    GeoHashBits hash = { .bits = (uint64_t)score, .step = GEO_STEP_MAX };
+    double distance;
+
+    if (!geohashDecodeWGS84(hash, &area)) return REDIS_ERR; /* Can't decode. */
+
+    double neighbor_y = (area.latitude.min + area.latitude.max) / 2;
+    double neighbor_x = (area.longitude.min + area.longitude.max) / 2;
+
+    if (!geohashGetDistanceIfInRadiusWGS84(x, y, neighbor_x, neighbor_y,
+                                           radius, &distance)) {
+        return REDIS_ERR;
+    }
+
+    /* Append the new element. */
+    geoPoint *gp = geoArrayAppend(ga);
+    gp->latitude = neighbor_y;
+    gp->longitude = neighbor_x;
+    gp->dist = distance;
+    gp->member = member;
+    gp->score = score;
+    return REDIS_OK;
+}
+
+/* Query a Redis sorted set to extract all the elements between 'min' and
+ * 'max', appending them into the array of geoPoint structures 'gparray'.
+ * The command returns the number of elements added to the array.
+ *
+ * Elements which are farest than 'radius' from the specified 'x' and 'y'
+ * coordinates are not included.
+ *
+ * The ability of this function to append to an existing set of points is
+ * important for good performances because querying by radius is performed
+ * using multiple queries to the sorted set, that we later need to sort
+ * via qsort. Similarly we need to be able to reject points outside the search
+ * radius area ASAP in order to allocate and process more points than needed. */
+int geoGetPointsInRange(robj *zobj, double min, double max, double x, double y, double radius, geoArray *ga) {
+    /* minex 0 = include min in range; maxex 1 = exclude max in range */
+    /* That's: min <= val < max */
+    zrangespec range = { .min = min, .max = max, .minex = 0, .maxex = 1 };
+    size_t origincount = ga->used;
+    sds member;
+
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *zl = zobj->ptr;
+        unsigned char *eptr, *sptr;
+        unsigned char *vstr = NULL;
+        unsigned int vlen = 0;
+        long long vlong = 0;
+        double score = 0;
+
+        if ((eptr = zzlFirstInRange(zl, &range)) == NULL) {
+            /* Nothing exists starting at our min.  No results. */
+            return 0;
+        }
+
+        sptr = ziplistNext(zl, eptr);
+        while (eptr) {
+            score = zzlGetScore(sptr);
+
+            /* If we fell out of range, break. */
+            if (!zslValueLteMax(score, &range))
+                break;
+
+            /* We know the element exists. ziplistGet should always succeed */
+            ziplistGet(eptr, &vstr, &vlen, &vlong);
+            member = (vstr == NULL) ? sdsfromlonglong(vlong) :
+                                      sdsnewlen(vstr,vlen);
+            if (geoAppendIfWithinRadius(ga,x,y,radius,score,member)
+                == REDIS_ERR) sdsfree(member);
+            zzlNext(zl, &eptr, &sptr);
+        }
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+        zskiplist *zsl = zs->zsl;
+        zskiplistNode *ln;
+
+        if ((ln = zslFirstInRange(zsl, &range)) == NULL) {
+            /* Nothing exists starting at our min.  No results. */
+            return 0;
+        }
+
+        while (ln) {
+            robj *o = ln->obj;
+            /* Abort when the node is no longer in range. */
+            if (!zslValueLteMax(ln->score, &range))
+                break;
+
+            member = (o->encoding == REDIS_ENCODING_INT) ?
+                        sdsfromlonglong((long)o->ptr) :
+                        sdsdup(o->ptr);
+            if (geoAppendIfWithinRadius(ga,x,y,radius,ln->score,member)
+                == REDIS_ERR) sdsfree(member);
+            ln = ln->level[0].forward;
+        }
+    }
+    return ga->used - origincount;
+}
+
+/* Obtain all members between the min/max of this geohash bounding box.
+ * Populate a geoArray of GeoPoints by calling geoGetPointsInRange().
+ * Return the number of points added to the array. */
+int membersOfGeoHashBox(robj *zobj, GeoHashBits hash, geoArray *ga, double x, double y, double radius) {
     GeoHashFix52Bits min, max;
 
     min = geohashAlign52Bits(hash);
     hash.bits++;
     max = geohashAlign52Bits(hash);
 
-    return geozrangebyscore(zobj, min, max, -1); /* -1 = no limit */
+    return geoGetPointsInRange(zobj, min, max, x, y, radius, ga);
 }
 
 /* Search all eight neighbors + self geohash box */
-static list *membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double x,
-                                   double y, double radius) {
-    list *l = NULL;
+int membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double x, double y, double radius, geoArray *ga) {
     GeoHashBits neighbors[9];
-    unsigned int i;
+    unsigned int i, count = 0;
 
     neighbors[0] = n.hash;
     neighbors[1] = n.neighbors.north;
@@ -153,76 +290,11 @@ static list *membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double x,
     /* For each neighbor (*and* our own hashbox), get all the matching
      * members and add them to the potential result list. */
     for (i = 0; i < sizeof(neighbors) / sizeof(*neighbors); i++) {
-        list *r;
-
         if (HASHISZERO(neighbors[i]))
             continue;
-
-        r = membersOfGeoHashBox(zobj, neighbors[i]);
-        if (!r)
-            continue;
-
-        if (!l) {
-            l = r;
-        } else {
-            listJoin(l, r);
-        }
-    }
-
-    /* if no results across any neighbors (*and* ourself, which is unlikely),
-     * then just give up. */
-    if (!l)
-        return NULL;
-
-    /* Iterate over all matching results in the combined 9-grid search area */
-    /* Remove any results outside of our search radius. */
-    listIter li;
-    listNode *ln;
-    listRewind(l, &li);
-    while ((ln = listNext(&li))) {
-        struct zipresult *zr = listNodeValue(ln);
-        GeoHashArea area = {{0,0},{0,0},{0,0}};
-        GeoHashBits hash = { .bits = (uint64_t)zr->score,
-                             .step = GEO_STEP_MAX };
-
-        if (!geohashDecodeWGS84(hash, &area)) {
-            /* Perhaps we should delete this node if the decode fails? */
-            continue;
-        }
-
-        double neighbor_y = (area.latitude.min + area.latitude.max) / 2;
-        double neighbor_x = (area.longitude.min + area.longitude.max) / 2;
-
-        double distance;
-        if (!geohashGetDistanceIfInRadiusWGS84(x, y, neighbor_x, neighbor_y,
-                                               radius, &distance)) {
-            /* If result is in the grid, but not in our radius, remove it. */
-            listDelNode(l, ln);
-#ifdef DEBUG
-            fprintf(stderr, "No match for neighbor (%f, %f) within (%f, %f) at "
-                            "distance %f\n",
-                    neighbor_y, neighbor_x, y, x, distance);
-#endif
-        } else {
-/* Else: bueno. */
-#ifdef DEBUG
-            fprintf(
-                stderr,
-                "Matched neighbor (%f, %f) within (%f, %f) at distance %f\n",
-                neighbor_y, neighbor_x, y, x, distance);
-#endif
-            zr->distance = distance;
-        }
-    }
-
-    /* We found results, but rejected all of them as out of range. Clean up. */
-    if (!listLength(l)) {
-        listRelease(l);
-        l = NULL;
+        count += membersOfGeoHashBox(zobj, neighbors[i], ga, x, y, radius);
     }
-
-    /* Success! */
-    return l;
+    return count;
 }
 
 /* Sort comparators for qsort() */
@@ -406,16 +478,17 @@ static void geoRadiusGeneric(redisClient *c, int type) {
     double x = latlong[1];
 
     /* Search the zset for all matching points */
-    list *found_matches =
-        membersOfAllNeighbors(zobj, georadius, x, y, radius_meters);
+    geoArray *ga = geoArrayCreate();
+    membersOfAllNeighbors(zobj, georadius, x, y, radius_meters, ga);
 
     /* If no matching results, the user gets an empty reply. */
-    if (!found_matches) {
+    if (ga->used == 0) {
         addReply(c, shared.emptymultibulk);
+        geoArrayFree(ga);
         return;
     }
 
-    long result_length = listLength(found_matches);
+    long result_length = ga->used;
     long option_length = 0;
 
     /* Our options are self-contained nested multibulk replies, so we
@@ -435,63 +508,40 @@ static void geoRadiusGeneric(redisClient *c, int type) {
      * user enabled for this request. */
     addReplyMultiBulkLen(c, result_length);
 
-    /* Iterate over results, populate struct used for sorting and result sending
-     */
-    listIter li;
-    listRewind(found_matches, &li);
-    struct geoPoint gp[result_length];
-    /* populate gp array from our results */
-    for (int i = 0; i < result_length; i++) {
-        struct zipresult *zr = listNodeValue(listNext(&li));
-
-        gp[i].member = NULL;
-        gp[i].set = key->ptr;
-        gp[i].dist = zr->distance / conversion;
-        gp[i].userdata = zr;
-
-        /* The layout of geoPoint allows us to pass the start offset
-         * of the struct directly to decodeGeohash. */
-        decodeGeohash(zr->score, (double *)(gp + i));
-    }
-
     /* Process [optional] requested sorting */
     if (sort == SORT_ASC) {
-        qsort(gp, result_length, sizeof(*gp), sort_gp_asc);
+        qsort(ga->array, result_length, sizeof(geoPoint), sort_gp_asc);
     } else if (sort == SORT_DESC) {
-        qsort(gp, result_length, sizeof(*gp), sort_gp_desc);
+        qsort(ga->array, result_length, sizeof(geoPoint), sort_gp_desc);
     }
 
     /* Finally send results back to the caller */
-    for (int i = 0; i < result_length; i++) {
-        struct zipresult *zr = gp[i].userdata;
+    int i;
+    for (i = 0; i < result_length; i++) {
+        geoPoint *gp = ga->array+i;
+        gp->dist /= conversion; /* Fix according to unit. */
 
         /* If we have options in option_length, return each sub-result
          * as a nested multi-bulk.  Add 1 to account for result value itself. */
         if (option_length)
             addReplyMultiBulkLen(c, option_length + 1);
 
-        switch (zr->type) {
-        case ZR_LONG:
-            addReplyBulkLongLong(c, zr->val.v);
-            break;
-        case ZR_STRING:
-            addReplyBulkCBuffer(c, zr->val.s, sdslen(zr->val.s));
-            break;
-        }
+        addReplyBulkSds(c,gp->member);
+        gp->member = NULL;
 
         if (withdist)
-            addReplyDoubleDistance(c, gp[i].dist);
+            addReplyDoubleDistance(c, gp->dist);
 
         if (withhash)
-            addReplyLongLong(c, zr->score);
+            addReplyLongLong(c, gp->score);
 
         if (withcoords) {
             addReplyMultiBulkLen(c, 2);
-            addReplyDouble(c, gp[i].latitude);
-            addReplyDouble(c, gp[i].longitude);
+            addReplyDouble(c, gp->latitude);
+            addReplyDouble(c, gp->longitude);
         }
     }
-    listRelease(found_matches);
+    geoArrayFree(ga);
 }
 
 void geoRadiusCommand(redisClient *c) {