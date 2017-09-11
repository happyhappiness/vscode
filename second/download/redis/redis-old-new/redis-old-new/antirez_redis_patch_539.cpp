@@ -318,8 +318,6 @@ void geoAddCommand(redisClient *c) {
     /* args 0-4: [cmd, key, lat, lng, val]; optional 5-6: [radius, units]
      * - OR -
      * args 0-N: [cmd, key, lat, lng, val, lat2, lng2, val2, ...] */
-    robj *cmd = c->argv[0];
-    robj *key = c->argv[1];
 
     /* Prepare for the three different forms of the add command. */
     double radius_meters = 0;
@@ -338,56 +336,49 @@ void geoAddCommand(redisClient *c) {
         return;
     }
 
-    redisClient *client = c;
     int elements = (c->argc - 2) / 3;
-    /* elements will always be correct size (integer math floors for us if we
-     * have 6 or 7 total arguments) */
-    if (elements > 1) {
-        /* We should probably use a static client and not create/free it
-         * for every multi-add */
-        client = createClient(-1); /* fake client for multi-zadd */
-
-        /* Tell fake client to use the same DB as our calling client. */
-        selectDb(client, c->db->id);
-    }
+    int argc = 2+elements*2; /* ZADD key score ele ... */
+    robj **argv = zcalloc(argc*sizeof(robj*));
+    argv[0] = createRawStringObject("zadd",4);
+    argv[1] = c->argv[1]; /* key */
+    incrRefCount(argv[1]);
+
+    /* Create the argument vector to call ZADD in order to add all
+     * the score,value pairs to the requested zset, where score is actually
+     * an encoded version of lat,long. */
+    uint8_t step = geohashEstimateStepsByRadius(radius_meters);
+    int i;
+    for (i = 0; i < elements; i++) {
+        double latlong[elements * 2];
 
-    /* Capture all lat/long components up front so if we encounter an error we
-     * return before making any changes to the database. */
-    double latlong[elements * 2];
-    for (int i = 0; i < elements; i++) {
-        if (!extractLatLongOrReply(c, (c->argv + 2) + (i * 3),
-                                   latlong + (i * 2)))
+        if (!extractLatLongOrReply(c, (c->argv+2)+(i*3),latlong)) {
+            for (i = 0; i < argc; i++)
+                if (argv[i]) decrRefCount(argv[i]);
+            zfree(argv);
             return;
-    }
-
-    /* Add all (lat, long, value) triples to the requested zset */
-    for (int i = 0; i < elements; i++) {
-        uint8_t step = geohashEstimateStepsByRadius(radius_meters);
+        }
 
 #ifdef DEBUG
         printf("Adding with step size: %d\n", step);
 #endif
+
+        /* Turn the coordinates into the score of the element. */
         GeoHashBits hash;
-        int ll_offset = i * 2;
-        double latitude = latlong[ll_offset];
-        double longitude = latlong[ll_offset + 1];
+        double latitude = latlong[0];
+        double longitude = latlong[1];
         geohashEncodeWGS84(latitude, longitude, step, &hash);
 
         GeoHashFix52Bits bits = geohashAlign52Bits(hash);
         robj *score = createObject(REDIS_STRING, sdsfromlonglong(bits));
         robj *val = c->argv[2 + i * 3 + 2];
-        /* (base args) + (offset for this triple) + (offset of value arg) */
-
-        rewriteClientCommandVector(client, 4, cmd, key, score, val);
-        decrRefCount(score);
-        zaddCommand(client);
+        argv[2+i*2] = score;
+        argv[3+i*2] = val;
+        incrRefCount(val);
     }
 
-    /* If we used a fake client, return a real reply then free fake client. */
-    if (client != c) {
-        addReplyLongLong(c, elements);
-        freeClient(client);
-    }
+    /* Finally call ZADD that will do the work for us. */
+    replaceClientCommandVector(c,argc,argv);
+    zaddCommand(c);
 }
 
 #define SORT_NONE 0