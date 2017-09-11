@@ -108,6 +108,9 @@ static double R_Zero, R_PosInf, R_NegInf, R_Nan;
 /* store string types for output */
 static char types[256][16];
 
+/* Prototypes */
+uint64_t crc64(uint64_t crc, const unsigned char *s, uint64_t l);
+
 /* when number of bytes to read is negative, do a peek */
 int readBytes(void *target, long num) {
     char peek = (num < 0) ? 1 : 0;
@@ -137,10 +140,10 @@ int processHeader() {
     }
 
     dump_version = (int)strtol(buf + 5, NULL, 10);
-    if (dump_version < 1 || dump_version > 4) {
+    if (dump_version < 1 || dump_version > 6) {
         ERROR("Unknown RDB format version: %d\n", dump_version);
     }
-    return 1;
+    return dump_version;
 }
 
 int loadType(entry *e) {
@@ -557,7 +560,16 @@ void printErrorStack(entry *e) {
 void process() {
     uint64_t num_errors = 0, num_valid_ops = 0, num_valid_bytes = 0;
     entry entry;
-    processHeader();
+    int dump_version = processHeader();
+
+    /* Exclude the final checksum for RDB >= 5. Will be checked at the end. */
+    if (dump_version >= 5) {
+        if (positions[0].size < 8) {
+            printf("RDB version >= 5 but no room for checksum.\n");
+            exit(1);
+        }
+        positions[0].size -= 8;;
+    }
 
     level = 1;
     while(positions[0].offset < positions[0].size) {
@@ -622,6 +634,26 @@ void process() {
         num_errors++;
     }
 
+    /* Verify checksum */
+    if (dump_version >= 5) {
+        uint64_t crc = crc64(0,positions[0].data,positions[0].size);
+        uint64_t crc2;
+        unsigned char *p = (unsigned char*)positions[0].data+positions[0].size;
+        crc2 = ((uint64_t)p[0] << 0) |
+               ((uint64_t)p[1] << 8) |
+               ((uint64_t)p[2] << 16) |
+               ((uint64_t)p[3] << 24) |
+               ((uint64_t)p[4] << 32) |
+               ((uint64_t)p[5] << 40) |
+               ((uint64_t)p[6] << 48) |
+               ((uint64_t)p[7] << 56);
+        if (crc != crc2) {
+            SHIFT_ERROR(positions[0].offset, "RDB CRC64 does not match.");
+        } else {
+            printf("CRC64 checksum is OK\n");
+        }
+    }
+
     /* print summary on errors */
     if (num_errors) {
         printf("\n");