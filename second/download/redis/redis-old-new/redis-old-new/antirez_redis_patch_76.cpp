@@ -217,6 +217,139 @@ void activeExpireCycle(int type) {
 }
 
 /*-----------------------------------------------------------------------------
+ * Expires of keys crated in writable slaves
+ *
+ * Normally slaves do not process expires: they wait the masters to synthesize
+ * DEL operations in order to retain consistency. However writable slaves are
+ * an exception: if a key is created in the slave and an expire is assigned
+ * to it, we need a way to expire such a key, since the master does not know
+ * anything about such a key.
+ *
+ * In order to do so, we track keys created in the slave side with an expire
+ * set, and call the expireSlaveKeys() function from time to time in order to
+ * reclaim the keys if they already expired.
+ *
+ * Note that the use case we are trying to cover here, is a popular one where
+ * slaves are put in writable mode in order to compute slow operations in
+ * the slave side that are mostly useful to actually read data in a more
+ * processed way. Think at sets intersections in a tmp key, with an expire so
+ * that it is also used as a cache to avoid intersecting every time.
+ *
+ * This implementation is currently not perfect but a lot better than leaking
+ * the keys as implemented in 3.2.
+ *----------------------------------------------------------------------------*/
+
+/* The dictionary where we remember key names and database ID of keys we may
+ * want to expire from the slave. Since this function is not often used we
+ * don't even care to initialize the database at startup. We'll do it once
+ * the feature is used the first time, that is, when rememberSlaveKeyWithExpire()
+ * is called.
+ *
+ * The dictionary has an SDS string representing the key as the hash table
+ * key, while the value is a 64 bit unsigned integer with the bits corresponding
+ * to the DB where the keys may exist set to 1. Currently the keys created
+ * with a DB id > 63 are not expired, but a trivial fix is to set the bitmap
+ * to the max 64 bit unsigned value when we know there is a key with a DB
+ * ID greater than 63, and check all the configured DBs in such a case. */
+dict *slaveKeysWithExpire = NULL;
+
+/* Check the set of keys created by the master with an expire set in order to
+ * check if they should be evicted. */
+void expireSlaveKeys(void) {
+    if (slaveKeysWithExpire == NULL ||
+        dictSize(slaveKeysWithExpire) == 0) return;
+
+    int cycles = 0, noexpire = 0;
+    mstime_t start = mstime();
+    while(1) {
+        dictEntry *de = dictGetRandomKey(slaveKeysWithExpire);
+        sds keyname = dictGetKey(de);
+        uint64_t dbids = dictGetUnsignedIntegerVal(de);
+        uint64_t new_dbids = 0;
+
+        /* Check the key against every database corresponding to the
+         * bits set in the value bitmap. */
+        int dbid = 0;
+        while(dbids && dbid < server.dbnum) {
+            if ((dbids & 1) != 0) {
+                redisDb *db = server.db+dbid;
+                dictEntry *expire = dictFind(db->expires,keyname);
+                int expired = 0;
+
+                if (expire &&
+                    activeExpireCycleTryExpire(server.db+dbid,expire,start))
+                {
+                    expired = 1;
+                }
+
+                /* If the key was not expired in this DB, we need to set the
+                 * corresponding bit in the new bitmap we set as value.
+                 * At the end of the loop if the bitmap is zero, it means we
+                 * no longer need to keep track of this key. */
+                if (expire && !expired) {
+                    noexpire++;
+                    new_dbids |= (uint64_t)1 << dbid;
+                }
+            }
+            dbid++;
+            dbids >>= 1;
+        }
+
+        /* Set the new bitmap as value of the key, in the dictionary
+         * of keys with an expire set directly in the writable slave. Otherwise
+         * if the bitmap is zero, we no longer need to keep track of it. */
+        if (new_dbids)
+            dictSetUnsignedIntegerVal(de,new_dbids);
+        else
+            dictDelete(slaveKeysWithExpire,keyname);
+
+        /* Stop conditions: found 3 keys we cna't expire in a row or
+         * time limit was reached. */
+        cycles++;
+        if (noexpire > 3) break;
+        if ((cycles % 64) == 0 && mstime()-start > 1) break;
+        if (dictSize(slaveKeysWithExpire) == 0) break;
+    }
+}
+
+/* Track keys that received an EXPIRE or similar command in the context
+ * of a writable slave. */
+void rememberSlaveKeyWithExpire(redisDb *db, robj *key) {
+    if (slaveKeysWithExpire == NULL)
+        slaveKeysWithExpire = dictCreate(&keyptrDictType,NULL);
+    if (db->id > 63) return;
+
+    dictEntry *de = dictAddOrFind(slaveKeysWithExpire,key->ptr);
+    /* If the entry was just created, set it to a copy of the SDS string
+     * representing the key: we don't want to need to take those keys
+     * in sync with the main DB. The keys will be removed by expireSlaveKeys()
+     * as it scans to find keys to remove. */
+    if (de->key == key->ptr) {
+        de->key = sdsdup(key->ptr);
+        dictSetUnsignedIntegerVal(de,0);
+    }
+
+    uint64_t dbids = dictGetUnsignedIntegerVal(de);
+    dbids |= (uint64_t)1 << db->id;
+    dictSetUnsignedIntegerVal(de,dbids);
+}
+
+/* Remove the keys in the hash table. We need to do that when data is
+ * flushed from the server. We may receive new keys from the master with
+ * the same name/db and it is no longer a good idea to expire them.
+ *
+ * Note: technically we should handle the case of a single DB being flushed
+ * but it is not worth it since anyway race conditions using the same set
+ * of key names in a wriatable slave and in its master will lead to
+ * inconsistencies. This is just a best-effort thing we do. */
+void flushSlaveKeysWithExpireList(void) {
+    if (slaveKeysWithExpire) {
+        dictRelease(slaveKeysWithExpire);
+        slaveKeysWithExpire = NULL;
+    }
+}
+
+/*-----------------------------------------------------------------------------
  * Expires Commands
  *----------------------------------------------------------------------------*/
 
@@ -265,7 +398,7 @@ void expireGenericCommand(client *c, long long basetime, int unit) {
         addReply(c, shared.cone);
         return;
     } else {
-        setExpire(c->db,key,when);
+        setExpire(c,c->db,key,when);
         addReply(c,shared.cone);
         signalModifiedKey(c->db,key);
         notifyKeyspaceEvent(NOTIFY_GENERIC,"expire",key,c->db->id);