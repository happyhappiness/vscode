@@ -581,6 +581,7 @@ void ziplistRepr(unsigned char *zl) {
 }
 
 #ifdef ZIPLIST_TEST_MAIN
+#include <sys/time.h>
 
 unsigned char *createList() {
     unsigned char *zl = ziplistNew();
@@ -610,6 +611,35 @@ unsigned char *createIntList() {
     return zl;
 }
 
+long long usec(void) {
+    struct timeval tv;
+    gettimeofday(&tv,NULL);
+    return (((long long)tv.tv_sec)*1000000)+tv.tv_usec;
+}
+
+void stress(int pos, int num, int maxsize, int dnum) {
+    int i,j,k;
+    unsigned char *zl;
+    char posstr[2][5] = { "HEAD", "TAIL" };
+    long long start;
+    for (i = 0; i < maxsize; i+=dnum) {
+        zl = ziplistNew();
+        for (j = 0; j < i; j++) {
+            zl = ziplistPush(zl,(unsigned char*)"quux",4,ZIPLIST_TAIL);
+        }
+
+        /* Do num times a push+pop from pos */
+        start = usec();
+        for (k = 0; k < num; k++) {
+            zl = ziplistPush(zl,(unsigned char*)"quux",4,pos);
+            zl = ziplistDeleteRange(zl,0,1);
+        }
+        printf("List size: %8d, bytes: %8d, %dx push+pop (%s): %6lld usec\n",
+            i,ZIPLIST_BYTES(zl),num,posstr[pos],usec()-start);
+        zfree(zl);
+    }
+}
+
 int main(int argc, char **argv) {
     unsigned char *zl, *p;
     unsigned char *entry;
@@ -918,6 +948,13 @@ int main(int argc, char **argv) {
         printf("SUCCESS\n");
     }
 
+    printf("Stress with variable ziplist size:\n");
+    {
+        stress(ZIPLIST_HEAD,100000,16384,256);
+        stress(ZIPLIST_TAIL,100000,16384,256);
+    }
+
     return 0;
 }
+
 #endif