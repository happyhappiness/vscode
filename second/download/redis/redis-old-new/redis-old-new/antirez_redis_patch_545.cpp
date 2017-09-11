@@ -29,7 +29,6 @@
 
 #include "geo.h"
 #include "geohash_helper.h"
-#include "geojson.h"
 #include "zset.h"
 
 /* ====================================================================
@@ -110,49 +109,15 @@ static double extractDistanceOrReply(redisClient *c, robj **argv,
     return distance * to_meters;
 }
 
-/* Output Reply Helper */
-static void latLongToGeojsonAndReply(redisClient *c, struct geojsonPoint *gp,
-                                     char *units) {
-    sds geojson = geojsonLatLongToPointFeature(
-        gp->latitude, gp->longitude, gp->set, gp->member, gp->dist, units);
-
-    addReplyBulkCBuffer(c, geojson, sdslen(geojson));
-    sdsfree(geojson);
-}
-
-/* Output Reply Helper */
-static void decodeGeohashToGeojsonBoundsAndReply(redisClient *c,
-                                                 uint64_t hashbits,
-                                                 struct geojsonPoint *gp) {
-    GeoHashArea area = {{0,0},{0,0},{0,0}};
-    GeoHashBits hash = { .bits = hashbits, .step = GEO_STEP_MAX };
-
-    geohashDecodeWGS84(hash, &area);
-
-    sds geojson = geojsonBoxToPolygonFeature(
-        area.latitude.min, area.longitude.min, area.latitude.max,
-        area.longitude.max, gp->set, gp->member);
-    addReplyBulkCBuffer(c, geojson, sdslen(geojson));
-    sdsfree(geojson);
-}
-
 /* The defailt addReplyDouble has too much accuracy.  We use this
  * for returning location distances. "5.21 meters away" is nicer
  * than "5.2144992818115 meters away." */
