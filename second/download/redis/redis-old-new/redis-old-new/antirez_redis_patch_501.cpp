@@ -41,7 +41,7 @@
 #include "crc64.h"
 
 #define ERROR(...) { \
-    redisLog(REDIS_WARNING, __VA_ARGS__); \
+    serverLog(REDIS_WARNING, __VA_ARGS__); \
     exit(1); \
 }
 
@@ -491,7 +491,7 @@ static void printCentered(int indent, int width, char* body) {
 
     memset(head, '=', indent);
     memset(tail, '=', width - 2 - indent - strlen(body));
-    redisLog(REDIS_WARNING, "%s %s %s", head, body, tail);
+    serverLog(REDIS_WARNING, "%s %s %s", head, body, tail);
 }
 
 static void printValid(uint64_t ops, uint64_t bytes) {
@@ -538,7 +538,7 @@ static void printErrorStack(entry *e) {
 
     /* display error stack */
     for (i = 0; i < errors.level; i++) {
-        redisLog(REDIS_WARNING, "0x%08lx - %s",
+        serverLog(REDIS_WARNING, "0x%08lx - %s",
             (unsigned long) errors.offset[i], errors.error[i]);
     }
 }
@@ -551,7 +551,7 @@ void process(void) {
     /* Exclude the final checksum for RDB >= 5. Will be checked at the end. */
     if (dump_version >= 5) {
         if (positions[0].size < 8) {
-            redisLog(REDIS_WARNING, "RDB version >= 5 but no room for checksum.");
+            serverLog(REDIS_WARNING, "RDB version >= 5 but no room for checksum.");
             exit(1);
         }
         positions[0].size -= 8;
@@ -636,13 +636,13 @@ void process(void) {
         if (crc != crc2) {
             SHIFT_ERROR(positions[0].offset, "RDB CRC64 does not match.");
         } else {
-            redisLog(REDIS_WARNING, "CRC64 checksum is OK");
+            serverLog(REDIS_WARNING, "CRC64 checksum is OK");
         }
     }
 
     /* print summary on errors */
     if (num_errors) {
-        redisLog(REDIS_WARNING, "Total unprocessable opcodes: %llu",
+        serverLog(REDIS_WARNING, "Total unprocessable opcodes: %llu",
             (unsigned long long) num_errors);
     }
 }
@@ -704,7 +704,7 @@ int redis_check_rdb_main(char **argv, int argc) {
         fprintf(stderr, "Usage: %s <rdb-file-name>\n", argv[0]);
         exit(1);
     }
-    redisLog(REDIS_WARNING, "Checking RDB file %s", argv[1]);
+    serverLog(REDIS_WARNING, "Checking RDB file %s", argv[1]);
     exit(redis_check_rdb(argv[1]));
     return 0;
 }