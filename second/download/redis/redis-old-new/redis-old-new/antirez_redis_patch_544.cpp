@@ -110,11 +110,13 @@ static double extractDistanceOrReply(redisClient *c, robj **argv,
 }
 
 /* The defailt addReplyDouble has too much accuracy.  We use this
- * for returning location distances. "5.21 meters away" is nicer
- * than "5.2144992818115 meters away." */
-static inline void addReplyDoubleMeters(redisClient *c, double d) {
-    char dbuf[128] = { 0 };
-    int dlen = snprintf(dbuf, sizeof(dbuf), "%.2f", d);
+ * for returning location distances. "5.2145 meters away" is nicer
+ * than "5.2144992818115 meters away." We provide 4 digits after the dot
+ * so that the returned value is decently accurate even when the unit is
+ * the kilometer. */
+static inline void addReplyDoubleDistance(redisClient *c, double d) {
+    char dbuf[128];
+    int dlen = snprintf(dbuf, sizeof(dbuf), "%.4f", d);
     addReplyBulkCBuffer(c, dbuf, dlen);
 }
 
@@ -510,7 +512,7 @@ static void geoRadiusGeneric(redisClient *c, int type) {
         }
 
         if (withdist)
-            addReplyDoubleMeters(c, gp[i].dist);
+            addReplyDoubleDistance(c, gp[i].dist);
 
         if (withhash)
             addReplyLongLong(c, zr->score);