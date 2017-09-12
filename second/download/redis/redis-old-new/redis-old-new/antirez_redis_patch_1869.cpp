@@ -38,6 +38,7 @@
 #include <ctype.h>
 #include <errno.h>
 #include <sys/stat.h>
+#include <sys/time.h>
 
 #include "anet.h"
 #include "sds.h"
@@ -67,6 +68,49 @@ static struct config {
 static int cliReadReply(int fd);
 static void usage();
 
+/*------------------------------------------------------------------------------
+ * Utility functions
+ *--------------------------------------------------------------------------- */
+
+static long long mstime(void) {
+    struct timeval tv;
+    long long mst;
+
+    gettimeofday(&tv, NULL);
+    mst = ((long)tv.tv_sec)*1000;
+    mst += tv.tv_usec/1000;
+    return mst;
+}
+
+static void printStringRepr(char *s, int len) {
+    printf("\"");
+    while(len--) {
+        switch(*s) {
+        case '\\':
+        case '"':
+            printf("\\%c",*s);
+            break;
+        case '\n': printf("\\n"); break;
+        case '\r': printf("\\r"); break;
+        case '\t': printf("\\t"); break;
+        case '\a': printf("\\a"); break;
+        case '\b': printf("\\b"); break;
+        default:
+            if (isprint(*s))
+                printf("%c",*s);
+            else
+                printf("\\x%02x",(unsigned char)*s);
+            break;
+        }
+        s++;
+    }
+    printf("\"");
+}
+
+/*------------------------------------------------------------------------------
+ * Networking / parsing
+ *--------------------------------------------------------------------------- */
+
 /* Connect to the client. If force is not zero the connection is performed
  * even if there is already a connected socket. */
 static int cliConnect(int force) {
@@ -115,31 +159,6 @@ static int cliReadSingleLineReply(int fd, int quiet) {
     return 0;
 }
 
-static void printStringRepr(char *s, int len) {
-    printf("\"");
-    while(len--) {
-        switch(*s) {
-        case '\\':
-        case '"':
-            printf("\\%c",*s);
-            break;
-        case '\n': printf("\\n"); break;
-        case '\r': printf("\\r"); break;
-        case '\t': printf("\\t"); break;
-        case '\a': printf("\\a"); break;
-        case '\b': printf("\\b"); break;
-        default:
-            if (isprint(*s))
-                printf("%c",*s);
-            else
-                printf("\\x%02x",(unsigned char)*s);
-            break;
-        }
-        s++;
-    }
-    printf("\"");
-}
-
 static int cliReadBulkReply(int fd) {
     sds replylen = cliReadLine(fd);
     char *reply, crlf[2];
@@ -318,6 +337,10 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     return 0;
 }
 
+/*------------------------------------------------------------------------------
+ * User interface
+ *--------------------------------------------------------------------------- */
+
 static int parseOptions(int argc, char **argv) {
     int i;
 
@@ -429,6 +452,7 @@ static void repl() {
                     exit(0);
                 } else {
                     int err;
+                    long long start_time = mstime(), elapsed;
 
                     if ((err = cliSendCommand(argc, argv, 1)) != 0) {
                         if (err == ECONNRESET) {
@@ -439,6 +463,9 @@ static void repl() {
                             cliSendCommand(argc,argv,1);
                         }
                     }
+                    elapsed = mstime()-start_time;
+                    if (elapsed > 500) printf("%.2f seconds\n",
+                        (double)elapsed/1000);
                 }
             }
             /* Free the argument vector */