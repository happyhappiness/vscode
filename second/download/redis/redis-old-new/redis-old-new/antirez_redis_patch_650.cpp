@@ -220,7 +220,7 @@ void sortCommand(redisClient *c) {
     if (sortval)
         incrRefCount(sortval);
     else
-        sortval = createListObject();
+        sortval = createQuicklistObject();
 
     /* The SORT command has an SQL-alike syntax, parse it */
     while(j < c->argc) {
@@ -420,6 +420,7 @@ void sortCommand(redisClient *c) {
     } else {
         redisPanic("Unknown type");
     }
+    printf("j: %d; vectorlen: %d\n", j, vectorlen);
     redisAssertWithInfo(c,sortval,j == vectorlen);
 
     /* Now it's time to load the right scores in the sorting vector */
@@ -509,7 +510,7 @@ void sortCommand(redisClient *c) {
             }
         }
     } else {
-        robj *sobj = createZiplistObject();
+        robj *sobj = createQuicklistObject();
 
         /* STORE option specified, set the sorting result as a List object */
         for (j = start; j <= end; j++) {