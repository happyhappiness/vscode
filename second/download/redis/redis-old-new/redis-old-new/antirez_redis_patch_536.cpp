@@ -413,7 +413,7 @@ void geoAddCommand(redisClient *c) {
 #define RADIUS_MEMBER 2
 
 /* GEORADIUS key x y radius unit [WITHDIST] [WITHHASH] [WITHCOORD] [ASC|DESC]
- *           [LIMIT count]
+ *                               [COUNT count]
  * GEORADIUSBYMEMBER key member radius unit ... options ... */
 static void geoRadiusGeneric(redisClient *c, int type) {
     robj *key = c->argv[1];
@@ -454,6 +454,7 @@ static void geoRadiusGeneric(redisClient *c, int type) {
     /* Discover and populate all optional parameters. */
     int withdist = 0, withhash = 0, withcoords = 0;
     int sort = SORT_NONE;
+    long long count = 0;
     if (c->argc > base_args) {
         int remaining = c->argc - base_args;
         for (int i = 0; i < remaining; i++) {
@@ -468,13 +469,25 @@ static void geoRadiusGeneric(redisClient *c, int type) {
                 sort = SORT_ASC;
             } else if (!strcasecmp(arg, "desc")) {
                 sort = SORT_DESC;
+            } else if (!strcasecmp(arg, "count") && remaining > 0) {
+                if (getLongLongFromObjectOrReply(c, c->argv[base_args+i+1],
+                    &count, NULL) != REDIS_OK) return;
+                if (count <= 0) {
+                    addReplyError(c,"COUNT must be > 0");
+                    return;
+                }
+                i++;
             } else {
                 addReply(c, shared.syntaxerr);
                 return;
             }
         }
     }
 
+    /* COUNT without ordering does not make much sense, force ASC
+     * ordering if COUNT was specified but no sorting was requested. */
+    if (count != 0 && sort == SORT_NONE) sort = SORT_ASC;
+
     /* Get all neighbor geohash boxes for our radius search */
     GeoHashRadius georadius =
         geohashGetAreasByRadiusWGS84(xy[0], xy[1], radius_meters);
@@ -512,7 +525,8 @@ static void geoRadiusGeneric(redisClient *c, int type) {
      * all strings of just zset members  *or* a nested multi-bulk reply
      * containing the zset member string _and_ all the additional options the
      * user enabled for this request. */
-    addReplyMultiBulkLen(c, result_length);
+    addReplyMultiBulkLen(c, (count == 0 || result_length < count) ?
+                            result_length : count);
 
     /* Process [optional] requested sorting */
     if (sort == SORT_ASC) {
@@ -546,6 +560,10 @@ static void geoRadiusGeneric(redisClient *c, int type) {
             addReplyDouble(c, gp->longitude);
             addReplyDouble(c, gp->latitude);
         }
+
+        /* Stop if COUNT was specified and we already provided the
+         * specified number of elements. */
+        if (count != 0 && count == i+1) break;
     }
     geoArrayFree(ga);
 }