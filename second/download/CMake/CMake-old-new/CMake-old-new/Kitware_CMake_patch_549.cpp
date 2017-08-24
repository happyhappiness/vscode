@@ -116,7 +116,7 @@ tar_set_file_perms(TAR *t, char *realname)
     return -1;
   }
   /* change permissions */
-  if (!TH_ISSYM(t) && chmod(filename, mode) == -1)
+  if (!TH_ISSYM(t) && chmod(filename, mode & 07777) == -1)
   {
 #ifdef DEBUG
     perror("chmod()");
@@ -718,6 +718,7 @@ tar_extract_dir(TAR *t, char *realname)
   char *filename;
   char buf[T_BLOCKSIZE];
   char *pathname = 0;
+  size_t len = 0;
 
   if (!TH_ISDIR(t))
   {
@@ -750,14 +751,23 @@ tar_extract_dir(TAR *t, char *realname)
     return -1;
     }
 
+    /* Strip trailing '/'...it confuses some Unixes (and BeOS)... */
+    strncpy(buf, filename, sizeof(buf)-1);
+    buf[sizeof(buf)-1] = 0;
+    len = strlen(buf);
+    if ((len > 0) && (buf[len-1] == '/'))
+      {
+      buf[len-1] = '\0';
+      }
+
 #ifdef DEBUG
   printf("  ==> extracting: %s (mode %04o, directory)\n", filename,
          mode);
 #endif
 #ifdef WIN32
-  if (mkdir(filename) == -1)
+  if (mkdir(buf) == -1)
 #else
-  if (mkdir(filename, mode) == -1)
+  if (mkdir(buf, mode & 07777) == -1)
 #endif
   {
 #ifdef __BORLANDC__
@@ -772,7 +782,7 @@ tar_extract_dir(TAR *t, char *realname)
 #endif      
     if (errno == EEXIST)
     {
-      if (chmod(filename, mode) == -1)
+      if (chmod(filename, mode & 07777) == -1)
       {
 #ifdef DEBUG
         perror("chmod()");
@@ -860,7 +870,7 @@ tar_extract_fifo(TAR *t, char *realname)
   printf("  ==> extracting: %s (fifo)\n", filename);
 #endif
 #ifndef WIN32
-  if (mkfifo(filename, mode) == -1)
+  if (mkfifo(filename, mode & 07777) == -1)
 #else
     (void)mode;
 #endif