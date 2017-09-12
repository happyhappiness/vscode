@@ -65,8 +65,8 @@
 /* data type to hold offset in file and size */
 typedef struct {
     void *data;
-    uint64_t size;
-    uint64_t offset;
+    size_t size;
+    size_t offset;
 } pos;
 
 static unsigned char level = 0;
@@ -77,8 +77,8 @@ static pos positions[16];
 /* Hold a stack of errors */
 typedef struct {
     char error[16][1024];
-    uint64_t offset[16];
-    uint32_t level;
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
@@ -536,7 +536,7 @@ void printErrorStack(entry *e) {
 
     /* display error stack */
     for (i = 0; i < errors.level; i++) {
-        printf("0x%08llx - %s\n", errors.offset[i], errors.error[i]);
+        printf("0x%08lx - %s\n", errors.offset[i], errors.error[i]);
     }
 }
 
@@ -622,7 +622,7 @@ int main(int argc, char **argv) {
     }
 
     int fd;
-    size_t size;
+    off_t size;
     struct stat stat;
     void *data;
 
@@ -636,6 +636,10 @@ int main(int argc, char **argv) {
         size = stat.st_size;
     }
 
+    if (sizeof(size_t) == sizeof(int32_t) && size >= INT_MAX) {
+        ERROR("Cannot check dump files >2GB on a 32-bit platform\n");
+    }
+
     data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
     if (data == MAP_FAILED) {
         ERROR("Cannot mmap: %s\n", argv[1]);