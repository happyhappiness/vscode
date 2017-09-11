@@ -89,7 +89,7 @@ int decodeGeohash(double bits, double *xy) {
 /* Input Argument Helper */
 /* Take a pointer to the latitude arg then use the next arg for longitude.
  * On parse error REDIS_ERR is returned, otherwise REDIS_OK. */
-int extractLongLatOrReply(redisClient *c, robj **argv,
+int extractLongLatOrReply(client *c, robj **argv,
                                         double *xy) {
     for (int i = 0; i < 2; i++) {
         if (getDoubleFromObjectOrReply(c, argv[i], xy + i, NULL) !=
@@ -123,7 +123,7 @@ int longLatFromMember(robj *zobj, robj *member, double *xy) {
  *
  * If the unit is not valid, an error is reported to the client, and a value
  * less than zero is returned. */
-double extractUnitOrReply(redisClient *c, robj *unit) {
+double extractUnitOrReply(client *c, robj *unit) {
     char *u = unit->ptr;
 
     if (!strcmp(u, "m")) {
@@ -148,7 +148,7 @@ double extractUnitOrReply(redisClient *c, robj *unit) {
  * to use in order to convert meters to the unit.
  *
  * On error a value less than zero is returned. */
-double extractDistanceOrReply(redisClient *c, robj **argv,
+double extractDistanceOrReply(client *c, robj **argv,
                                      double *conversion) {
     double distance;
     if (getDoubleFromObjectOrReply(c, argv[0], &distance,
@@ -168,7 +168,7 @@ double extractDistanceOrReply(redisClient *c, robj **argv,
  * than "5.2144992818115 meters away." We provide 4 digits after the dot
  * so that the returned value is decently accurate even when the unit is
  * the kilometer. */
-void addReplyDoubleDistance(redisClient *c, double d) {
+void addReplyDoubleDistance(client *c, double d) {
     char dbuf[128];
     int dlen = snprintf(dbuf, sizeof(dbuf), "%.4f", d);
     addReplyBulkCBuffer(c, dbuf, dlen);
@@ -363,7 +363,7 @@ static int sort_gp_desc(const void *a, const void *b) {
  * ==================================================================== */
 
 /* GEOADD key long lat name [long2 lat2 name2 ... longN latN nameN] */
-void geoaddCommand(redisClient *c) {
+void geoaddCommand(client *c) {
     /* Check arguments number for sanity. */
     if ((c->argc - 2) % 3 != 0) {
         /* Need an odd number of arguments if we got this far... */
@@ -419,7 +419,7 @@ void geoaddCommand(redisClient *c) {
 /* GEORADIUS key x y radius unit [WITHDIST] [WITHHASH] [WITHCOORD] [ASC|DESC]
  *                               [COUNT count]
  * GEORADIUSBYMEMBER key member radius unit ... options ... */
-void georadiusGeneric(redisClient *c, int type) {
+void georadiusGeneric(client *c, int type) {
     robj *key = c->argv[1];
 
     /* Look up the requested zset */
@@ -569,20 +569,20 @@ void georadiusGeneric(redisClient *c, int type) {
 }
 
 /* GEORADIUS wrapper function. */
-void georadiusCommand(redisClient *c) {
+void georadiusCommand(client *c) {
     georadiusGeneric(c, RADIUS_COORDS);
 }
 
 /* GEORADIUSBYMEMBER wrapper function. */
-void georadiusByMemberCommand(redisClient *c) {
+void georadiusByMemberCommand(client *c) {
     georadiusGeneric(c, RADIUS_MEMBER);
 }
 
 /* GEOHASH key ele1 ele2 ... eleN
  *
  * Returns an array with an 11 characters geohash representation of the
  * position of the specified elements. */
-void geohashCommand(redisClient *c) {
+void geohashCommand(client *c) {
     char *geoalphabet= "0123456789bcdefghjkmnpqrstuvwxyz";
     int j;
 
@@ -637,7 +637,7 @@ void geohashCommand(redisClient *c) {
  *
  * Returns an array of two-items arrays representing the x,y position of each
  * element specified in the arguments. For missing elements NULL is returned. */
-void geoposCommand(redisClient *c) {
+void geoposCommand(client *c) {
     int j;
 
     /* Look up the requested zset */
@@ -671,7 +671,7 @@ void geoposCommand(redisClient *c) {
  * Return the distance, in meters by default, otherwise accordig to "unit",
  * between points ele1 and ele2. If one or more elements are missing NULL
  * is returned. */
-void geodistCommand(redisClient *c) {
+void geodistCommand(client *c) {
     double to_meter = 1;
 
     /* Check if there is the unit to extract, otherwise assume meters. */