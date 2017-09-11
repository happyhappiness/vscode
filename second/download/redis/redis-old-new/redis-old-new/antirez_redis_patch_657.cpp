@@ -101,12 +101,16 @@ uint64_t intrev64(uint64_t v) {
     return v;
 }
 
-#ifdef TESTMAIN
+#ifdef REDIS_TEST
 #include <stdio.h>
 
-int main(void) {
+#define UNUSED(x) (void)(x)
+int endianconvTest(int argc, char *argv[]) {
     char buf[32];
 
+    UNUSED(argc);
+    UNUSED(argv);
+
     sprintf(buf,"ciaoroma");
     memrev16(buf);
     printf("%s\n", buf);