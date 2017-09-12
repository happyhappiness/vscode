@@ -46,6 +46,7 @@
 #include <fcntl.h>
 #include <sys/time.h>
 #include <sys/resource.h>
+#include <limits.h>
 
 #include "ae.h"     /* Event driven programming library */
 #include "sds.h"    /* Dynamic safe strings */
@@ -82,9 +83,28 @@
 #define REDIS_LIST 1
 #define REDIS_SET 2
 #define REDIS_HASH 3
+
+/* Object types only used for dumping to disk */
 #define REDIS_SELECTDB 254
 #define REDIS_EOF 255
 
+/* Defines related to the dump file format. To store 32 bits lengths for short
+ * keys requires a lot of space, so we check the most significant 2 bits of
+ * the first byte to interpreter the length:
+ *
+ * 00|000000 => if the two MSB are 00 the len is the 6 bits of this byte
+ * 01|000000 00000000 =>  01, the len is 14 byes, 6 bits + 8 bits of next byte
+ * 10|000000 [32 bit integer] => if it's 01, a full 32 bit len will follow
+ * 11|000000 [64 bit integer] => if it's 11, a full 64 bit len will follow
+ *
+ * 64 bit lengths are not used currently. Lenghts up to 63 are stored using
+ * a single byte, most DB keys, and may values, will fit inside. */
+#define REDIS_RDB_6BITLEN 0
+#define REDIS_RDB_14BITLEN 1
+#define REDIS_RDB_32BITLEN 2
+#define REDIS_RDB_64BITLEN 3
+#define REDIS_RDB_LENERR UINT_MAX
+
 /* Client flags */
 #define REDIS_CLOSE 1       /* This client connection should be closed ASAP */
 #define REDIS_SLAVE 2       /* This client is a slave server */
@@ -230,11 +250,11 @@ static void freeSetObject(robj *o);
 static void decrRefCount(void *o);
 static robj *createObject(int type, void *ptr);
 static void freeClient(redisClient *c);
-static int loadDb(char *filename);
+static int rdbLoad(char *filename);
 static void addReply(redisClient *c, robj *obj);
 static void addReplySds(redisClient *c, sds s);
 static void incrRefCount(robj *o);
-static int saveDbBackground(char *filename);
+static int rdbSaveBackground(char *filename);
 static robj *createStringObject(char *ptr, size_t len);
 static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int dictid, robj **argv, int argc);
 static int syncWithMaster(void);
@@ -641,7 +661,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
                 now-server.lastsave > sp->seconds) {
                 redisLog(REDIS_NOTICE,"%d changes in %d seconds. Saving...",
                     sp->changes, sp->seconds);
-                saveDbBackground(server.dbfilename);
+                rdbSaveBackground(server.dbfilename);
                 break;
             }
          }
