@@ -1014,7 +1014,7 @@ static void stress(int pos, int num, int maxsize, int dnum) {
     }
 }
 
-static void pop(unsigned char *zl, int where) {
+static unsigned char *pop(unsigned char *zl, int where) {
     unsigned char *p, *vstr;
     unsigned int vlen;
     long long vlong;
@@ -1034,7 +1034,7 @@ static void pop(unsigned char *zl, int where) {
         }
 
         printf("\n");
-        ziplistDeleteRange(zl,-1,1);
+        return ziplistDelete(zl,&p);
     } else {
         printf("ERROR: Could not pop\n");
         exit(1);
@@ -1099,16 +1099,16 @@ int ziplistTest(int argc, char **argv) {
     zl = createList();
     ziplistRepr(zl);
 
-    pop(zl,ZIPLIST_TAIL);
+    zl = pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
-    pop(zl,ZIPLIST_HEAD);
+    zl = pop(zl,ZIPLIST_HEAD);
     ziplistRepr(zl);
 
-    pop(zl,ZIPLIST_TAIL);
+    zl = pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
-    pop(zl,ZIPLIST_TAIL);
+    zl = pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
     printf("Get element at index 3:\n");