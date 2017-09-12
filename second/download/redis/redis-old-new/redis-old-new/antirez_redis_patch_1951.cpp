@@ -65,8 +65,8 @@
 /* data type to hold offset in file and size */
 typedef struct {
     void *data;
-    unsigned long size;
-    unsigned long offset;
+    size_t size;
+    size_t offset;
 } pos;
 
 static unsigned char level = 0;
@@ -77,8 +77,8 @@ static pos positions[16];
 /* Hold a stack of errors */
 typedef struct {
     char error[16][1024];
-    unsigned long offset[16];
-    unsigned int level;
+    size_t offset[16];
+    size_t level;
 } errors_t;
 static errors_t errors;
 
@@ -112,7 +112,7 @@ int readBytes(void *target, long num) {
     if (p.offset + num > p.size) {
         return 0;
     } else {
-        memcpy(target, (void*)((unsigned long)p.data + p.offset), num);
+        memcpy(target, (void*)((size_t)p.data + p.offset), num);
         if (!peek) positions[level].offset += num;
     }
     return 1;
@@ -494,15 +494,17 @@ void printCentered(int indent, int width, char* body) {
     printf("%s %s %s\n", head, body, tail);
 }
 
-void printValid(int ops, int bytes) {
+void printValid(uint64_t ops, uint64_t bytes) {
     char body[80];
-    sprintf(body, "Processed %d valid opcodes (in %d bytes)", ops, bytes);
+    sprintf(body, "Processed %llu valid opcodes (in %llu bytes)",
+        (unsigned long long) ops, (unsigned long long) bytes);
     printCentered(4, 80, body);
 }
 
-void printSkipped(int bytes, int offset) {
+void printSkipped(uint64_t bytes, uint64_t offset) {
     char body[80];
-    sprintf(body, "Skipped %d bytes (resuming at 0x%08x)", bytes, offset);
+    sprintf(body, "Skipped %llu bytes (resuming at 0x%08llx)",
+        (unsigned long long) bytes, (unsigned long long) offset);
     printCentered(4, 80, body);
 }
 
@@ -541,7 +543,7 @@ void printErrorStack(entry *e) {
 }
 
 void process() {
-    int i, num_errors = 0, num_valid_ops = 0, num_valid_bytes = 0;
+    uint64_t num_errors = 0, num_valid_ops = 0, num_valid_bytes = 0;
     entry entry;
     processHeader();
 
@@ -558,7 +560,9 @@ void process() {
             num_valid_bytes = 0;
 
             /* search for next valid entry */
-            unsigned long offset = positions[0].offset + 1;
+            uint64_t offset = positions[0].offset + 1;
+            int i = 0;
+
             while (!entry.success && offset < positions[0].size) {
                 positions[1].offset = offset;
 
@@ -606,9 +610,10 @@ void process() {
     }
 
     /* print summary on errors */
-    if (num_errors > 0) {
+    if (num_errors) {
         printf("\n");
-        printf("Total unprocessable opcodes: %d\n", num_errors);
+        printf("Total unprocessable opcodes: %llu\n",
+            (unsigned long long) num_errors);
     }
 }
 
@@ -620,7 +625,7 @@ int main(int argc, char **argv) {
     }
 
     int fd;
-    unsigned long size;
+    off_t size;
     struct stat stat;
     void *data;
 
@@ -634,6 +639,10 @@ int main(int argc, char **argv) {
         size = stat.st_size;
     }
 
+    if (sizeof(size_t) == sizeof(int32_t) && size >= INT_MAX) {
+        ERROR("Cannot check dump files >2GB on a 32-bit platform\n");
+    }
+
     data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
     if (data == MAP_FAILED) {
         ERROR("Cannot mmap: %s\n", argv[1]);