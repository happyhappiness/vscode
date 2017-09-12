@@ -5008,7 +5008,7 @@ static int zslDelete(zskiplist *zsl, double score, robj *obj) {
  * Min and mx are inclusive, so a score >= min || score <= max is deleted.
  * Note that this function takes the reference to the hash table view of the
  * sorted set, in order to remove the elements from the hash table too. */
-static unsigned long zslDeleteRange(zskiplist *zsl, double min, double max, dict *dict) {
+static unsigned long zslDeleteRangeByScore(zskiplist *zsl, double min, double max, dict *dict) {
     zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
     unsigned long removed = 0;
     int i;
@@ -5317,7 +5317,7 @@ static void zremrangebyscoreCommand(redisClient *c) {
             return;
         }
         zs = zsetobj->ptr;
-        deleted = zslDeleteRange(zs->zsl,min,max,zs->dict);
+        deleted = zslDeleteRangeByScore(zs->zsl,min,max,zs->dict);
         if (htNeedsResize(zs->dict)) dictResize(zs->dict);
         server.dirty += deleted;
         addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",deleted));