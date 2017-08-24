@@ -76,6 +76,7 @@ th_print_long_ls(TAR *t)
   char groupname[_POSIX_LOGIN_NAME_MAX];
   time_t mtime;
   struct tm *mtm;
+  char *pathname = 0;
 
 #ifdef HAVE_STRFTIME
   char timebuf[18];
@@ -124,7 +125,12 @@ th_print_long_ls(TAR *t)
          mtm->tm_mday, mtm->tm_hour, mtm->tm_min, mtm->tm_year + 1900);
 #endif
 
-  printf(" %s", th_get_pathname(t));
+  pathname = th_get_pathname(t);
+  if (pathname)
+    {
+    printf(" %s", pathname);
+    free(pathname);
+    }
 
 #if !defined(_WIN32) || defined(__CYGWIN__)
   if (TH_ISSYM(t) || TH_ISLNK(t))
@@ -142,5 +148,3 @@ th_print_long_ls(TAR *t)
 
   putchar('\n');
 }
-
-