@@ -28,13 +28,8 @@
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
-#include "fmacros.h"
-#include <stdlib.h>
-#include <stdio.h>
-#include <string.h>
-#include <unistd.h>
+#include "server.h"
 #include <sys/stat.h>
-#include "config.h"
 
 #define ERROR(...) { \
     char __buf[1024]; \
@@ -60,7 +55,7 @@ int readLong(FILE *fp, char prefix, long *target) {
         return 0;
     }
     if (buf[0] != prefix) {
-        ERROR("Expected prefix '%c', got: '%c'",buf[0],prefix);
+        ERROR("Expected prefix '%c', got: '%c'",prefix,buf[0]);
         return 0;
     }
     *target = strtol(buf+1,&eptr,10);
@@ -87,7 +82,7 @@ int readString(FILE *fp, char** target) {
 
     /* Increase length to also consume \r\n */
     len += 2;
-    *target = (char*)malloc(len);
+    *target = (char*)zmalloc(len);
     if (!readBytes(fp,*target,len)) {
         return 0;
     }
@@ -127,12 +122,12 @@ off_t process(FILE *fp) {
                     }
                 }
             }
-            free(str);
+            zfree(str);
         }
 
         /* Stop if the loop did not finish */
         if (i < argc) {
-            if (str) free(str);
+            if (str) zfree(str);
             break;
         }
     }
@@ -146,7 +141,7 @@ off_t process(FILE *fp) {
     return pos;
 }
 
-int main(int argc, char **argv) {
+int redis_check_aof_main(int argc, char **argv) {
     char *filename;
     int fix = 0;
 
@@ -185,6 +180,25 @@ int main(int argc, char **argv) {
         exit(1);
     }
 
+    /* This AOF file may have an RDB preamble. Check this to start, and if this
+     * is the case, start processing the RDB part. */
+    if (size >= 8) {    /* There must be at least room for the RDB header. */
+        char sig[5];
+        int has_preamble = fread(sig,sizeof(sig),1,fp) == 1 &&
+                            memcmp(sig,"REDIS",sizeof(sig)) == 0;
+        rewind(fp);
+        if (has_preamble) {
+            printf("The AOF appears to start with an RDB preamble.\n"
+                   "Checking the RDB preamble to start:\n");
+            if (redis_check_rdb_main(argc,argv,fp) == C_ERR) {
+                printf("RDB preamble of AOF file is not sane, aborting.\n");
+                exit(1);
+            } else {
+                printf("RDB preamble is OK, proceding with AOF tail...\n");
+            }
+        }
+    }
+
     off_t pos = process(fp);
     off_t diff = size-pos;
     printf("AOF analyzed: size=%lld, ok_up_to=%lld, diff=%lld\n",
@@ -214,5 +228,5 @@ int main(int argc, char **argv) {
     }
 
     fclose(fp);
-    return 0;
+    exit(0);
 }