@@ -171,11 +171,6 @@
 
 /* Anti-warning macro... */
 #define REDIS_NOTUSED(V) ((void) V)
-int die() {
-        char *err = NULL;
-        sprintf(err, "gonner");
-        return 0;
-}
 
 
 /*================================= Data types ============================== */
@@ -1604,8 +1599,7 @@ static robj *createListObject(void) {
 static robj *createSetObject(void) {
     dict *d = dictCreate(&setDictType,NULL);
     if (!d) oom("dictCreate");
-	die();
-return createObject(REDIS_SET,d);
+    return createObject(REDIS_SET,d);
 }
 
 static void freeStringObject(robj *o) {