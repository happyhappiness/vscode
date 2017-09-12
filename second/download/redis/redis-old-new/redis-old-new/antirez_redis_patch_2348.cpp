@@ -89,6 +89,7 @@
 #define REDIS_HASH 3
 
 /* Object types only used for dumping to disk */
+#define REDIS_EXPIRETIME 253
 #define REDIS_SELECTDB 254
 #define REDIS_EOF 255
 
@@ -288,6 +289,8 @@ static int removeExpire(redisDb *db, robj *key);
 static int expireIfNeeded(redisDb *db, robj *key);
 static int deleteIfVolatile(redisDb *db, robj *key);
 static int deleteKey(redisDb *db, robj *key);
+static time_t getExpire(redisDb *db, robj *key);
+static int setExpire(redisDb *db, robj *key, time_t when);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -1585,6 +1588,12 @@ static int rdbSaveType(FILE *fp, unsigned char type) {
     return 0;
 }
 
+static int rdbSaveTime(FILE *fp, time_t t) {
+    int32_t t32 = (int32_t) t;
+    if (fwrite(&t32,4,1,fp) == 0) return -1;
+    return 0;
+}
+
 /* check rdbLoadLen() comments for more info */
 static int rdbSaveLen(FILE *fp, uint32_t len) {
     unsigned char buf[2];
@@ -1713,6 +1722,7 @@ static int rdbSave(char *filename) {
     FILE *fp;
     char tmpfile[256];
     int j;
+    time_t now = time(NULL);
 
     snprintf(tmpfile,256,"temp-%d.%ld.rdb",(int)time(NULL),(long int)random());
     fp = fopen(tmpfile,"w");
@@ -1722,7 +1732,8 @@ static int rdbSave(char *filename) {
     }
     if (fwrite("REDIS0001",9,1,fp) == 0) goto werr;
     for (j = 0; j < server.dbnum; j++) {
-        dict *d = server.db[j].dict;
+        redisDb *db = server.db+j;
+        dict *d = db->dict;
         if (dictSize(d) == 0) continue;
         di = dictGetIterator(d);
         if (!di) {
@@ -1738,7 +1749,16 @@ static int rdbSave(char *filename) {
         while((de = dictNext(di)) != NULL) {
             robj *key = dictGetEntryKey(de);
             robj *o = dictGetEntryVal(de);
-
+            time_t expiretime = getExpire(db,key);
+
+            /* Save the expire time */
+            if (expiretime != -1) {
+                /* If this key is already expired skip it */
+                if (expiretime < now) continue;
+                if (rdbSaveType(fp,REDIS_EXPIRETIME) == -1) goto werr;
+                if (rdbSaveTime(fp,expiretime) == -1) goto werr;
+            }
+            /* Save the key and associated value */
             if (rdbSaveType(fp,o->type) == -1) goto werr;
             if (rdbSaveStringObject(fp,key) == -1) goto werr;
             if (o->type == REDIS_STRING) {
@@ -1831,6 +1851,12 @@ static int rdbLoadType(FILE *fp) {
     return type;
 }
 
+static time_t rdbLoadTime(FILE *fp) {
+    int32_t t32;
+    if (fread(&t32,4,1,fp) == 0) return -1;
+    return (time_t) t32;
+}
+
 /* Load an encoded length from the DB, see the REDIS_RDB_* defines on the top
  * of this file for a description of how this are stored on disk.
  *
@@ -1942,11 +1968,12 @@ static int rdbLoad(char *filename) {
     FILE *fp;
     robj *keyobj = NULL;
     uint32_t dbid;
-    int type;
-    int retval;
+    int type, retval, rdbver;
     dict *d = server.db[0].dict;
+    redisDb *db = server.db+0;
     char buf[1024];
-    int rdbver;
+    time_t expiretime = -1, now = time(NULL);
+
     fp = fopen(filename,"r");
     if (!fp) return REDIS_ERR;
     if (fread(buf,9,1,fp) == 0) goto eoferr;
@@ -1967,6 +1994,11 @@ static int rdbLoad(char *filename) {
 
         /* Read type. */
         if ((type = rdbLoadType(fp)) == -1) goto eoferr;
+        if (type == REDIS_EXPIRETIME) {
+            if ((expiretime = rdbLoadTime(fp)) == -1) goto eoferr;
+            /* We read the time so we need to read the object type again */
+            if ((type = rdbLoadType(fp)) == -1) goto eoferr;
+        }
         if (type == REDIS_EOF) break;
         /* Handle SELECT DB opcode as a special case */
         if (type == REDIS_SELECTDB) {
@@ -1976,7 +2008,8 @@ static int rdbLoad(char *filename) {
                 redisLog(REDIS_WARNING,"FATAL: Data file was created with a Redis server configured to handle more than %d databases. Exiting\n", server.dbnum);
                 exit(1);
             }
-            d = server.db[dbid].dict;
+            db = server.db+dbid;
+            d = db->dict;
             continue;
         }
         /* Read key */
@@ -2014,6 +2047,13 @@ static int rdbLoad(char *filename) {
             redisLog(REDIS_WARNING,"Loading DB, duplicated key (%s) found! Unrecoverable error, exiting now.", keyobj->ptr);
             exit(1);
         }
+        /* Set the expire time if needed */
+        if (expiretime != -1) {
+            setExpire(db,keyobj,expiretime);
+            /* Delete this key if already expired */
+            if (expiretime < now) deleteKey(db,keyobj);
+            expiretime = -1;
+        }
         keyobj = o = NULL;
     }
     fclose(fp);
@@ -3208,6 +3248,18 @@ static int setExpire(redisDb *db, robj *key, time_t when) {
     }
 }
 
+/* Return the expire time of the specified key, or -1 if no expire
+ * is associated with this key (i.e. the key is non volatile) */
+static time_t getExpire(redisDb *db, robj *key) {
+    dictEntry *de;
+
+    /* No expire? return ASAP */
+    if (dictSize(db->expires) == 0 ||
+       (de = dictFind(db->expires,key)) == NULL) return -1;
+
+    return (time_t) dictGetEntryVal(de);
+}
+
 static int expireIfNeeded(redisDb *db, robj *key) {
     time_t when;
     dictEntry *de;