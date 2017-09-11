@@ -365,44 +365,46 @@ size_t intsetBlobLen(intset *is) {
     return sizeof(intset)+intrev32ifbe(is->length)*intrev32ifbe(is->encoding);
 }
 
-#ifdef INTSET_TEST_MAIN
+#ifdef REDIS_TEST
 #include <sys/time.h>
+#include <time.h>
 
-void intsetRepr(intset *is) {
-    int i;
-    for (i = 0; i < intrev32ifbe(is->length); i++) {
+#if 0
+static void intsetRepr(intset *is) {
+    for (uint32_t i = 0; i < intrev32ifbe(is->length); i++) {
         printf("%lld\n", (uint64_t)_intsetGet(is,i));
     }
     printf("\n");
 }
 
-void error(char *err) {
+static void error(char *err) {
     printf("%s\n", err);
     exit(1);
 }
+#endif
 
-void ok(void) {
+static void ok(void) {
     printf("OK\n");
 }
 
-long long usec(void) {
+static long long usec(void) {
     struct timeval tv;
     gettimeofday(&tv,NULL);
     return (((long long)tv.tv_sec)*1000000)+tv.tv_usec;
 }
 
 #define assert(_e) ((_e)?(void)0:(_assert(#_e,__FILE__,__LINE__),exit(1)))
-void _assert(char *estr, char *file, int line) {
+static void _assert(char *estr, char *file, int line) {
     printf("\n\n=== ASSERTION FAILED ===\n");
     printf("==> %s:%d '%s' is not true\n",file,line,estr);
 }
 
-intset *createSet(int bits, int size) {
+static intset *createSet(int bits, int size) {
     uint64_t mask = (1<<bits)-1;
-    uint64_t i, value;
+    uint64_t value;
     intset *is = intsetNew();
 
-    for (i = 0; i < size; i++) {
+    for (int i = 0; i < size; i++) {
         if (bits > 32) {
             value = (rand()*rand()) & mask;
         } else {
@@ -413,10 +415,8 @@ intset *createSet(int bits, int size) {
     return is;
 }
 
-void checkConsistency(intset *is) {
-    int i;
-
-    for (i = 0; i < (intrev32ifbe(is->length)-1); i++) {
+static void checkConsistency(intset *is) {
+    for (uint32_t i = 0; i < (intrev32ifbe(is->length)-1); i++) {
         uint32_t encoding = intrev32ifbe(is->encoding);
 
         if (encoding == INTSET_ENC_INT16) {
@@ -432,11 +432,15 @@ void checkConsistency(intset *is) {
     }
 }
 
-int main(int argc, char **argv) {
+#define UNUSED(x) (void)(x)
+int intsetTest(int argc, char **argv) {
     uint8_t success;
     int i;
     intset *is;
-    sranddev();
+    srand(time(NULL));
+
+    UNUSED(argc);
+    UNUSED(argv);
 
     printf("Value encodings: "); {
         assert(_intsetValueEncoding(-32768) == INTSET_ENC_INT16);
@@ -464,7 +468,7 @@ int main(int argc, char **argv) {
     }
 
     printf("Large number of random adds: "); {
-        int inserts = 0;
+        uint32_t inserts = 0;
         is = intsetNew();
         for (i = 0; i < 1024; i++) {
             is = intsetAdd(is,rand()%0x800,&success);
@@ -566,5 +570,7 @@ int main(int argc, char **argv) {
         checkConsistency(is);
         ok();
     }
+
+    return 0;
 }
 #endif