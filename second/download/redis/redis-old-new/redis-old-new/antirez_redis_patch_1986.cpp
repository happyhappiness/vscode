@@ -65,8 +65,8 @@
 /* data type to hold offset in file and size */
 typedef struct {
     void *data;
-    unsigned long size;
-    unsigned long offset;
+    uint64_t size;
+    uint64_t offset;
 } pos;
 
 static unsigned char level = 0;
@@ -77,8 +77,8 @@ static pos positions[16];
 /* Hold a stack of errors */
 typedef struct {
     char error[16][1024];
-    unsigned long offset[16];
-    unsigned int level;
+    uint64_t offset[16];
+    uint32_t level;
 } errors_t;
 static errors_t errors;
 
@@ -494,15 +494,15 @@ void printCentered(int indent, int width, char* body) {
     printf("%s %s %s\n", head, body, tail);
 }
 
-void printValid(int ops, int bytes) {
+void printValid(uint64_t ops, uint64_t bytes) {
     char body[80];
-    sprintf(body, "Processed %d valid opcodes (in %d bytes)", ops, bytes);
+    sprintf(body, "Processed %llu valid opcodes (in %llu bytes)", ops, bytes);
     printCentered(4, 80, body);
 }
 
-void printSkipped(int bytes, int offset) {
+void printSkipped(uint64_t bytes, uint64_t offset) {
     char body[80];
-    sprintf(body, "Skipped %d bytes (resuming at 0x%08x)", bytes, offset);
+    sprintf(body, "Skipped %llu bytes (resuming at 0x%08llx)", bytes, offset);
     printCentered(4, 80, body);
 }
 
@@ -536,12 +536,12 @@ void printErrorStack(entry *e) {
 
     /* display error stack */
     for (i = 0; i < errors.level; i++) {
-        printf("0x%08lx - %s\n", errors.offset[i], errors.error[i]);
+        printf("0x%08llx - %s\n", errors.offset[i], errors.error[i]);
     }
 }
 
 void process() {
-    int i, num_errors = 0, num_valid_ops = 0, num_valid_bytes = 0;
+    uint64_t num_errors = 0, num_valid_ops = 0, num_valid_bytes = 0;
     entry entry;
     processHeader();
 
@@ -558,7 +558,9 @@ void process() {
             num_valid_bytes = 0;
 
             /* search for next valid entry */
-            unsigned long offset = positions[0].offset + 1;
+            uint64_t offset = positions[0].offset + 1;
+            int i = 0;
+
             while (!entry.success && offset < positions[0].size) {
                 positions[1].offset = offset;
 
@@ -606,9 +608,9 @@ void process() {
     }
 
     /* print summary on errors */
-    if (num_errors > 0) {
+    if (num_errors) {
         printf("\n");
-        printf("Total unprocessable opcodes: %d\n", num_errors);
+        printf("Total unprocessable opcodes: %llu\n", num_errors);
     }
 }
 
@@ -620,7 +622,7 @@ int main(int argc, char **argv) {
     }
 
     int fd;
-    unsigned long size;
+    size_t size;
     struct stat stat;
     void *data;
 