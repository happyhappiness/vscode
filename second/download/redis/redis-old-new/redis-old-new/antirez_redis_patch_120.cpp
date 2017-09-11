@@ -1024,7 +1024,7 @@ int rdbSaveBackground(char *filename) {
         redisSetProcTitle("redis-rdb-bgsave");
         retval = rdbSave(filename);
         if (retval == C_OK) {
-            size_t private_dirty = zmalloc_get_private_dirty();
+            size_t private_dirty = zmalloc_get_private_dirty(-1);
 
             if (private_dirty) {
                 serverLog(LL_NOTICE,
@@ -1761,7 +1761,7 @@ int rdbSaveToSlavesSockets(void) {
             retval = C_ERR;
 
         if (retval == C_OK) {
-            size_t private_dirty = zmalloc_get_private_dirty();
+            size_t private_dirty = zmalloc_get_private_dirty(-1);
 
             if (private_dirty) {
                 serverLog(LL_NOTICE,