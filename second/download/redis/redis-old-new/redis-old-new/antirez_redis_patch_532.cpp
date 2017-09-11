@@ -112,6 +112,30 @@ static int longLatFromMember(robj *zobj, robj *member, double *xy) {
     return REDIS_OK;
 }
 
+/* Check that the unit argument matches one of the known units, and returns
+ * the conversion factor to meters (you need to divide meters by the conversion
+ * factor to convert to the right unit).
+ *
+ * If the unit is not valid, an error is reported to the client, and a value
+ * less than zero is returned. */
+double extractUnitOrReply(redisClient *c, robj *unit) {
+    char *u = unit->ptr;
+
+    if (!strcmp(u, "m") || !strncmp(u, "meter", 5)) {
+        return 1;
+    } else if (!strcmp(u, "ft") || !strncmp(u, "feet", 4)) {
+        return 0.3048;
+    } else if (!strcmp(u, "mi") || !strncmp(u, "mile", 4)) {
+        return 1609.34;
+    } else if (!strcmp(u, "km") || !strncmp(u, "kilometer", 9)) {
+        return 1000;
+    } else {
+        addReplyError(c, "unsupported unit provided. please use meters (m), "
+                         "kilometers (km), miles (mi), or feet (ft)");
+        return -1;
+    }
+}
+
 /* Input Argument Helper.
  * Extract the dinstance from the specified two arguments starting at 'argv'
  * that shouldbe in the form: <number> <unit> and return the dinstance in the
@@ -127,25 +151,10 @@ static double extractDistanceOrReply(redisClient *c, robj **argv,
         return -1;
     }
 
-    double to_meters;
-    sds units = argv[1]->ptr;
-    if (!strcmp(units, "m") || !strncmp(units, "meter", 5)) {
-        to_meters = 1;
-    } else if (!strcmp(units, "ft") || !strncmp(units, "feet", 4)) {
-        to_meters = 0.3048;
-    } else if (!strcmp(units, "mi") || !strncmp(units, "mile", 4)) {
-        to_meters = 1609.34;
-    } else if (!strcmp(units, "km") || !strncmp(units, "kilometer", 9)) {
-        to_meters = 1000;
-    } else {
-        addReplyError(c, "unsupported unit provided. please use meters (m), "
-                         "kilometers (km), miles (mi), or feet (ft)");
-        return -1;
-    }
-
-    if (conversion)
-        *conversion = to_meters;
+    double to_meters = extractUnitOrReply(c,argv[1]);
+    if (to_meters < 0) return -1;
 
+    if (conversion) *conversion = to_meters;
     return distance * to_meters;
 }
 
@@ -742,3 +751,42 @@ void geoposCommand(redisClient *c) {
         }
     }
 }
+
+/* GEODIST key ele1 ele2 [unit]
+ *
+ * Return the distance, in meters by default, otherwise accordig to "unit",
+ * between points ele1 and ele2. If one or more elements are missing NULL
+ * is returned. */
+void geodistCommand(redisClient *c) {
+    double to_meter = 1;
+
+    /* Check if there is the unit to extract, otherwise assume meters. */
+    if (c->argc == 5) {
+        to_meter = extractUnitOrReply(c,c->argv[4]);
+        if (to_meter < 0) return;
+    } else if (c->argc > 5) {
+        addReply(c,shared.syntaxerr);
+        return;
+    }
+
+    /* Look up the requested zset */
+    robj *zobj = NULL;
+    if ((zobj = lookupKeyReadOrReply(c, c->argv[1], shared.emptybulk))
+        == NULL || checkType(c, zobj, REDIS_ZSET)) return;
+
+    /* Get the scores. We need both otherwise NULL is returned. */
+    double score1, score2, xyxy[4];
+    if (zsetScore(zobj, c->argv[2], &score1) == REDIS_ERR ||
+        zsetScore(zobj, c->argv[3], &score2) == REDIS_ERR)
+    {
+        addReply(c,shared.nullbulk);
+        return;
+    }
+
+    /* Decode & compute the distance. */
+    if (!decodeGeohash(score1,xyxy) || !decodeGeohash(score2,xyxy+2))
+        addReply(c,shared.nullbulk);
+    else
+        addReplyDouble(c,
+            geohashGetDistance(xyxy[0],xyxy[1],xyxy[2],xyxy[3]) / to_meter);
+}