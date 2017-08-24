@@ -13,10 +13,12 @@
 #include <libtarint/internal.h>
 
 #include <stdio.h>
-#ifndef WIN32
-#include <pwd.h>
-#include <grp.h>
+
+#if !defined(_WIN32) || defined(__CYGWIN__)
+# include <pwd.h>
+# include <grp.h>
 #endif
+
 #include <time.h>
 #include <limits.h>
 
@@ -64,7 +66,7 @@ void
 th_print_long_ls(TAR *t)
 {
   char modestring[12];
-#ifndef WIN32
+#if !defined(_WIN32) || defined(__CYGWIN__)
   struct passwd *pw;
   struct group *gr;
 #endif
@@ -85,26 +87,26 @@ th_print_long_ls(TAR *t)
 #endif
 
   uid = th_get_uid(t);
-#ifndef WIN32
+#if !defined(_WIN32) || defined(__CYGWIN__)
   pw = getpwuid(uid);
   if (pw != NULL)
     strlcpy(username, pw->pw_name, sizeof(username));
   else
 #endif
-    snprintf(username, sizeof(username), "%d", uid);
+    snprintf(username, sizeof(username), "%d", (int)uid);
   gid = th_get_gid(t);
-#ifndef WIN32
+#if !defined(_WIN32) || defined(__CYGWIN__)
   gr = getgrgid(gid);
   if (gr != NULL)
     strlcpy(groupname, gr->gr_name, sizeof(groupname));
   else
 #endif
-    snprintf(groupname, sizeof(groupname), "%d", gid);
+    snprintf(groupname, sizeof(groupname), "%d", (int)gid);
     
   strmode(th_get_mode(t), modestring);
   printf("%.10s %-8.8s %-8.8s ", modestring, username, groupname);
 
-#ifndef WIN32
+#if !defined(_WIN32) || defined(__CYGWIN__)
   if (TH_ISCHR(t) || TH_ISBLK(t))
     printf(" %3d, %3d ", th_get_devmajor(t), th_get_devminor(t));
   else
@@ -124,7 +126,7 @@ th_print_long_ls(TAR *t)
 
   printf(" %s", th_get_pathname(t));
 
-#ifndef _WIN32
+#if !defined(_WIN32) || defined(__CYGWIN__)
   if (TH_ISSYM(t) || TH_ISLNK(t))
   {
     if (TH_ISSYM(t))