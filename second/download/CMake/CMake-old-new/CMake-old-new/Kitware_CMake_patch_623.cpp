@@ -14,7 +14,7 @@
 
 #include <stdio.h>
 #include <libtar/compat.h>
-#ifdef _MSC_VER
+#if defined(_WIN32) && !defined(__CYGWIN__)
 #include <libtarint/filesystem.h>
 #else
 #include <sys/param.h>
@@ -35,7 +35,7 @@ int
 tar_extract_glob(TAR *t, char *globname, char *prefix)
 {
   char *filename;
-  char buf[MAXPATHLEN];
+  char buf[TAR_MAXPATHLEN];
   int i;
 
   while ((i = th_read(t)) == 0)
@@ -65,7 +65,7 @@ int
 tar_extract_all(TAR *t, char *prefix)
 {
   char *filename;
-  char buf[MAXPATHLEN];
+  char buf[TAR_MAXPATHLEN];
   int i;
 
 #ifdef DEBUG
@@ -100,9 +100,9 @@ tar_extract_all(TAR *t, char *prefix)
 int
 tar_append_tree(TAR *t, char *realdir, char *savedir)
 {
-  char realpath[MAXPATHLEN];
-  char savepath[MAXPATHLEN];
-#ifndef _MSC_VER
+  char realpath[TAR_MAXPATHLEN];
+  char savepath[TAR_MAXPATHLEN];
+#if !defined(_WIN32) || defined(__CYGWIN__)
   struct dirent *dent;
   DIR *dp;
 #else  
@@ -123,7 +123,7 @@ tar_append_tree(TAR *t, char *realdir, char *savedir)
   puts("    tar_append_tree(): done with tar_append_file()...");
 #endif
 
-#ifdef _MSC_VER
+#if defined(_WIN32) && !defined(__CYGWIN__)
   dp = kwOpenDir(realdir);
 #else
   dp = opendir(realdir);
@@ -135,7 +135,7 @@ tar_append_tree(TAR *t, char *realdir, char *savedir)
       return 0;
     return -1;
   }
-#ifdef _MSC_VER
+#if defined(_WIN32) && !defined(__CYGWIN__)
   while ((dent = kwReadDir(dp)) != NULL)
 #else
   while ((dent = readdir(dp)) != NULL)
@@ -145,10 +145,10 @@ tar_append_tree(TAR *t, char *realdir, char *savedir)
         strcmp(dent->d_name, "..") == 0)
       continue;
 
-    snprintf(realpath, MAXPATHLEN, "%s/%s", realdir,
+    snprintf(realpath, TAR_MAXPATHLEN, "%s/%s", realdir,
        dent->d_name);
     if (savedir)
-      snprintf(savepath, MAXPATHLEN, "%s/%s", savedir,
+      snprintf(savepath, TAR_MAXPATHLEN, "%s/%s", savedir,
          dent->d_name);
 
 #ifndef WIN32
@@ -171,7 +171,7 @@ tar_append_tree(TAR *t, char *realdir, char *savedir)
       return -1;
   }
 
-#ifdef _MSC_VER
+#if defined(_WIN32) && !defined(__CYGWIN__)
   kwCloseDir(dp);
 #else
   closedir(dp);