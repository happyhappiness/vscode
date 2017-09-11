@@ -181,9 +181,13 @@ uint64_t crc64(uint64_t crc, const unsigned char *s, uint64_t l) {
 }
 
 /* Test main */
-#ifdef TEST_MAIN
+#ifdef REDIS_TEST
 #include <stdio.h>
-int main(void) {
+
+#define UNUSED(x) (void)(x)
+int crc64Test(int argc, char *argv[]) {
+    UNUSED(argc);
+    UNUSED(argv);
     printf("e9c6d914c4b8d9ca == %016llx\n",
         (unsigned long long) crc64(0,(unsigned char*)"123456789",9));
     return 0;