@@ -14,11 +14,13 @@
 
 #include <stdio.h>
 #include <libtar/compat.h>
-#if defined(_WIN32) && !defined(__CYGWIN__)
-#include <libtarint/filesystem.h>
-#else
+#if defined(HAVE_SYS_PARAM_H)
 #include <sys/param.h>
+#endif
+#if defined(HAVE_DIRENT_H)
 #include <dirent.h>
+#else
+#include <libtarint/filesystem.h>
 #endif
 #include <errno.h>
 
@@ -102,14 +104,23 @@ tar_append_tree(TAR *t, char *realdir, char *savedir)
 {
   char realpath[TAR_MAXPATHLEN];
   char savepath[TAR_MAXPATHLEN];
-#if !defined(_WIN32) || defined(__CYGWIN__)
+  size_t plen;
+#if defined(HAVE_DIRENT_H)
   struct dirent *dent;
   DIR *dp;
 #else  
   kwDirEntry * dent;
   kwDirectory *dp;
 #endif  
   struct stat s;
+  strncpy(realpath, realdir, sizeof(realpath));
+  realpath[sizeof(realpath)-1] = 0;
+  plen = strlen(realpath);
+  if ( realpath[plen-1] == '/' )
+    {
+    realpath[plen-1] = 0;
+    }
+  
 
 #ifdef DEBUG
   printf("==> tar_append_tree(0x%lx, \"%s\", \"%s\")\n",
@@ -123,10 +134,22 @@ tar_append_tree(TAR *t, char *realdir, char *savedir)
   puts("    tar_append_tree(): done with tar_append_file()...");
 #endif
 
+  if ( stat(realpath, &s) != 0 )
+    {
+    return -1;   
+    }
+  if ( 
 #if defined(_WIN32) && !defined(__CYGWIN__)
-  dp = kwOpenDir(realdir);
+    (s.st_mode & _S_IFDIR) == 0
 #else
+    !S_ISDIR(s.st_mode)
+#endif
+  )
+    return 0;
+#if defined(HAVE_DIRENT_H)
   dp = opendir(realdir);
+#else
+  dp = kwOpenDir(realdir);
 #endif
 
   if (dp == NULL)
@@ -135,10 +158,10 @@ tar_append_tree(TAR *t, char *realdir, char *savedir)
       return 0;
     return -1;
   }
-#if defined(_WIN32) && !defined(__CYGWIN__)
-  while ((dent = kwReadDir(dp)) != NULL)
-#else
+#if defined(HAVE_DIRENT_H)
   while ((dent = readdir(dp)) != NULL)
+#else
+  while ((dent = kwReadDir(dp)) != NULL)
 #endif
   {
     if (strcmp(dent->d_name, ".") == 0 ||
@@ -171,10 +194,10 @@ tar_append_tree(TAR *t, char *realdir, char *savedir)
       return -1;
   }
 
-#if defined(_WIN32) && !defined(__CYGWIN__)
-  kwCloseDir(dp);
-#else
+#if defined(HAVE_DIRENT_H)
   closedir(dp);
+#else
+  kwCloseDir(dp);
 #endif
 
   return 0;