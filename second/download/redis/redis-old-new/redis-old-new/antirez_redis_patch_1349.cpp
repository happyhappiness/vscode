@@ -602,6 +602,7 @@ int rdbSave(char *filename) {
     dictIterator *di = NULL;
     dictEntry *de;
     char tmpfile[256];
+    char magic[10];
     int j;
     long long now = mstime();
     FILE *fp;
@@ -616,7 +617,8 @@ int rdbSave(char *filename) {
     }
 
     rioInitWithFile(&rdb,fp);
-    if (rdbWriteRaw(&rdb,"REDIS0004",9) == -1) goto werr;
+    snprintf(magic,sizeof(magic),"REDIS%04d",REDIS_RDB_VERSION);
+    if (rdbWriteRaw(&rdb,magic,9) == -1) goto werr;
 
     for (j = 0; j < server.dbnum; j++) {
         redisDb *db = server.db+j;