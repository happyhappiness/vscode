@@ -653,7 +653,7 @@ int loadAppendOnlyFile(char *filename) {
         serverLog(LL_NOTICE,"Reading RDB preamble from AOF file...");
         if (fseek(fp,0,SEEK_SET) == -1) goto readerr;
         rioInitWithFile(&rdb,fp);
-        if (rdbLoadRio(&rdb) != C_OK) {
+        if (rdbLoadRio(&rdb,NULL) != C_OK) {
             serverLog(LL_WARNING,"Error reading the RDB preamble of the AOF file, AOF loading aborted");
             goto readerr;
         } else {
@@ -1152,7 +1152,7 @@ int rewriteAppendOnlyFile(char *filename) {
 
     if (server.aof_use_rdb_preamble) {
         int error;
-        if (rdbSaveRio(&aof,&error,RDB_SAVE_AOF_PREAMBLE) == C_ERR) {
+        if (rdbSaveRio(&aof,&error,RDB_SAVE_AOF_PREAMBLE,NULL) == C_ERR) {
             errno = error;
             goto werr;
         }