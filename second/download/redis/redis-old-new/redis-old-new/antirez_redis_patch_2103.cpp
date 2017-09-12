@@ -622,6 +622,7 @@ static int pubsubUnsubscribeAllPatterns(redisClient *c, int notify);
 static void freePubsubPattern(void *p);
 static int listMatchPubsubPattern(void *a, void *b);
 static int compareStringObjects(robj *a, robj *b);
+static int equalStringObjects(robj *a, robj *b);
 static void usage();
 static int rewriteAppendOnlyFileBackground(void);
 static int vmSwapObjectBlocking(robj *key, robj *val);
@@ -1022,6 +1023,30 @@ static long long memtoll(const char *p, int *err) {
     return val*mul;
 }
 
+/* Convert a long long into a string. Returns the number of
+ * characters needed to represent the number, that can be shorter if passed
+ * buffer length is not enough to store the whole number. */
+static int ll2string(char *s, size_t len, long long value) {
+    char buf[32], *p;
+    unsigned long long v;
+    size_t l;
+
+    if (len == 0) return 0;
+    v = (value < 0) ? -value : value;
+    p = buf+31; /* point to the last character */
+    do {
+        *p-- = '0'+(v%10);
+        v /= 10;
+    } while(v);
+    if (value < 0) *p-- = '-';
+    p++;
+    l = 32-(p-buf);
+    if (l+1 > len) l = len-1; /* Make sure it fits, including the nul term */
+    memcpy(s,p,l);
+    s[l] = '\0';
+    return l;
+}
+
 static void redisLog(int level, const char *fmt, ...) {
     va_list ap;
     FILE *fp;
@@ -1104,8 +1129,8 @@ static int dictEncObjKeyCompare(void *privdata, const void *key1,
     int cmp;
 
     if (o1->encoding == REDIS_ENCODING_INT &&
-        o2->encoding == REDIS_ENCODING_INT &&
-        o1->ptr == o2->ptr) return 1;
+        o2->encoding == REDIS_ENCODING_INT)
+            return o1->ptr == o2->ptr;
 
     o1 = getDecodedObject(o1);
     o2 = getDecodedObject(o2);
@@ -1125,7 +1150,7 @@ static unsigned int dictEncObjHash(const void *key) {
             char buf[32];
             int len;
 
-            len = snprintf(buf,32,"%ld",(long)o->ptr);
+            len = ll2string(buf,32,(long)o->ptr);
             return dictGenHashFunction((unsigned char*)buf, len);
         } else {
             unsigned int hash;
@@ -2656,7 +2681,7 @@ static void *dupClientReplyValue(void *o) {
 }
 
 static int listMatchObjects(void *a, void *b) {
-    return compareStringObjects(a,b) == 0;
+    return equalStringObjects(a,b);
 }
 
 static redisClient *createClient(int fd) {
@@ -2896,7 +2921,7 @@ static robj *createStringObjectFromLongLong(long long value) {
             o->encoding = REDIS_ENCODING_INT;
             o->ptr = (void*)((long)value);
         } else {
-            o->ptr = sdscatprintf(sdsempty(),"%lld",value);
+            o = createObject(REDIS_STRING,sdsfromlonglong(value));
         }
     }
     return o;
@@ -3111,7 +3136,7 @@ static int isStringRepresentableAsLong(sds s, long *longval) {
 
     value = strtol(s, &endptr, 10);
     if (endptr[0] != '\0') return REDIS_ERR;
-    slen = snprintf(buf,32,"%ld",value);
+    slen = ll2string(buf,32,value);
 
     /* If the number converted back into a string is not identical
      * then it's not possible to encode the string as integer */
@@ -3164,7 +3189,7 @@ static robj *getDecodedObject(robj *o) {
     if (o->type == REDIS_STRING && o->encoding == REDIS_ENCODING_INT) {
         char buf[32];
 
-        snprintf(buf,32,"%ld",(long)o->ptr);
+        ll2string(buf,32,(long)o->ptr);
         dec = createStringObject(buf,strlen(buf));
         return dec;
     } else {
@@ -3174,7 +3199,7 @@ static robj *getDecodedObject(robj *o) {
 
 /* Compare two string objects via strcmp() or alike.
  * Note that the objects may be integer-encoded. In such a case we
- * use snprintf() to get a string representation of the numbers on the stack
+ * use ll2string() to get a string representation of the numbers on the stack
  * and compare the strings, it's much faster than calling getDecodedObject().
  *
  * Important note: if objects are not integer encoded, but binary-safe strings,
@@ -3187,14 +3212,14 @@ static int compareStringObjects(robj *a, robj *b) {
 
     if (a == b) return 0;
     if (a->encoding != REDIS_ENCODING_RAW) {
-        snprintf(bufa,sizeof(bufa),"%ld",(long) a->ptr);
+        ll2string(bufa,sizeof(bufa),(long) a->ptr);
         astr = bufa;
         bothsds = 0;
     } else {
         astr = a->ptr;
     }
     if (b->encoding != REDIS_ENCODING_RAW) {
-        snprintf(bufb,sizeof(bufb),"%ld",(long) b->ptr);
+        ll2string(bufb,sizeof(bufb),(long) b->ptr);
         bstr = bufb;
         bothsds = 0;
     } else {
@@ -3203,14 +3228,26 @@ static int compareStringObjects(robj *a, robj *b) {
     return bothsds ? sdscmp(astr,bstr) : strcmp(astr,bstr);
 }
 
+/* Equal string objects return 1 if the two objects are the same from the
+ * point of view of a string comparison, otherwise 0 is returned. Note that
+ * this function is faster then checking for (compareStringObject(a,b) == 0)
+ * because it can perform some more optimization. */
+static int equalStringObjects(robj *a, robj *b) {
+    if (a->encoding != REDIS_ENCODING_RAW && b->encoding != REDIS_ENCODING_RAW){
+        return a->ptr == b->ptr;
+    } else {
+        return compareStringObjects(a,b) == 0;
+    }
+}
+
 static size_t stringObjectLen(robj *o) {
     redisAssert(o->type == REDIS_STRING);
     if (o->encoding == REDIS_ENCODING_RAW) {
         return sdslen(o->ptr);
     } else {
         char buf[32];
 
-        return snprintf(buf,32,"%ld",(long)o->ptr);
+        return ll2string(buf,32,(long)o->ptr);
     }
 }
 
@@ -3351,7 +3388,7 @@ static int rdbTryIntegerEncoding(char *s, size_t len, unsigned char *enc) {
     /* Check if it's possible to encode this value as a number */
     value = strtoll(s, &endptr, 10);
     if (endptr[0] != '\0') return 0;
-    snprintf(buf,32,"%lld",value);
+    ll2string(buf,32,value);
 
     /* If the number converted back into a string is not identical
      * then it's not possible to encode the string as integer */
@@ -3760,7 +3797,11 @@ static uint32_t rdbLoadLen(FILE *fp, int *isencoded) {
     }
 }
 
-static robj *rdbLoadIntegerObject(FILE *fp, int enctype) {
+/* Load an integer-encoded object from file 'fp', with the specified
+ * encoding type 'enctype'. If encode is true the function may return
+ * an integer-encoded object as reply, otherwise the returned object
+ * will always be encoded as a raw string. */
+static robj *rdbLoadIntegerObject(FILE *fp, int enctype, int encode) {
     unsigned char enc[4];
     long long val;
 
@@ -3781,7 +3822,10 @@ static robj *rdbLoadIntegerObject(FILE *fp, int enctype) {
         val = 0; /* anti-warning */
         redisPanic("Unknown RDB integer encoding type");
     }
-    return createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",val));
+    if (encode)
+        return createStringObjectFromLongLong(val);
+    else
+        return createObject(REDIS_STRING,sdsfromlonglong(val));
 }
 
 static robj *rdbLoadLzfStringObject(FILE*fp) {
@@ -3803,7 +3847,7 @@ static robj *rdbLoadLzfStringObject(FILE*fp) {
     return NULL;
 }
 
-static robj *rdbLoadStringObject(FILE*fp) {
+static robj *rdbGenericLoadStringObject(FILE*fp, int encode) {
     int isencoded;
     uint32_t len;
     sds val;
@@ -3814,7 +3858,7 @@ static robj *rdbLoadStringObject(FILE*fp) {
         case REDIS_RDB_ENC_INT8:
         case REDIS_RDB_ENC_INT16:
         case REDIS_RDB_ENC_INT32:
-            return rdbLoadIntegerObject(fp,len);
+            return rdbLoadIntegerObject(fp,len,encode);
         case REDIS_RDB_ENC_LZF:
             return rdbLoadLzfStringObject(fp);
         default:
@@ -3831,6 +3875,14 @@ static robj *rdbLoadStringObject(FILE*fp) {
     return createObject(REDIS_STRING,val);
 }
 
+static robj *rdbLoadStringObject(FILE *fp) {
+    return rdbGenericLoadStringObject(fp,0);
+}
+
+static robj *rdbLoadEncodedStringObject(FILE *fp) {
+    return rdbGenericLoadStringObject(fp,1);
+}
+
 /* For information about double serialization check rdbSaveDoubleValue() */
 static int rdbLoadDoubleValue(FILE *fp, double *val) {
     char buf[128];
@@ -3857,7 +3909,7 @@ static robj *rdbLoadObject(int type, FILE *fp) {
     redisLog(REDIS_DEBUG,"LOADING OBJECT %d (at %d)\n",type,ftell(fp));
     if (type == REDIS_STRING) {
         /* Read string value */
-        if ((o = rdbLoadStringObject(fp)) == NULL) return NULL;
+        if ((o = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
         o = tryObjectEncoding(o);
     } else if (type == REDIS_LIST || type == REDIS_SET) {
         /* Read list/set value */
@@ -3873,7 +3925,7 @@ static robj *rdbLoadObject(int type, FILE *fp) {
         while(listlen--) {
             robj *ele;
 
-            if ((ele = rdbLoadStringObject(fp)) == NULL) return NULL;
+            if ((ele = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
             ele = tryObjectEncoding(ele);
             if (type == REDIS_LIST) {
                 listAddNodeTail((list*)o->ptr,ele);
@@ -3894,7 +3946,7 @@ static robj *rdbLoadObject(int type, FILE *fp) {
             robj *ele;
             double *score = zmalloc(sizeof(double));
 
-            if ((ele = rdbLoadStringObject(fp)) == NULL) return NULL;
+            if ((ele = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
             ele = tryObjectEncoding(ele);
             if (rdbLoadDoubleValue(fp,score) == -1) return NULL;
             dictAdd(zs->dict,ele,score);
@@ -4850,7 +4902,7 @@ static void lremCommand(redisClient *c) {
         robj *ele = listNodeValue(ln);
 
         next = fromtail ? ln->prev : ln->next;
-        if (compareStringObjects(ele,c->argv[3]) == 0) {
+        if (equalStringObjects(ele,c->argv[3])) {
             listDelNode(list,ln);
             server.dirty++;
             removed++;
@@ -5454,7 +5506,7 @@ static int zslDelete(zskiplist *zsl, double score, robj *obj) {
     /* We may have multiple elements with the same score, what we need
      * is to find the element with both the right score and object. */
     x = x->forward[0];
-    if (x && score == x->score && compareStringObjects(x->obj,obj) == 0) {
+    if (x && score == x->score && equalStringObjects(x->obj,obj)) {
         zslDeleteNode(zsl, x, update);
         zslFreeNode(x);
         return 1;
@@ -5559,7 +5611,7 @@ static unsigned long zslGetRank(zskiplist *zsl, double score, robj *o) {
         }
 
         /* x might be equal to zsl->header, so test if obj is non-NULL */
-        if (x->obj && compareStringObjects(x->obj,o) == 0) {
+        if (x->obj && equalStringObjects(x->obj,o)) {
             return rank;
         }
     }
@@ -9623,7 +9675,7 @@ static int dontWaitForSwappedKey(redisClient *c, robj *key) {
     /* Remove the key from the list of keys this client is waiting for. */
     listRewind(c->io_keys,&li);
     while ((ln = listNext(&li)) != NULL) {
-        if (compareStringObjects(ln->value,key) == 0) {
+        if (equalStringObjects(ln->value,key)) {
             listDelNode(c->io_keys,ln);
             break;
         }
@@ -9850,7 +9902,7 @@ static int listMatchPubsubPattern(void *a, void *b) {
     pubsubPattern *pa = a, *pb = b;
 
     return (pa->client == pb->client) &&
-           (compareStringObjects(pa->pattern,pb->pattern) == 0);
+           (equalStringObjects(pa->pattern,pb->pattern));
 }
 
 /* Subscribe a client to a channel. Returns 1 if the operation succeeded, or