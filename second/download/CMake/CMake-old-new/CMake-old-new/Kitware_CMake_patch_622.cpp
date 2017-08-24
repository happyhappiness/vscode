@@ -15,7 +15,7 @@
 #include <stdio.h>
 #include <errno.h>
 #include <fcntl.h>
-#ifdef _MSC_VER
+#if defined(_WIN32) && !defined(__CYGWIN__)
 # include <libtar/compat.h>
 #else
 # include <sys/param.h>
@@ -45,7 +45,7 @@ typedef struct tar_dev tar_dev_t;
 struct tar_ino
 {
   ino_t ti_ino;
-  char ti_name[MAXPATHLEN];
+  char ti_name[TAR_MAXPATHLEN];
 };
 typedef struct tar_ino tar_ino_t;
 
@@ -68,7 +68,7 @@ tar_append_file(TAR *t, char *realname, char *savename)
   libtar_hashptr_t hp;
   tar_dev_t *td = NULL;
   tar_ino_t *ti = NULL;
-  char path[MAXPATHLEN];
+  char path[TAR_MAXPATHLEN];
 
 #ifdef DEBUG
   printf("==> tar_append_file(TAR=0x%lx (\"%s\"), realname=\"%s\", "
@@ -162,8 +162,8 @@ tar_append_file(TAR *t, char *realname, char *savename)
 #endif
     if (i == -1)
       return -1;
-    if (i >= MAXPATHLEN)
-      i = MAXPATHLEN - 1;
+    if (i >= TAR_MAXPATHLEN)
+      i = TAR_MAXPATHLEN - 1;
     path[i] = '\0';
 #ifdef DEBUG
     printf("    tar_append_file(): encoding symlink \"%s\" -> "