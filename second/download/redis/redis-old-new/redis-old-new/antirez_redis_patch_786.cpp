@@ -1416,7 +1416,7 @@ static int toIntType(char *key, char *type) {
 
 static void getKeyTypes(redisReply *keys, int *types) {
     redisReply *reply;
-    int i;
+    unsigned int i;
 
     /* Pipeline TYPE commands */
     for(i=0;i<keys->elements;i++) {
@@ -1445,7 +1445,7 @@ static void getKeySizes(redisReply *keys, int *types,
 {
     redisReply *reply;
     char *sizecmds[] = {"STRLEN","LLEN","SCARD","HLEN","ZCARD"};
-    int i;
+    unsigned int i;
 
     /* Pipeline size commands */
     for(i=0;i<keys->elements;i++) {
@@ -1492,7 +1492,8 @@ static void findBigKeys(void) {
     char *typename[] = {"string","list","set","hash","zset"};
     char *typeunit[] = {"bytes","items","members","fields","members"};
     redisReply *reply, *keys;
-    int type, *types=NULL, arrsize=0, i;
+    unsigned int arrsize=0, i;
+    int type, *types=NULL;
     double pct;
 
     /* Total keys pre scanning */
@@ -1779,7 +1780,7 @@ static void scanMode(void) {
             printf("ERROR: %s\n", reply->str);
             exit(1);
         } else {
-            int j;
+            unsigned int j;
 
             cur = strtoull(reply->element[0]->str,NULL,10);
             for (j = 0; j < reply->element[1]->elements; j++)