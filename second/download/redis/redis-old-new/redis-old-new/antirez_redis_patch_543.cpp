@@ -225,37 +225,6 @@ static list *membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double x,
     return l;
 }
 
-/* With no subscribers, each call of this function adds a median latency of 2
- * microseconds. */
-/* We aren't participating in any keyspace/keyevent notifications other than
- * what's provided by the underlying zset itself, but it's probably not useful
- * for clients to get the 52-bit integer geohash as an "update" value. */
-static int publishLocationUpdate(const sds zset, const sds member,
-                                 const double latitude,
-                                 const double longitude) {
-    int published;
-
-    /* event is: "<latitude> <longitude>" */
-    sds event = sdscatprintf(sdsempty(), "%.7f %.7f", latitude, longitude);
-    robj *eventobj = createObject(REDIS_STRING, event);
-
-    /* channel is: __geo:<zset>:<member> */
-    /* If you want all events for this zset then just psubscribe
-     * to "__geo:<zset>:*" */
-    sds chan = sdsnewlen("__geo:", 6);
-    chan = sdscatsds(chan, zset);
-    chan = sdscatlen(chan, ":", 1);
-    chan = sdscatsds(chan, member);
-    robj *chanobj = createObject(REDIS_STRING, chan);
-
-    published = pubsubPublishMessage(chanobj, eventobj);
-
-    decrRefCount(chanobj);
-    decrRefCount(eventobj);
-
-    return published;
-}
-
 /* Sort comparators for qsort() */
 static int sort_gp_asc(const void *a, const void *b) {
     const struct geoPoint *gpa = a, *gpb = b;
@@ -343,7 +312,6 @@ void geoAddCommand(redisClient *c) {
         rewriteClientCommandVector(client, 4, cmd, key, score, val);
         decrRefCount(score);
         zaddCommand(client);
-        publishLocationUpdate(key->ptr, val->ptr, latitude, longitude);
     }
 
     /* If we used a fake client, return a real reply then free fake client. */