@@ -52,6 +52,9 @@
 #include "redis.h"
 #include <math.h>
 
+static int zslLexValueGteMin(robj *value, zlexrangespec *spec);
+static int zslLexValueLteMax(robj *value, zlexrangespec *spec);
+
 zskiplistNode *zslCreateNode(int level, double score, robj *obj) {
     zskiplistNode *zn = zmalloc(sizeof(*zn)+level*sizeof(struct zskiplistLevel));
     zn->score = score;
@@ -319,6 +322,35 @@ unsigned long zslDeleteRangeByScore(zskiplist *zsl, zrangespec *range, dict *dic
     return removed;
 }
 
+unsigned long zslDeleteRangeByLex(zskiplist *zsl, zlexrangespec *range, dict *dict) {
+    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
+    unsigned long removed = 0;
+    int i;
+
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        while (x->level[i].forward &&
+            !zslLexValueGteMin(x->level[i].forward->obj,range))
+                x = x->level[i].forward;
+        update[i] = x;
+    }
+
+    /* Current node is the last with score < or <= min. */
+    x = x->level[0].forward;
+
+    /* Delete nodes while in range. */
+    while (x && zslLexValueLteMax(x->obj,range)) {
+        zskiplistNode *next = x->level[0].forward;
+        zslDeleteNode(zsl,x,update);
+        dictDelete(dict,x->obj);
+        zslFreeNode(x);
+        removed++;
+        x = next;
+    }
+    return removed;
+}
+
 /* Delete all the elements with rank between start and end from the skiplist.
  * Start and end are inclusive. Note that start and end need to be 1-based */
 unsigned long zslDeleteRangeByRank(zskiplist *zsl, unsigned int start, unsigned int end, dict *dict) {
@@ -1008,6 +1040,33 @@ unsigned char *zzlDeleteRangeByScore(unsigned char *zl, zrangespec *range, unsig
     return zl;
 }
 
+unsigned char *zzlDeleteRangeByLex(unsigned char *zl, zlexrangespec *range, unsigned long *deleted) {
+    unsigned char *eptr, *sptr;
+    unsigned long num = 0;
+
+    if (deleted != NULL) *deleted = 0;
+
+    eptr = zzlFirstInLexRange(zl,range);
+    if (eptr == NULL) return zl;
+
+    /* When the tail of the ziplist is deleted, eptr will point to the sentinel
+     * byte and ziplistNext will return NULL. */
+    while ((sptr = ziplistNext(zl,eptr)) != NULL) {
+        if (zzlLexValueLteMax(eptr,range)) {
+            /* Delete both the element and the score. */
+            zl = ziplistDelete(zl,&eptr);
+            zl = ziplistDelete(zl,&eptr);
+            num++;
+        } else {
+            /* No longer in range. */
+            break;
+        }
+    }
+
+    if (deleted != NULL) *deleted = num;
+    return zl;
+}
+
 /* Delete all the elements with rank between start and end from the skiplist.
  * Start and end are inclusive. Note that start and end need to be 1-based */
 unsigned char *zzlDeleteRangeByRank(unsigned char *zl, unsigned int start, unsigned int end, unsigned long *deleted) {
@@ -1325,6 +1384,7 @@ void zremrangeGenericCommand(redisClient *c, int rangetype) {
     int keyremoved = 0;
     unsigned long deleted;
     zrangespec range;
+    zlexrangespec lexrange;
     long start, end, llen;
 
     /* Step 1: Parse the range. */
@@ -1337,6 +1397,11 @@ void zremrangeGenericCommand(redisClient *c, int rangetype) {
             addReplyError(c,"min or max is not a float");
             return;
         }
+    } else if (rangetype == ZRANGE_LEX) {
+        if (zslParseLexRange(c->argv[2],c->argv[3],&lexrange) != REDIS_OK) {
+            addReplyError(c,"min or max not valid string range item");
+            return;
+        }
     }
 
     /* Step 2: Lookup & range sanity checks if needed. */
@@ -1368,6 +1433,9 @@ void zremrangeGenericCommand(redisClient *c, int rangetype) {
         case ZRANGE_SCORE:
             zobj->ptr = zzlDeleteRangeByScore(zobj->ptr,&range,&deleted);
             break;
+        case ZRANGE_LEX:
+            zobj->ptr = zzlDeleteRangeByLex(zobj->ptr,&lexrange,&deleted);
+            break;
         }
         if (zzlLength(zobj->ptr) == 0) {
             dbDelete(c->db,key);
@@ -1382,6 +1450,9 @@ void zremrangeGenericCommand(redisClient *c, int rangetype) {
         case ZRANGE_SCORE:
             deleted = zslDeleteRangeByScore(zs->zsl,&range,zs->dict);
             break;
+        case ZRANGE_LEX:
+            deleted = zslDeleteRangeByLex(zs->zsl,&lexrange,zs->dict);
+            break;
         }
         if (htNeedsResize(zs->dict)) dictResize(zs->dict);
         if (dictSize(zs->dict) == 0) {
@@ -1412,6 +1483,10 @@ void zremrangebyscoreCommand(redisClient *c) {
     zremrangeGenericCommand(c,ZRANGE_SCORE);
 }
 
+void zremrangebylexCommand(redisClient *c) {
+    zremrangeGenericCommand(c,ZRANGE_LEX);
+}
+
 typedef struct {
     robj *subject;
     int type; /* Set, sorted set */