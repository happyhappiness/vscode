@@ -39,24 +39,49 @@ tar_extract_glob(TAR *t, char *globname, char *prefix)
   char *filename;
   char buf[TAR_MAXPATHLEN];
   int i;
+  char *pathname = 0;
 
   while ((i = th_read(t)) == 0)
   {
-    filename = th_get_pathname(t);
+    pathname = th_get_pathname(t);
+    filename = pathname;
+
     if (fnmatch(globname, filename, FNM_PATHNAME | FNM_PERIOD))
     {
+      if (pathname)
+        {
+        free(pathname);
+        pathname = 0;
+        }
+
       if (TH_ISREG(t) && tar_skip_regfile(t))
         return -1;
       continue;
     }
+
     if (t->options & TAR_VERBOSE)
       th_print_long_ls(t);
+
     if (prefix != NULL)
       snprintf(buf, sizeof(buf), "%s/%s", prefix, filename);
     else
       strlcpy(buf, filename, sizeof(buf));
+
     if (tar_extract_file(t, filename) != 0)
+      {
+      if (pathname)
+        {
+        free(pathname);
+        pathname = 0;
+        }
       return -1;
+      }
+
+    if (pathname)
+      {
+      free(pathname);
+      pathname = 0;
+      }
   }
 
   return (i == 1 ? 0 : -1);
@@ -69,6 +94,7 @@ tar_extract_all(TAR *t, char *prefix)
   char *filename;
   char buf[TAR_MAXPATHLEN];
   int i;
+  char *pathname = 0;
 
 #ifdef DEBUG
   printf("==> tar_extract_all(TAR *t, \"%s\")\n",
@@ -80,17 +106,28 @@ tar_extract_all(TAR *t, char *prefix)
 #ifdef DEBUG
     puts("    tar_extract_all(): calling th_get_pathname()");
 #endif
-    filename = th_get_pathname(t);
+
+    pathname = th_get_pathname(t);
+    filename = pathname;
+
     if (t->options & TAR_VERBOSE)
       th_print_long_ls(t);
     if (prefix != NULL)
       snprintf(buf, sizeof(buf), "%s/%s", prefix, filename);
     else
       strlcpy(buf, filename, sizeof(buf));
+
+    if (pathname)
+      {
+      free(pathname);
+      pathname = 0;
+      }
+
 #ifdef DEBUG
     printf("    tar_extract_all(): calling tar_extract_file(t, "
            "\"%s\")\n", buf);
 #endif
+
     if (tar_extract_file(t, buf) != 0)
       return -1;
   }