@@ -1394,12 +1414,37 @@ static void decrRefCount(void *obj) {
 
 /*============================ DB saving/loading ============================ */
 
+static int rdbSaveType(FILE *fp, unsigned char type) {
+    if (fwrite(&type,1,1,fp) == 0) return -1;
+    return 0;
+}
+
+static int rdbSaveLen(FILE *fp, uint32_t len) {
+    unsigned char buf[2];
+
+    if (len < (1<<6)) {
+        /* Save a 6 bit len */
+        buf[0] = (len&0xFF)|REDIS_RDB_6BITLEN;
+        if (fwrite(buf,1,1,fp) == 0) return -1;
+    } else if (len < (1<<14)) {
+        /* Save a 14 bit len */
+        buf[0] = ((len>>8)&0xFF)|REDIS_RDB_14BITLEN;
+        buf[1] = len&0xFF;
+        if (fwrite(buf,4,1,fp) == 0) return -1;
+    } else {
+        /* Save a 32 bit len */
+        buf[0] = REDIS_RDB_32BITLEN;
+        if (fwrite(buf,1,1,fp) == 0) return -1;
+        len = htonl(len);
+        if (fwrite(&len,4,1,fp) == 0) return -1;
+    }
+    return 0;
+}
+
 /* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success */
-static int saveDb(char *filename) {
+static int rdbSave(char *filename) {
     dictIterator *di = NULL;
     dictEntry *de;
-    uint32_t len;
-    uint8_t type;
     FILE *fp;
     char tmpfile[256];
     int j;
@@ -1410,7 +1455,7 @@ static int saveDb(char *filename) {
         redisLog(REDIS_WARNING, "Failed saving the DB: %s", strerror(errno));
         return REDIS_ERR;
     }
-    if (fwrite("REDIS0000",9,1,fp) == 0) goto werr;
+    if (fwrite("REDIS0001",9,1,fp) == 0) goto werr;
     for (j = 0; j < server.dbnum; j++) {
         dict *d = server.dict[j];
         if (dictGetHashTableUsed(d) == 0) continue;
@@ -1421,59 +1466,54 @@ static int saveDb(char *filename) {
         }
 
         /* Write the SELECT DB opcode */
-        type = REDIS_SELECTDB;
-        len = htonl(j);
-        if (fwrite(&type,1,1,fp) == 0) goto werr;
-        if (fwrite(&len,4,1,fp) == 0) goto werr;
+        if (rdbSaveType(fp,REDIS_SELECTDB) == -1) goto werr;
+        if (rdbSaveLen(fp,j) == -1) goto werr;
 
         /* Iterate this DB writing every entry */
         while((de = dictNext(di)) != NULL) {
             robj *key = dictGetEntryKey(de);
             robj *o = dictGetEntryVal(de);
 
-            type = o->type;
-            len = htonl(sdslen(key->ptr));
-            if (fwrite(&type,1,1,fp) == 0) goto werr;
-            if (fwrite(&len,4,1,fp) == 0) goto werr;
+            if (rdbSaveType(fp,o->type) == -1) goto werr;
+            if (rdbSaveLen(fp,sdslen(key->ptr)) == -1) goto werr;
             if (fwrite(key->ptr,sdslen(key->ptr),1,fp) == 0) goto werr;
-            if (type == REDIS_STRING) {
+            if (o->type == REDIS_STRING) {
                 /* Save a string value */
                 sds sval = o->ptr;
-                len = htonl(sdslen(sval));
-                if (fwrite(&len,4,1,fp) == 0) goto werr;
+
+                if (rdbSaveLen(fp,sdslen(sval)) == -1) goto werr;
                 if (sdslen(sval) &&
                     fwrite(sval,sdslen(sval),1,fp) == 0) goto werr;
-            } else if (type == REDIS_LIST) {
+            } else if (o->type == REDIS_LIST) {
                 /* Save a list value */
                 list *list = o->ptr;
                 listNode *ln = list->head;
 
-                len = htonl(listLength(list));
-                if (fwrite(&len,4,1,fp) == 0) goto werr;
+                if (rdbSaveLen(fp,listLength(list)) == -1) goto werr;
                 while(ln) {
                     robj *eleobj = listNodeValue(ln);
-                    len = htonl(sdslen(eleobj->ptr));
-                    if (fwrite(&len,4,1,fp) == 0) goto werr;
-                    if (sdslen(eleobj->ptr) && fwrite(eleobj->ptr,sdslen(eleobj->ptr),1,fp) == 0)
+
+                    if (rdbSaveLen(fp,sdslen(eleobj->ptr)) == -1) goto werr;
+                    if (sdslen(eleobj->ptr) &&
+                        fwrite(eleobj->ptr,sdslen(eleobj->ptr),1,fp) == 0)
                         goto werr;
                     ln = ln->next;
                 }
-            } else if (type == REDIS_SET) {
+            } else if (o->type == REDIS_SET) {
                 /* Save a set value */
                 dict *set = o->ptr;
                 dictIterator *di = dictGetIterator(set);
                 dictEntry *de;
 
                 if (!set) oom("dictGetIteraotr");
-                len = htonl(dictGetHashTableUsed(set));
-                if (fwrite(&len,4,1,fp) == 0) goto werr;
+                if (rdbSaveLen(fp,dictGetHashTableUsed(set)) == -1) goto werr;
                 while((de = dictNext(di)) != NULL) {
                     robj *eleobj;
 
                     eleobj = dictGetEntryKey(de);
-                    len = htonl(sdslen(eleobj->ptr));
-                    if (fwrite(&len,4,1,fp) == 0) goto werr;
-                    if (sdslen(eleobj->ptr) && fwrite(eleobj->ptr,sdslen(eleobj->ptr),1,fp) == 0)
+                    if (rdbSaveLen(fp,sdslen(eleobj->ptr)) == -1) goto werr;
+                    if (sdslen(eleobj->ptr) &&
+                        fwrite(eleobj->ptr,sdslen(eleobj->ptr),1,fp) == 0)
                         goto werr;
                 }
                 dictReleaseIterator(di);
@@ -1484,8 +1524,9 @@ static int saveDb(char *filename) {
         dictReleaseIterator(di);
     }
     /* EOF opcode */
-    type = REDIS_EOF;
-    if (fwrite(&type,1,1,fp) == 0) goto werr;
+    if (rdbSaveType(fp,REDIS_EOF) == -1) goto werr;
+
+    /* Make sure data will not remain on the OS's output buffers */
     fflush(fp);
     fsync(fileno(fp));
     fclose(fp);
@@ -1510,14 +1551,14 @@ static int saveDb(char *filename) {
     return REDIS_ERR;
 }
 
-static int saveDbBackground(char *filename) {
+static int rdbSaveBackground(char *filename) {
     pid_t childpid;
 
     if (server.bgsaveinprogress) return REDIS_ERR;
     if ((childpid = fork()) == 0) {
         /* Child */
         close(server.fd);
-        if (saveDb(filename) == REDIS_OK) {
+        if (rdbSave(filename) == REDIS_OK) {
             exit(0);
         } else {
             exit(1);
@@ -1531,121 +1572,133 @@ static int saveDbBackground(char *filename) {
     return REDIS_OK; /* unreached */
 }
 
-static int loadType(FILE *fp) {
-    uint8_t type;
+static int rdbLoadType(FILE *fp) {
+    unsigned char type;
     if (fread(&type,1,1,fp) == 0) return -1;
     return type;
 }
 
-static int loadDb(char *filename) {
+static uint32_t rdbLoadLen(FILE *fp, int rdbver) {
+    unsigned char buf[2];
+    uint32_t len;
+
+    if (rdbver == 0) {
+        if (fread(&len,4,1,fp) == 0) return REDIS_RDB_LENERR;
+        return ntohl(len);
+    } else {
+        if (fread(buf,1,1,fp) == 0) return REDIS_RDB_LENERR;
+        if ((buf[0]&0xC0) == REDIS_RDB_6BITLEN) {
+            /* Read a 6 bit len */
+            return buf[0];
+        } else if ((buf[0]&0xC0) == REDIS_RDB_14BITLEN) {
+            /* Read a 14 bit len */
+            if (fread(buf+1,1,1,fp) == 0) return REDIS_RDB_LENERR;
+            return ((buf[0]&0x3F)<<8)|buf[1];
+        } else {
+            /* Read a 32 bit len */
+            if (fread(&len,4,1,fp) == 0) return REDIS_RDB_LENERR;
+            return ntohl(len);
+        }
+    }
+    return 0;
+}
+
+static robj *rdbLoadStringObject(FILE*fp,int rdbver) {
+    uint32_t len = rdbLoadLen(fp,rdbver);
+    sds val;
+
+    if (len == REDIS_RDB_LENERR) return NULL;
+    val = sdsnewlen(NULL,len);
+    if (len && fread(val,len,1,fp) == 0) {
+        sdsfree(val);
+        return NULL;
+    }
+    return createObject(REDIS_STRING,val);
+}
+
+static int rdbLoad(char *filename) {
     FILE *fp;
-    char buf[REDIS_LOADBUF_LEN];    /* Try to use this buffer instead of */
-    char vbuf[REDIS_LOADBUF_LEN];   /* malloc() when the element is small */
-    char *key = NULL, *val = NULL;
-    uint32_t klen,vlen,dbid;
+    robj *keyobj = NULL;
+    uint32_t dbid;
     int type;
     int retval;
     dict *d = server.dict[0];
+    char buf[1024];
+    int rdbver;
 
     fp = fopen(filename,"r");
     if (!fp) return REDIS_ERR;
     if (fread(buf,9,1,fp) == 0) goto eoferr;
-    if (memcmp(buf,"REDIS0000",9) != 0) {
+    buf[9] = '\0';
+    if (memcmp(buf,"REDIS",5) != 0) {
         fclose(fp);
         redisLog(REDIS_WARNING,"Wrong signature trying to load DB from file");
         return REDIS_ERR;
     }
+    rdbver = atoi(buf+5);
+    if (rdbver > 1) {
+        fclose(fp);
+        redisLog(REDIS_WARNING,"Can't handle RDB format version %d",rdbver);
+        return REDIS_ERR;
+    }
     while(1) {
         robj *o;
 
         /* Read type. */
-        if ((type = loadType(fp)) == -1) goto eoferr;
+        if ((type = rdbLoadType(fp)) == -1) goto eoferr;
         if (type == REDIS_EOF) break;
         /* Handle SELECT DB opcode as a special case */
         if (type == REDIS_SELECTDB) {
-            if (fread(&dbid,4,1,fp) == 0) goto eoferr;
-            dbid = ntohl(dbid);
+            if ((dbid = rdbLoadLen(fp,rdbver)) == REDIS_RDB_LENERR) goto eoferr;
             if (dbid >= (unsigned)server.dbnum) {
-                redisLog(REDIS_WARNING,"FATAL: Data file was created with a Redis server compiled to handle more than %d databases. Exiting\n", server.dbnum);
+                redisLog(REDIS_WARNING,"FATAL: Data file was created with a Redis server configured to handle more than %d databases. Exiting\n", server.dbnum);
                 exit(1);
             }
             d = server.dict[dbid];
             continue;
         }
         /* Read key */
-        if (fread(&klen,4,1,fp) == 0) goto eoferr;
-        klen = ntohl(klen);
-        if (klen <= REDIS_LOADBUF_LEN) {
-            key = buf;
-        } else {
-            key = zmalloc(klen);
-            if (!key) oom("Loading DB from file");
-        }
-        if (fread(key,klen,1,fp) == 0) goto eoferr;
+        if ((keyobj = rdbLoadStringObject(fp,rdbver)) == NULL) goto eoferr;
 
         if (type == REDIS_STRING) {
             /* Read string value */
-            if (fread(&vlen,4,1,fp) == 0) goto eoferr;
-            vlen = ntohl(vlen);
-            if (vlen <= REDIS_LOADBUF_LEN) {
-                val = vbuf;
-            } else {
-                val = zmalloc(vlen);
-                if (!val) oom("Loading DB from file");
-            }
-            if (vlen && fread(val,vlen,1,fp) == 0) goto eoferr;
-            o = createObject(REDIS_STRING,sdsnewlen(val,vlen));
+            if ((o = rdbLoadStringObject(fp,rdbver)) == NULL) goto eoferr;
         } else if (type == REDIS_LIST || type == REDIS_SET) {
             /* Read list/set value */
             uint32_t listlen;
-            if (fread(&listlen,4,1,fp) == 0) goto eoferr;
-            listlen = ntohl(listlen);
+
+            if ((listlen = rdbLoadLen(fp,rdbver)) == REDIS_RDB_LENERR)
+                goto eoferr;
             o = (type == REDIS_LIST) ? createListObject() : createSetObject();
             /* Load every single element of the list/set */
             while(listlen--) {
                 robj *ele;
 
-                if (fread(&vlen,4,1,fp) == 0) goto eoferr;
-                vlen = ntohl(vlen);
-                if (vlen <= REDIS_LOADBUF_LEN) {
-                    val = vbuf;
-                } else {
-                    val = zmalloc(vlen);
-                    if (!val) oom("Loading DB from file");
-                }
-                if (vlen && fread(val,vlen,1,fp) == 0) goto eoferr;
-                ele = createObject(REDIS_STRING,sdsnewlen(val,vlen));
+                if ((ele = rdbLoadStringObject(fp,rdbver)) == NULL) goto eoferr;
                 if (type == REDIS_LIST) {
                     if (!listAddNodeTail((list*)o->ptr,ele))
                         oom("listAddNodeTail");
                 } else {
                     if (dictAdd((dict*)o->ptr,ele,NULL) == DICT_ERR)
                         oom("dictAdd");
                 }
-                /* free the temp buffer if needed */
-                if (val != vbuf) zfree(val);
-                val = NULL;
             }
         } else {
             assert(0 != 0);
         }
         /* Add the new object in the hash table */
-        retval = dictAdd(d,createStringObject(key,klen),o);
+        retval = dictAdd(d,keyobj,o);
         if (retval == DICT_ERR) {
-            redisLog(REDIS_WARNING,"Loading DB, duplicated key found! Unrecoverable error, exiting now.");
+            redisLog(REDIS_WARNING,"Loading DB, duplicated key (%s) found! Unrecoverable error, exiting now.", keyobj->ptr);
             exit(1);
         }
-        /* Iteration cleanup */
-        if (key != buf) zfree(key);
-        if (val != vbuf) zfree(val);
-        key = val = NULL;
+        keyobj = o = NULL;
     }
     fclose(fp);
     return REDIS_OK;
 
 eoferr: /* unexpected end of file is handled here with a fatal exit */
-    if (key != buf) zfree(key);
-    if (val != vbuf) zfree(val);
+    decrRefCount(keyobj);
     redisLog(REDIS_WARNING,"Short read loading DB. Unrecoverable error, exiting now.");
     exit(1);
     return REDIS_ERR; /* Just to avoid warning */
@@ -1894,7 +1947,7 @@ static void typeCommand(redisClient *c) {
 }
 
 static void saveCommand(redisClient *c) {
-    if (saveDb(server.dbfilename) == REDIS_OK) {
+    if (rdbSave(server.dbfilename) == REDIS_OK) {
         addReply(c,shared.ok);
     } else {
         addReply(c,shared.err);
@@ -1906,7 +1959,7 @@ static void bgsaveCommand(redisClient *c) {
         addReplySds(c,sdsnew("-ERR background save already in progress\r\n"));
         return;
     }
-    if (saveDbBackground(server.dbfilename) == REDIS_OK) {
+    if (rdbSaveBackground(server.dbfilename) == REDIS_OK) {
         addReply(c,shared.ok);
     } else {
         addReply(c,shared.err);
@@ -1915,7 +1968,7 @@ static void bgsaveCommand(redisClient *c) {
 
 static void shutdownCommand(redisClient *c) {
     redisLog(REDIS_WARNING,"User requested shutdown, saving DB...");
-    if (saveDb(server.dbfilename) == REDIS_OK) {
+    if (rdbSave(server.dbfilename) == REDIS_OK) {
         if (server.daemonize) {
           unlink(server.pidfile);
         }
@@ -2508,13 +2561,13 @@ static void sinterstoreCommand(redisClient *c) {
 static void flushdbCommand(redisClient *c) {
     dictEmpty(c->dict);
     addReply(c,shared.ok);
-    saveDb(server.dbfilename);
+    rdbSave(server.dbfilename);
 }
 
 static void flushallCommand(redisClient *c) {
     emptyDb();
     addReply(c,shared.ok);
-    saveDb(server.dbfilename);
+    rdbSave(server.dbfilename);
 }
 
 redisSortOperation *createSortOperation(int type, robj *pattern) {
@@ -2923,7 +2976,8 @@ static void syncCommand(redisClient *c) {
     if (c->flags & REDIS_SLAVE) return;
 
     redisLog(REDIS_NOTICE,"Slave ask for syncronization");
-    if (flushClientOutput(c) == REDIS_ERR || saveDb(server.dbfilename) != REDIS_OK)
+    if (flushClientOutput(c) == REDIS_ERR ||
+        rdbSave(server.dbfilename) != REDIS_OK)
         goto closeconn;
 
     fd = open(server.dbfilename, O_RDONLY);
@@ -3020,7 +3074,7 @@ static int syncWithMaster(void) {
         return REDIS_ERR;
     }
     emptyDb();
-    if (loadDb(server.dbfilename) != REDIS_OK) {
+    if (rdbLoad(server.dbfilename) != REDIS_OK) {
         redisLog(REDIS_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
         close(fd);
         return REDIS_ERR;
@@ -3079,7 +3133,7 @@ int main(int argc, char **argv) {
     initServer();
     if (server.daemonize) daemonize();
     redisLog(REDIS_NOTICE,"Server started, Redis version " REDIS_VERSION);
-    if (loadDb(server.dbfilename) == REDIS_OK)
+    if (rdbLoad(server.dbfilename) == REDIS_OK)
         redisLog(REDIS_NOTICE,"DB loaded from disk");
     if (aeCreateFileEvent(server.el, server.fd, AE_READABLE,
         acceptHandler, NULL, NULL) == AE_ERR) oom("creating file event");