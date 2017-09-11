@@ -476,10 +476,6 @@ static void geoRadiusGeneric(redisClient *c, int type) {
     GeoHashRadius georadius =
         geohashGetAreasByRadiusWGS84(xy[0], xy[1], radius_meters);
 
-#ifdef DEBUG
-    printf("Searching with step size: %d\n", georadius.hash.step);
-#endif
-
     /* Search the zset for all matching points */
     geoArray *ga = geoArrayCreate();
     membersOfAllNeighbors(zobj, georadius, xy[0], xy[1], radius_meters, ga);
@@ -618,9 +614,6 @@ void geoEncodeCommand(redisClient *c) {
     GeoHashFix52Bits bits = geohashAlign52Bits(geohash);
 
 /* Decode the hash so we can return its bounding box */
-#ifdef DEBUG
-    printf("Decoding with step size: %d\n", geohash.step);
-#endif
     GeoHashArea area;
     geohashDecodeWGS84(geohash, &area);
 