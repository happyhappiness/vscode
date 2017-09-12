@@ -5300,13 +5300,15 @@ static void zrangeGenericCommand(redisClient *c, int reverse) {
             if (end >= llen) end = llen-1;
             rangelen = (end-start)+1;
 
-            /* Return the result in form of a multi-bulk reply */
+            /* check if starting point is trivial, before searching
+             * the element in log(N) time */
             if (reverse) {
-                ln = zslGetElementByRank(zsl, llen - start);
+                ln = start == 0 ? zsl->tail : zslGetElementByRank(zsl, llen - start);
             } else {
-                ln = zslGetElementByRank(zsl, start + 1);
+                ln = start == 0 ? zsl->header->forward[0] : zslGetElementByRank(zsl, start + 1);
             }
 
+            /* Return the result in form of a multi-bulk reply */
             addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
                 withscores ? (rangelen*2) : rangelen));
             for (j = 0; j < rangelen; j++) {