@@ -82,15 +82,15 @@ void geoArrayFree(geoArray *ga) {
 /* ====================================================================
  * Helpers
  * ==================================================================== */
-static inline int decodeGeohash(double bits, double *xy) {
+int decodeGeohash(double bits, double *xy) {
     GeoHashBits hash = { .bits = (uint64_t)bits, .step = GEO_STEP_MAX };
     return geohashDecodeToLongLatWGS84(hash, xy);
 }
 
 /* Input Argument Helper */
 /* Take a pointer to the latitude arg then use the next arg for longitude.
  * On parse error REDIS_ERR is returned, otherwise REDIS_OK. */
-static inline int extractLongLatOrReply(redisClient *c, robj **argv,
+int extractLongLatOrReply(redisClient *c, robj **argv,
                                         double *xy) {
     for (int i = 0; i < 2; i++) {
         if (getDoubleFromObjectOrReply(c, argv[i], xy + i, NULL) !=
@@ -104,7 +104,7 @@ static inline int extractLongLatOrReply(redisClient *c, robj **argv,
 /* Input Argument Helper */
 /* Decode lat/long from a zset member's score.
  * Returns REDIS_OK on successful decoding, otherwise REDIS_ERR is returned. */
-static int longLatFromMember(robj *zobj, robj *member, double *xy) {
+int longLatFromMember(robj *zobj, robj *member, double *xy) {
     double score = 0;
 
     if (zsetScore(zobj, member, &score) == REDIS_ERR) return REDIS_ERR;
@@ -143,7 +143,7 @@ double extractUnitOrReply(redisClient *c, robj *unit) {
  * to use in order to convert meters to the unit.
  *
  * On error a value less than zero is returned. */
-static double extractDistanceOrReply(redisClient *c, robj **argv,
+double extractDistanceOrReply(redisClient *c, robj **argv,
                                      double *conversion) {
     double distance;
     if (getDoubleFromObjectOrReply(c, argv[0], &distance,
@@ -163,7 +163,7 @@ static double extractDistanceOrReply(redisClient *c, robj **argv,
  * than "5.2144992818115 meters away." We provide 4 digits after the dot
  * so that the returned value is decently accurate even when the unit is
  * the kilometer. */
-static inline void addReplyDoubleDistance(redisClient *c, double d) {
+inline void addReplyDoubleDistance(redisClient *c, double d) {
     char dbuf[128];
     int dlen = snprintf(dbuf, sizeof(dbuf), "%.4f", d);
     addReplyBulkCBuffer(c, dbuf, dlen);
@@ -414,7 +414,7 @@ void geoaddCommand(redisClient *c) {
 /* GEORADIUS key x y radius unit [WITHDIST] [WITHHASH] [WITHCOORD] [ASC|DESC]
  *                               [COUNT count]
  * GEORADIUSBYMEMBER key member radius unit ... options ... */
-static void georadiusGeneric(redisClient *c, int type) {
+void georadiusGeneric(redisClient *c, int type) {
     robj *key = c->argv[1];
 
     /* Look up the requested zset */