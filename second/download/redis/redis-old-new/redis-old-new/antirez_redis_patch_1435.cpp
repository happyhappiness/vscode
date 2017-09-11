@@ -1,5 +1,6 @@
 #include "redis.h"
 #include "pqsort.h" /* Partial qsort for SORT+LIMIT */
+#include <math.h> /* isnan() */
 
 redisSortOperation *createSortOperation(int type, robj *pattern) {
     redisSortOperation *so = zmalloc(sizeof(*so));
@@ -102,7 +103,10 @@ int sortCompare(const void *s1, const void *s2) {
         } else if (so1->u.score < so2->u.score) {
             cmp = -1;
         } else {
-            cmp = 0;
+            /* Objects have the same score, but we don't want the comparison
+             * to be undefined, so we compare objects lexicographycally.
+             * This way the result of SORT is deterministic. */
+            cmp = compareStringObjects(so1->obj,so2->obj);
         }
     } else {
         /* Alphanumeric sorting */
@@ -136,6 +140,7 @@ void sortCommand(redisClient *c) {
     long limit_start = 0, limit_count = -1, start, end;
     int j, dontsort = 0, vectorlen;
     int getop = 0; /* GET operation counter */
+    int int_convertion_error = 0;
     robj *sortval, *sortby = NULL, *storekey = NULL;
     redisSortObject *vector; /* Resulting vector to sort */
 
@@ -266,7 +271,14 @@ void sortCommand(redisClient *c) {
                 if (sortby) vector[j].u.cmpobj = getDecodedObject(byval);
             } else {
                 if (byval->encoding == REDIS_ENCODING_RAW) {
-                    vector[j].u.score = strtod(byval->ptr,NULL);
+                    char *eptr;
+
+                    vector[j].u.score = strtod(byval->ptr,&eptr);
+                    if (eptr[0] != '\0' || errno == ERANGE ||
+                        isnan(vector[j].u.score))
+                    {
+                        int_convertion_error = 1;
+                    }
                 } else if (byval->encoding == REDIS_ENCODING_INT) {
                     /* Don't need to decode the object if it's
                      * integer-encoded (the only encoding supported) so
@@ -295,6 +307,7 @@ void sortCommand(redisClient *c) {
     }
     if (end >= vectorlen) end = vectorlen-1;
 
+    server.sort_dontsort = dontsort;
     if (dontsort == 0) {
         server.sort_desc = desc;
         server.sort_alpha = alpha;
@@ -308,7 +321,9 @@ void sortCommand(redisClient *c) {
     /* Send command output to the output buffer, performing the specified
      * GET/DEL/INCR/DECR operations if any. */
     outputlen = getop ? getop*(end-start+1) : end-start+1;
-    if (storekey == NULL) {
+    if (int_convertion_error) {
+        addReplyError(c,"One or more scores can't be converted into double");
+    } else if (storekey == NULL) {
         /* STORE option not specified, sent the sorting result to client */
         addReplyMultiBulkLen(c,outputlen);
         for (j = start; j <= end; j++) {