-static inline void addReplyDoubleNicer(redisClient *c, double d) {
+static inline void addReplyDoubleMeters(redisClient *c, double d) {
     char dbuf[128] = { 0 };
     int dlen = snprintf(dbuf, sizeof(dbuf), "%.2f", d);
     addReplyBulkCBuffer(c, dbuf, dlen);
 }
 
-/* Output Reply Helper */
-static void replyGeojsonCollection(redisClient *c, struct geojsonPoint *gp,
-                                   long result_length, char *units) {
-    sds geojson = geojsonFeatureCollection(gp, result_length, units);
-    addReplyBulkCBuffer(c, geojson, sdslen(geojson));
-    sdsfree(geojson);
-}
-
 /* geohash range+zset access helper */
 /* Obtain all members between the min/max of this geohash bounding box. */
 /* Returns list of results.  List must be listRelease()'d later. */
@@ -291,7 +256,7 @@ static int publishLocationUpdate(const sds zset, const sds member,
 
 /* Sort comparators for qsort() */
 static int sort_gp_asc(const void *a, const void *b) {
-    const struct geojsonPoint *gpa = a, *gpb = b;
+    const struct geoPoint *gpa = a, *gpb = b;
     /* We can't do adist - bdist because they are doubles and
      * the comparator returns an int. */
     if (gpa->dist > gpb->dist)
@@ -431,12 +396,8 @@ static void geoRadiusGeneric(redisClient *c, int type) {
         return;
     }
 
-    sds units = c->argv[base_args - 2 + 1]->ptr;
-
     /* Discover and populate all optional parameters. */
-    int withdist = 0, withhash = 0, withcoords = 0,
-         withgeojson = 0, withgeojsonbounds = 0,
-         withgeojsoncollection = 0, noproperties = 0;
+    int withdist = 0, withhash = 0, withcoords = 0, noproperties = 0;
     int sort = SORT_NONE;
     if (c->argc > base_args) {
         int remaining = c->argc - base_args;
@@ -448,14 +409,6 @@ static void geoRadiusGeneric(redisClient *c, int type) {
                 withhash = 1;
             else if (!strncasecmp(arg, "withcoord", 9))
                 withcoords = 1;
-            else if (!strncasecmp(arg, "withgeojsonbound", 16))
-                withgeojsonbounds = 1;
-            else if (!strncasecmp(arg, "withgeojsoncollection", 21))
-                withgeojsoncollection = 1;
-            else if (!strncasecmp(arg, "withgeo", 7) ||
-                     !strcasecmp(arg, "geojson") || !strcasecmp(arg, "json") ||
-                     !strcasecmp(arg, "withjson"))
-                withgeojson = 1;
             else if (!strncasecmp(arg, "noprop", 6) ||
                      !strncasecmp(arg, "withoutprop", 11))
                 noproperties = 1;
@@ -471,8 +424,6 @@ static void geoRadiusGeneric(redisClient *c, int type) {
         }
     }
 
-    int withgeo = withgeojsonbounds || withgeojsoncollection || withgeojson;
-
     /* Get all neighbor geohash boxes for our radius search */
     GeoHashRadius georadius =
         geohashGetAreasByRadiusWGS84(latlong[0], latlong[1], radius_meters);
@@ -508,23 +459,17 @@ static void geoRadiusGeneric(redisClient *c, int type) {
     if (withhash)
         option_length++;
 
-    if (withgeojson)
-        option_length++;
-
-    if (withgeojsonbounds)
-        option_length++;
-
     /* The multibulk len we send is exactly result_length. The result is either
      * all strings of just zset members  *or* a nested multi-bulk reply
      * containing the zset member string _and_ all the additional options the
      * user enabled for this request. */
-    addReplyMultiBulkLen(c, result_length + withgeojsoncollection);
+    addReplyMultiBulkLen(c, result_length);
 
     /* Iterate over results, populate struct used for sorting and result sending
      */
     listIter li;
     listRewind(found_matches, &li);
-    struct geojsonPoint gp[result_length];
+    struct geoPoint gp[result_length];
     /* populate gp array from our results */
     for (int i = 0; i < result_length; i++) {
         struct zipresult *zr = listNodeValue(listNext(&li));
@@ -534,7 +479,7 @@ static void geoRadiusGeneric(redisClient *c, int type) {
         gp[i].dist = zr->distance / conversion;
         gp[i].userdata = zr;
 
-        /* The layout of geojsonPoint allows us to pass the start offset
+        /* The layout of geoPoint allows us to pass the start offset
          * of the struct directly to decodeGeohash. */
         decodeGeohash(zr->score, (double *)(gp + i));
     }
@@ -558,18 +503,14 @@ static void geoRadiusGeneric(redisClient *c, int type) {
         switch (zr->type) {
         case ZR_LONG:
             addReplyBulkLongLong(c, zr->val.v);
-            if (withgeo && !noproperties)
-                gp[i].member = sdscatprintf(sdsempty(), "%llu", zr->val.v);
             break;
         case ZR_STRING:
             addReplyBulkCBuffer(c, zr->val.s, sdslen(zr->val.s));
-            if (withgeo && !noproperties)
-                gp[i].member = sdsdup(zr->val.s);
             break;
         }
 
         if (withdist)
-            addReplyDoubleNicer(c, gp[i].dist);
+            addReplyDoubleMeters(c, gp[i].dist);
 
         if (withhash)
             addReplyLongLong(c, zr->score);
@@ -579,21 +520,7 @@ static void geoRadiusGeneric(redisClient *c, int type) {
             addReplyDouble(c, gp[i].latitude);
             addReplyDouble(c, gp[i].longitude);
         }
-
-        if (withgeojson)
-            latLongToGeojsonAndReply(c, gp + i, units);
-
-        if (withgeojsonbounds)
-            decodeGeohashToGeojsonBoundsAndReply(c, zr->score, gp + i);
     }
-
-    if (withgeojsoncollection)
-        replyGeojsonCollection(c, gp, result_length, units);
-
-    if (withgeo && !noproperties)
-        for (int i = 0; i < result_length; i++)
-            sdsfree(gp[i].member);
-
     listRelease(found_matches);
 }
 
@@ -610,18 +537,11 @@ void geoRadiusByMemberCommand(redisClient *c) {
 }
 
 void geoDecodeCommand(redisClient *c) {
-    /* args 0-1: ["geodecode", geohash];
-     * optional: [geojson] */
-
     GeoHashBits geohash;
     if (getLongLongFromObjectOrReply(c, c->argv[1], (long long *)&geohash.bits,
                                      NULL) != REDIS_OK)
         return;
 
-    int withgeojson = 0;
-    if (c->argc == 3)
-        withgeojson = 1;
-
     GeoHashArea area;
     geohash.step = GEO_STEP_MAX;
     geohashDecodeWGS84(geohash, &area);
@@ -630,7 +550,7 @@ void geoDecodeCommand(redisClient *c) {
     double x = (area.longitude.min + area.longitude.max) / 2;
 
     /* Returning three nested replies */
-    addReplyMultiBulkLen(c, 3 + withgeojson * 2);
+    addReplyMultiBulkLen(c, 3);
 
     /* First, the minimum corner */
     addReplyMultiBulkLen(c, 2);
@@ -646,50 +566,23 @@ void geoDecodeCommand(redisClient *c) {
     addReplyMultiBulkLen(c, 2);
     addReplyDouble(c, y);
     addReplyDouble(c, x);
-
-    if (withgeojson) {
-        struct geojsonPoint gp = { .latitude = y,
-                                   .longitude = x,
-                                   .member = NULL };
-
-        /* Return geojson Feature Point */
-        latLongToGeojsonAndReply(c, &gp, NULL);
-
-        /* Return geojson Feature Polygon */
-        decodeGeohashToGeojsonBoundsAndReply(c, geohash.bits, &gp);
-    }
 }
 
 void geoEncodeCommand(redisClient *c) {
     /* args 0-2: ["geoencode", lat, long];
-     * optionals: [radius, units]
-     * - AND / OR -
-     * optional: [geojson] */
-
-    int withgeojson = 0;
-    for (int i = 3; i < c->argc; i++) {
-        char *arg = c->argv[i]->ptr;
-        if (!strncasecmp(arg, "withgeo", 7) || !strcasecmp(arg, "geojson") ||
-            !strcasecmp(arg, "json") || !strcasecmp(arg, "withjson")) {
-            withgeojson = 1;
-            break;
-        }
-    }
+     * optionals: [radius, units] */
 
     double radius_meters = 0;
     if (c->argc >= 5) {
-        if ((radius_meters = extractDistanceOrReply(c, c->argv + 3, NULL)) <
-            0) {
+        if ((radius_meters = extractDistanceOrReply(c, c->argv + 3, NULL)) < 0)
             return;
-        }
-    } else if (c->argc == 4 && !withgeojson) {
+    } else if (c->argc == 4) {
         addReplyError(c, "must provide units when asking for radius encode");
         return;
     }
 
     double latlong[2];
-    if (!extractLatLongOrReply(c, c->argv + 1, latlong))
-        return;
+    if (!extractLatLongOrReply(c, c->argv + 1, latlong)) return;
 
     /* Encode lat/long into our geohash */
     GeoHashBits geohash;
@@ -709,8 +602,8 @@ void geoEncodeCommand(redisClient *c) {
     double y = (area.latitude.min + area.latitude.max) / 2;
     double x = (area.longitude.min + area.longitude.max) / 2;
 
-    /* Return four nested multibulk replies with optional geojson returns */
-    addReplyMultiBulkLen(c, 4 + withgeojson * 2);
+    /* Return four nested multibulk replies. */
+    addReplyMultiBulkLen(c, 4);
 
     /* Return the binary geohash we calculated as 52-bit integer */
     addReplyLongLong(c, bits);
@@ -729,22 +622,4 @@ void geoEncodeCommand(redisClient *c) {
     addReplyMultiBulkLen(c, 2);
     addReplyDouble(c, y);
     addReplyDouble(c, x);
-
-    if (withgeojson) {
-        struct geojsonPoint gp = { .latitude = y,
-                                   .longitude = x,
-                                   .member = NULL };
-
-        /* Return geojson Feature Point */
-        latLongToGeojsonAndReply(c, &gp, NULL);
-
-        /* Return geojson Feature Polygon (bounding box for this step size) */
-        /* We don't use the helper function here because we can't re-calculate
-         * the area if we have a non-GEO_STEP_MAX step size. */
-        sds geojson = geojsonBoxToPolygonFeature(
-            area.latitude.min, area.longitude.min, area.latitude.max,
-            area.longitude.max, gp.set, gp.member);
-        addReplyBulkCBuffer(c, geojson, sdslen(geojson));
-        sdsfree(geojson);
-    }
 }