@@ -9,11 +9,11 @@
 #define ERROR(...) { \
     char __buf[1024]; \
     sprintf(__buf, __VA_ARGS__); \
-    sprintf(error, "0x%08lx: %s", epos, __buf); \
+    sprintf(error, "0x%16llx: %s", (long long)epos, __buf); \
 }
 
 static char error[1024];
-static long epos;
+static off_t epos;
 
 int consumeNewline(char *buf) {
     if (strncmp(buf,"\r\n",2) != 0) {
@@ -25,7 +25,7 @@ int consumeNewline(char *buf) {
 
 int readLong(FILE *fp, char prefix, long *target) {
     char buf[128], *eptr;
-    epos = ftell(fp);
+    epos = ftello(fp);
     if (fgets(buf,sizeof(buf),fp) == NULL) {
         return 0;
     }
@@ -39,7 +39,7 @@ int readLong(FILE *fp, char prefix, long *target) {
 
 int readBytes(FILE *fp, char *target, long length) {
     long real;
-    epos = ftell(fp);
+    epos = ftello(fp);
     real = fread(target,1,length,fp);
     if (real != length) {
         ERROR("Expected to read %ld bytes, got %ld bytes",length,real);
@@ -72,13 +72,14 @@ int readArgc(FILE *fp, long *target) {
     return readLong(fp,'*',target);
 }
 
-long process(FILE *fp) {
-    long argc, pos = 0;
+off_t process(FILE *fp) {
+    long argc;
+    off_t pos = 0;
     int i, multi = 0;
     char *str;
 
     while(1) {
-        if (!multi) pos = ftell(fp);
+        if (!multi) pos = ftello(fp);
         if (!readArgc(fp, &argc)) break;
 
         for (i = 0; i < argc; i++) {
@@ -148,18 +149,20 @@ int main(int argc, char **argv) {
         exit(1);
     }
 
-    long size = sb.st_size;
+    off_t size = sb.st_size;
     if (size == 0) {
         printf("Empty file: %s\n", filename);
         exit(1);
     }
 
-    long pos = process(fp);
-    long diff = size-pos;
+    off_t pos = process(fp);
+    off_t diff = size-pos;
+    printf("AOF analyzed: size=%lld, ok_up_to=%lld, diff=%lld\n",
+        (long long) size, (long long) pos, (long long) diff);
     if (diff > 0) {
         if (fix) {
             char buf[2];
-            printf("This will shrink the AOF from %ld bytes, with %ld bytes, to %ld bytes\n",size,diff,pos);
+            printf("This will shrink the AOF from %lld bytes, with %lld bytes, to %lld bytes\n",(long long)size,(long long)diff,(long long)pos);
             printf("Continue? [y/N]: ");
             if (fgets(buf,sizeof(buf),stdin) == NULL ||
                 strncasecmp(buf,"y",1) != 0) {