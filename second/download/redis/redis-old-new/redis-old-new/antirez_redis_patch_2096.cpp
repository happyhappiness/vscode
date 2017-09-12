@@ -74,7 +74,8 @@
 #include "zmalloc.h" /* total memory usage aware version of malloc/free */
 #include "lzf.h"    /* LZF compression library */
 #include "pqsort.h" /* Partial qsort for SORT+LIMIT */
-#include "zipmap.h"
+#include "zipmap.h" /* Compact dictionary-alike data structure */
+#include "sha1.h"   /* SHA1 is used for DEBUG DIGEST */
 
 /* Error codes */
 #define REDIS_OK                0
@@ -10255,6 +10256,180 @@ static void publishCommand(redisClient *c) {
 
 /* ================================= Debugging ============================== */
 
+/* Compute the sha1 of string at 's' with 'len' bytes long.
+ * The SHA1 is then xored againt the string pointed by digest.
+ * Since xor is commutative, this operation is used in order to
+ * "add" digests relative to unordered elements.
+ *
+ * So digest(a,b,c,d) will be the same of digest(b,a,c,d) */
+static void xorDigest(unsigned char *digest, void *ptr, size_t len) {
+    SHA1_CTX ctx;
+    unsigned char hash[20], *s = ptr;
+    int j;
+
+    SHA1Init(&ctx);
+    SHA1Update(&ctx,s,len);
+    SHA1Final(hash,&ctx);
+
+    for (j = 0; j < 20; j++)
+        digest[j] ^= hash[j];
+}
+
+static void xorObjectDigest(unsigned char *digest, robj *o) {
+    o = getDecodedObject(o);
+    xorDigest(digest,o->ptr,sdslen(o->ptr));
+    decrRefCount(o);
+}
+
+/* This function instead of just computing the SHA1 and xoring it
+ * against diget, also perform the digest of "digest" itself and
+ * replace the old value with the new one.
+ *
+ * So the final digest will be:
+ *
+ * digest = SHA1(digest xor SHA1(data))
+ *
+ * This function is used every time we want to preserve the order so
+ * that digest(a,b,c,d) will be different than digest(b,c,d,a)
+ *
+ * Also note that mixdigest("foo") followed by mixdigest("bar")
+ * will lead to a different digest compared to "fo", "obar".
+ */
+static void mixDigest(unsigned char *digest, void *ptr, size_t len) {
+    SHA1_CTX ctx;
+    char *s = ptr;
+
+    xorDigest(digest,s,len);
+    SHA1Init(&ctx);
+    SHA1Update(&ctx,digest,20);
+    SHA1Final(digest,&ctx);
+}
+
+static void mixObjectDigest(unsigned char *digest, robj *o) {
+    o = getDecodedObject(o);
+    mixDigest(digest,o->ptr,sdslen(o->ptr));
+    decrRefCount(o);
+}
+
+/* Compute the dataset digest. Since keys, sets elements, hashes elements
+ * are not ordered, we use a trick: every aggregate digest is the xor
+ * of the digests of their elements. This way the order will not change
+ * the result. For list instead we use a feedback entering the output digest
+ * as input in order to ensure that a different ordered list will result in
+ * a different digest. */
+static void computeDatasetDigest(unsigned char *final) {
+    unsigned char digest[20];
+    char buf[128];
+    dictIterator *di = NULL;
+    dictEntry *de;
+    int j;
+    uint32_t aux;
+
+    memset(final,0,20); /* Start with a clean result */
+
+    for (j = 0; j < server.dbnum; j++) {
+        redisDb *db = server.db+j;
+
+        if (dictSize(db->dict) == 0) continue;
+        di = dictGetIterator(db->dict);
+
+        /* hash the DB id, so the same dataset moved in a different
+         * DB will lead to a different digest */
+        aux = htonl(j);
+        mixDigest(final,&aux,sizeof(aux));
+
+        /* Iterate this DB writing every entry */
+        while((de = dictNext(di)) != NULL) {
+            robj *key, *o;
+            time_t expiretime;
+
+            memset(digest,0,20); /* This key-val digest */
+            key = dictGetEntryKey(de);
+            mixObjectDigest(digest,key);
+            if (!server.vm_enabled || key->storage == REDIS_VM_MEMORY ||
+                key->storage == REDIS_VM_SWAPPING) {
+                o = dictGetEntryVal(de);
+                incrRefCount(o);
+            } else {
+                o = vmPreviewObject(key);
+            }
+            aux = htonl(o->type);
+            mixDigest(digest,&aux,sizeof(aux));
+            expiretime = getExpire(db,key);
+
+            /* Save the key and associated value */
+            if (o->type == REDIS_STRING) {
+                mixObjectDigest(digest,o);
+            } else if (o->type == REDIS_LIST) {
+                list *list = o->ptr;
+                listNode *ln;
+                listIter li;
+
+                listRewind(list,&li);
+                while((ln = listNext(&li))) {
+                    robj *eleobj = listNodeValue(ln);
+
+                    mixObjectDigest(digest,eleobj);
+                }
+            } else if (o->type == REDIS_SET) {
+                dict *set = o->ptr;
+                dictIterator *di = dictGetIterator(set);
+                dictEntry *de;
+
+                while((de = dictNext(di)) != NULL) {
+                    robj *eleobj = dictGetEntryKey(de);
+
+                    xorObjectDigest(digest,eleobj);
+                }
+                dictReleaseIterator(di);
+            } else if (o->type == REDIS_ZSET) {
+                zset *zs = o->ptr;
+                dictIterator *di = dictGetIterator(zs->dict);
+                dictEntry *de;
+
+                while((de = dictNext(di)) != NULL) {
+                    robj *eleobj = dictGetEntryKey(de);
+                    double *score = dictGetEntryVal(de);
+                    unsigned char eledigest[20];
+
+                    snprintf(buf,sizeof(buf),"%.17g",*score);
+                    memset(eledigest,0,20);
+                    mixObjectDigest(eledigest,eleobj);
+                    mixDigest(eledigest,buf,strlen(buf));
+                    xorDigest(digest,eledigest,20);
+                }
+                dictReleaseIterator(di);
+            } else if (o->type == REDIS_HASH) {
+                hashIterator *hi;
+                robj *obj;
+
+                hi = hashInitIterator(o);
+                while (hashNext(hi) != REDIS_ERR) {
+                    unsigned char eledigest[20];
+
+                    memset(eledigest,0,20);
+                    obj = hashCurrent(hi,REDIS_HASH_KEY);
+                    mixObjectDigest(eledigest,obj);
+                    decrRefCount(obj);
+                    obj = hashCurrent(hi,REDIS_HASH_VALUE);
+                    mixObjectDigest(eledigest,obj);
+                    decrRefCount(obj);
+                    xorDigest(digest,eledigest,20);
+                }
+                hashReleaseIterator(hi);
+            } else {
+                redisPanic("Unknown object type");
+            }
+            decrRefCount(o);
+            /* If the key has an expire, add it to the mix */
+            if (expiretime != -1) xorDigest(digest,"!!expire!!",10);
+            /* We can finally xor the key-val digest to the final digest */
+            xorDigest(final,digest,20);
+        }
+        dictReleaseIterator(di);
+    }
+}
+
 static void debugCommand(redisClient *c) {
     if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
         *((char*)-1) = 'x';
@@ -10362,6 +10537,17 @@ static void debugCommand(redisClient *c) {
             dictAdd(c->db->dict,key,val);
         }
         addReply(c,shared.ok);
+    } else if (!strcasecmp(c->argv[1]->ptr,"digest") && c->argc == 2) {
+        unsigned char digest[20];
+        sds d = sdsnew("+");
+        int j;
+
+        computeDatasetDigest(digest);
+        for (j = 0; j < 20; j++)
+            d = sdscatprintf(d, "%02x",digest[j]);
+
+        d = sdscatlen(d,"\r\n",2);
+        addReplySds(c,d);
     } else {
         addReplySds(c,sdsnew(
             "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|SWAPIN <key>|SWAPOUT <key>|RELOAD]\r\n"));