 
 void
 storeIOWrite(StoreIOState::Pointer sio, char const *buf, size_t size, off_t offset, FREE * free_func)
 {
     sio->write(buf,size,offset,free_func);
 }
-
-/*
- * Make this non-static so we can register
- * it from storeInit();
- */
-void
-storeIOStats(StoreEntry * sentry)
-{
-    storeAppendPrintf(sentry, "Store IO Interface Stats\n");
-    storeAppendPrintf(sentry, "create.calls %d\n", store_io_stats.create.calls);
-    storeAppendPrintf(sentry, "create.select_fail %d\n", store_io_stats.create.select_fail);
-    storeAppendPrintf(sentry, "create.create_fail %d\n", store_io_stats.create.create_fail);
-    storeAppendPrintf(sentry, "create.success %d\n", store_io_stats.create.success);
-}
