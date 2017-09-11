@@ -28,9 +28,11 @@
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
-
 #include "redis.h"
 
+#include <fcntl.h>
+#include <sys/stat.h>
+
 static struct {
     const char     *name;
     const int       value;
@@ -1465,6 +1467,63 @@ void rewriteConfigRemoveOrphaned(struct rewriteConfigState *state) {
     dictReleaseIterator(di);
 }
 
+/* This function overwrites the old configuration file with the new content.
+ *
+ * 1) The old file length is obtained.
+ * 2) If the new content is smaller, padding is added.
+ * 3) A single write(2) call is used to replace the content of the file.
+ * 4) Later the file is truncated to the length of the new content.
+ *
+ * This way we are sure the file is left in a consistent state even if the
+ * process is stopped between any of the four operations.
+ *
+ * The function returns 0 on success, otherwise -1 is returned and errno
+ * set accordingly. */
+int rewriteConfigOverwriteFile(char *configfile, sds content) {
+    int retval = 0;
+    int fd = open(configfile,O_RDWR|O_CREAT);
+    int content_size = sdslen(content), padding = 0;
+    struct stat sb;
+    sds content_padded;
+
+    /* 1) Open the old file (or create a new one if it does not
+     *    exist), get the size. */
+    if (fd == -1) return -1; /* errno set by open(). */
+    if (fstat(fd,&sb) == -1) {
+        close(fd);
+        return -1; /* errno set by fstat(). */
+    }
+
+    /* 2) Pad the content at least match the old file size. */
+    content_padded = sdsdup(content);
+    if (content_size < sb.st_size) {
+        /* If the old file was bigger, pad the content with
+         * a newline plus as many "#" chars as required. */
+        padding = sb.st_size - content_size;
+        content_padded = sdsgrowzero(content_padded,sb.st_size);
+        content_padded[content_size] = '\n';
+        memset(content_padded+content_size+1,'#',padding-1);
+    }
+
+    /* 3) Write the new content using a single write(2). */
+    if (write(fd,content_padded,strlen(content_padded)) == -1) {
+        retval = -1;
+        goto cleanup;
+    }
+
+    /* 4) Truncate the file to the right length if we used padding. */
+    if (padding) {
+        if (ftruncate(fd,content_size) == -1) {
+            /* Non critical error... */
+        }
+    }
+
+cleanup:
+    sdsfree(content_padded);
+    close(fd);
+    return retval;
+}
+
 /* Rewrite the configuration file at "path".
  * If the configuration file already exists, we try at best to retain comments
  * and overall structure.
@@ -1476,6 +1535,7 @@ void rewriteConfigRemoveOrphaned(struct rewriteConfigState *state) {
 int rewriteConfig(char *path) {
     struct rewriteConfigState *state;
     sds newcontent;
+    int retval;
 
     /* Step 1: read the old config into our rewrite state. */
     if ((state = rewriteConfigReadOldFile(path)) == NULL) return -1;
@@ -1567,11 +1627,11 @@ int rewriteConfig(char *path) {
     /* Step 4: generate a new configuration file from the modified state
      * and write it into the original file. */
     newcontent = rewriteConfigGetContentFromState(state);
-    printf("%s\n", newcontent);
+    retval = rewriteConfigOverwriteFile(server.configfile,newcontent);
 
     sdsfree(newcontent);
     rewriteConfigReleaseState(state);
-    return 0;
+    return retval;
 }
 
 /*-----------------------------------------------------------------------------