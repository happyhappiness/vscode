@@ -332,7 +332,7 @@ void sortCommand(redisClient *c) {
      * In this case to load all the objects in the vector is a huge waste of
      * resources. We just allocate a vector that is big enough for the selected
      * range length, and make sure to load just this part in the vector. */
-    if (sortval->type == REDIS_ZSET &&
+    if ((sortval->type == REDIS_ZSET || sortval->type == REDIS_LIST) &&
         dontsort &&
         (start != 0 || end != vectorlen-1))
     {
@@ -343,7 +343,35 @@ void sortCommand(redisClient *c) {
     vector = zmalloc(sizeof(redisSortObject)*vectorlen);
     j = 0;
 
-    if (sortval->type == REDIS_LIST) {
+    if (sortval->type == REDIS_LIST && dontsort) {
+        /* Special handling for a list, if 'dontsort' is true.
+         * This makes sure we return elements in the list original
+         * ordering, accordingly to DESC / ASC options.
+         *
+         * Note that in this case we also handle LIMIT here in a direct
+         * way, just getting the required range, as an optimization. */
+        if (end >= start) {
+            listTypeIterator *li;
+            listTypeEntry entry;
+            li = listTypeInitIterator(sortval,
+                    desc ? listTypeLength(sortval) - start - 1 : start,
+                    desc ? REDIS_HEAD : REDIS_TAIL);
+
+            while(j < vectorlen && listTypeNext(li,&entry)) {
+                vector[j].obj = listTypeGet(&entry);
+                vector[j].u.score = 0;
+                vector[j].u.cmpobj = NULL;
+                j++;
+            }
+            listTypeReleaseIterator(li);
+            /* The code producing the output does not know that in the case of
+             * sorted set, 'dontsort', and LIMIT, we are able to get just the
+             * range, already sorted, so we need to adjust "start" and "end"
+             * to make sure start is set to 0. */
+            end -= start;
+            start = 0;
+        }
+    } else if (sortval->type == REDIS_LIST) {
         listTypeIterator *li = listTypeInitIterator(sortval,0,REDIS_TAIL);
         listTypeEntry entry;
         while(listTypeNext(li,&entry)) {
@@ -420,7 +448,6 @@ void sortCommand(redisClient *c) {
     } else {
         redisPanic("Unknown type");
     }
-    printf("j: %d; vectorlen: %d\n", j, vectorlen);
     redisAssertWithInfo(c,sortval,j == vectorlen);
 
     /* Now it's time to load the right scores in the sorting vector */