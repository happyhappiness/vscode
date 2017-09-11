@@ -315,13 +315,14 @@ size_t zmalloc_get_smap_bytes_by_field(char *field, long pid) {
     char line[1024];
     size_t bytes = 0;
     int flen = strlen(field);
+    FILE *fp;
 
     if (pid == -1) {
-        FILE *fp = fopen("/proc/self/smaps","r");
+        fp = fopen("/proc/self/smaps","r");
     } else {
         char filename[128];
         snprintf(filename,sizeof(filename),"/proc/%ld/smaps",pid);
-        FILE *fp = fopen(filename,"r");
+        fp = fopen(filename,"r");
     }
 
     if (!fp) return 0;