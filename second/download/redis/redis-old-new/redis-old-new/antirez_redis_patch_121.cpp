@@ -304,15 +304,26 @@ float zmalloc_get_fragmentation_ratio(size_t rss) {
  * /proc/self/smaps. The field must be specified with trailing ":" as it
  * apperas in the smaps output.
  *
- * Example: zmalloc_get_smap_bytes_by_field("Rss:");
+ * If a pid is specified, the information is extracted for such a pid,
+ * otherwise if pid is -1 the information is reported is about the
+ * current process.
+ *
+ * Example: zmalloc_get_smap_bytes_by_field("Rss:",-1);
  */
 #if defined(HAVE_PROC_SMAPS)
-size_t zmalloc_get_smap_bytes_by_field(char *field) {
+size_t zmalloc_get_smap_bytes_by_field(char *field, long pid) {
     char line[1024];
     size_t bytes = 0;
-    FILE *fp = fopen("/proc/self/smaps","r");
     int flen = strlen(field);
 
+    if (pid == -1) {
+        FILE *fp = fopen("/proc/self/smaps","r");
+    } else {
+        char filename[128];
+        snprintf(filename,sizeof(filename),"/proc/%ld/smaps",pid);
+        FILE *fp = fopen(filename,"r");
+    }
+
     if (!fp) return 0;
     while(fgets(line,sizeof(line),fp) != NULL) {
         if (strncmp(line,field,flen) == 0) {
@@ -327,14 +338,15 @@ size_t zmalloc_get_smap_bytes_by_field(char *field) {
     return bytes;
 }
 #else
-size_t zmalloc_get_smap_bytes_by_field(char *field) {
+size_t zmalloc_get_smap_bytes_by_field(char *field, long pid) {
     ((void) field);
+    ((void) pid);
     return 0;
 }
 #endif
 
-size_t zmalloc_get_private_dirty(void) {
-    return zmalloc_get_smap_bytes_by_field("Private_Dirty:");
+size_t zmalloc_get_private_dirty(long pid) {
+    return zmalloc_get_smap_bytes_by_field("Private_Dirty:",pid);
 }
 
 /* Returns the size of physical memory (RAM) in bytes.