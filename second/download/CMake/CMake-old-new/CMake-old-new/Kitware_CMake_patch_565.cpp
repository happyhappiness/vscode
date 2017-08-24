@@ -106,6 +106,11 @@ tar_set_file_perms(TAR *t, char *realname)
     return -1;
   }
 
+#else /* WIN32 */
+  (void)filename;
+  (void)gid;
+  (void)uid;
+  (void)mode;
 #endif /* WIN32 */
 
   return 0;
@@ -273,6 +278,11 @@ tar_extract_regfile(TAR *t, char *realname)
   printf("### done extracting %s\n", filename);
 #endif
 
+  (void)filename;
+  (void)gid;
+  (void)uid;
+  (void)mode;
+
   return 0;
 }
 
@@ -340,6 +350,8 @@ tar_extract_hardlink(TAR * t, char *realname)
 #endif
 #ifndef WIN32
   if (link(linktgt, filename) == -1)
+#else
+  (void)linktgt;
 #endif
   {
 #ifdef DEBUG
@@ -421,6 +433,10 @@ tar_extract_chardev(TAR *t, char *realname)
 #ifndef WIN32
   if (mknod(filename, mode | S_IFCHR,
       compat_makedev(devmaj, devmin)) == -1)
+#else
+  (void)devmin;
+  (void)devmaj;
+  (void)mode;
 #endif
   {
 #ifdef DEBUG
@@ -462,6 +478,10 @@ tar_extract_blockdev(TAR *t, char *realname)
 #ifndef WIN32
   if (mknod(filename, mode | S_IFBLK,
       compat_makedev(devmaj, devmin)) == -1)
+#else
+  (void)devmin;
+  (void)devmaj;
+  (void)mode;
 #endif
   {
 #ifdef DEBUG
@@ -557,6 +577,8 @@ tar_extract_fifo(TAR *t, char *realname)
 #endif
 #ifndef WIN32
   if (mkfifo(filename, mode) == -1)
+#else
+    (void)mode;
 #endif
   {
 #ifdef DEBUG