@@ -5081,6 +5081,26 @@ static unsigned long zslGetRank(zskiplist *zsl, double score, robj *o) {
     return 0;
 }
 
+/* Finds an element by its rank. The rank argument needs to be 1-based. */
+zskiplistNode* zslGetElementByRank(zskiplist *zsl, unsigned long rank) {
+    zskiplistNode *x;
+    unsigned long traversed = 0;
+    int i;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        while (x->forward[i] && (traversed + x->span[i]) <= rank) {
+            traversed += x->span[i];
+            x = x->forward[i];
+        }
+
+        if (traversed == rank) {
+            return x;
+        }
+    }
+    return NULL;
+}
+
 /* The actual Z-commands implementations */
 
 /* This generic command implements both ZADD and ZINCRBY.
@@ -5282,13 +5302,9 @@ static void zrangeGenericCommand(redisClient *c, int reverse) {
 
             /* Return the result in form of a multi-bulk reply */
             if (reverse) {
-                ln = zsl->tail;
-                while (start--)
-                    ln = ln->backward;
+                ln = zslGetElementByRank(zsl, llen - start);
             } else {
-                ln = zsl->header->forward[0];
-                while (start--)
-                    ln = ln->forward[0];
+                ln = zslGetElementByRank(zsl, start + 1);
             }
 
             addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",