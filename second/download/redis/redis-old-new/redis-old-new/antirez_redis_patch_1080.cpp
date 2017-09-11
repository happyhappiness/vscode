@@ -759,10 +759,14 @@ void activeExpireCycle(int type) {
          * of the keys were expired. */
         do {
             unsigned long num, slots;
-            long long now;
+            long long now, ttl_sum;
+            int ttl_samples;
 
             /* If there is nothing to expire try next DB ASAP. */
-            if ((num = dictSize(db->expires)) == 0) break;
+            if ((num = dictSize(db->expires)) == 0) {
+                db->avg_ttl = 0;
+                break;
+            }
             slots = dictSlots(db->expires);
             now = mstime();
 
@@ -775,14 +779,33 @@ void activeExpireCycle(int type) {
             /* The main collection cycle. Sample random keys among keys
              * with an expire set, checking for expired ones. */
             expired = 0;
+            ttl_sum = 0;
+            ttl_samples = 0;
+
             if (num > ACTIVE_EXPIRE_CYCLE_LOOKUPS_PER_LOOP)
                 num = ACTIVE_EXPIRE_CYCLE_LOOKUPS_PER_LOOP;
+
             while (num--) {
                 dictEntry *de;
+                long long ttl;
 
                 if ((de = dictGetRandomKey(db->expires)) == NULL) break;
+                ttl = dictGetSignedIntegerVal(de)-now;
                 if (activeExpireCycleTryExpire(db,de,now)) expired++;
+                if (ttl < 0) ttl = 0;
+                ttl_sum += ttl;
+                ttl_samples++;
             }
+
+            /* Update the average TTL stats for this database. */
+            if (ttl_samples) {
+                long long avg_ttl = ttl_sum/ttl_samples;
+
+                if (db->avg_ttl == 0) db->avg_ttl = avg_ttl;
+                /* Smooth the value averaging with the previous one. */
+                db->avg_ttl = (db->avg_ttl+avg_ttl)/2;
+            }
+
             /* We can't block forever here even if there are many keys to
              * expire. So after a given amount of milliseconds return to the
              * caller waiting for the other active expire cycle. */
@@ -1530,6 +1553,7 @@ void initServer() {
         server.db[j].ready_keys = dictCreate(&setDictType,NULL);
         server.db[j].watched_keys = dictCreate(&keylistDictType,NULL);
         server.db[j].id = j;
+        server.db[j].avg_ttl = 0;
     }
     server.pubsub_channels = dictCreate(&keylistDictType,NULL);
     server.pubsub_patterns = listCreate();
@@ -2580,8 +2604,9 @@ sds genRedisInfoString(char *section) {
             keys = dictSize(server.db[j].dict);
             vkeys = dictSize(server.db[j].expires);
             if (keys || vkeys) {
-                info = sdscatprintf(info, "db%d:keys=%lld,expires=%lld\r\n",
-                    j, keys, vkeys);
+                info = sdscatprintf(info,
+                    "db%d:keys=%lld,expires=%lld,avg_ttl=%lld\r\n",
+                    j, keys, vkeys, server.db[j].avg_ttl);
             }
         }
     }