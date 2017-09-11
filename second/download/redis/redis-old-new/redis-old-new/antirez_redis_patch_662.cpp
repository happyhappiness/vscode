@@ -1028,10 +1028,12 @@ void pop(unsigned char *zl, int where) {
         else
             printf("Pop tail: ");
 
-        if (vstr)
+        if (vstr) {
             if (vlen && fwrite(vstr,vlen,1,stdout) == 0) perror("fwrite");
-        else
+        }
+        else {
             printf("%lld", vlong);
+        }
 
         printf("\n");
         ziplistDeleteRange(zl,-1,1);
@@ -1368,7 +1370,7 @@ int main(int argc, char **argv) {
     {
         char v[3][257];
         zlentry e[3];
-        int i;
+        size_t i;
 
         for (i = 0; i < (sizeof(v)/sizeof(v[0])); i++) {
             memset(v[i], 'a' + i, sizeof(v[0]));
@@ -1464,7 +1466,7 @@ int main(int argc, char **argv) {
         for (i = 0; i < 20000; i++) {
             zl = ziplistNew();
             ref = listCreate();
-            listSetFreeMethod(ref,sdsfree);
+            listSetFreeMethod(ref,(void (*)(void*))sdsfree);
             len = rand() % 256;
 
             /* Create lists */