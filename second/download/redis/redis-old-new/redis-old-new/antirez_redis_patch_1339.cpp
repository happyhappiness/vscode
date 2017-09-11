@@ -170,8 +170,7 @@ static const uint64_t crc64_tab[256] = {
     UINT64_C(0x536fa08fdfd90e51), UINT64_C(0x29b7d047efec8728),
 };
 
-uint64_t crc64(const unsigned char *s, uint64_t l) {
-    uint64_t crc = 0;
+uint64_t crc64(uint64_t crc, const unsigned char *s, uint64_t l) {
     uint64_t j;
 
     for (j = 0; j < l; j++) {
@@ -186,7 +185,7 @@ uint64_t crc64(const unsigned char *s, uint64_t l) {
 #include <stdio.h>
 int main(void) {
     printf("e9c6d914c4b8d9ca == %016llx\n",
-        (unsigned long long) crc64((unsigned char*)"123456789",9));
+        (unsigned long long) crc64(0,(unsigned char*)"123456789",9));
     return 0;
 }
 #endif