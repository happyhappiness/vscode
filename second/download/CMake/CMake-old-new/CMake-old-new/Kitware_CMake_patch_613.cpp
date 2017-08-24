@@ -213,10 +213,11 @@ tar_extract_regfile(TAR *t, char *realname)
   uid = th_get_uid(t);
   gid = th_get_gid(t);
 
+  /* Make a copy of the string because dirname and mkdirhier may modify the
+   * string */
   strncpy(buf, filename, sizeof(buf)-1);
   buf[sizeof(buf)-1] = 0;
 
-
   if (mkdirhier(dirname(buf)) == -1)
     {
     return -1;
@@ -331,6 +332,7 @@ tar_extract_hardlink(TAR * t, char *realname)
   char *linktgt = NULL;
   linkname_t *lnp;
   libtar_hashptr_t hp;
+  char buf[T_BLOCKSIZE];
 
   if (!TH_ISLNK(t))
   {
@@ -339,7 +341,13 @@ tar_extract_hardlink(TAR * t, char *realname)
   }
 
   filename = (realname ? realname : th_get_pathname(t));
-  if (mkdirhier(dirname(filename)) == -1)
+
+  /* Make a copy of the string because dirname and mkdirhier may modify the
+   * string */
+  strncpy(buf, filename, sizeof(buf)-1);
+  buf[sizeof(buf)-1] = 0;
+
+  if (mkdirhier(dirname(buf)) == -1)
     return -1;
   libtar_hashptr_reset(&hp);
   if (libtar_hash_getkey(t->h, &hp, th_get_linkname(t),
@@ -375,6 +383,7 @@ int
 tar_extract_symlink(TAR *t, char *realname)
 {
   char *filename;
+  char buf[T_BLOCKSIZE];
 
 #ifndef _WIN32
   if (!TH_ISSYM(t))
@@ -385,11 +394,19 @@ tar_extract_symlink(TAR *t, char *realname)
 #endif
 
   filename = (realname ? realname : th_get_pathname(t));
-  if (mkdirhier(dirname(filename)) == -1)
+
+  /* Make a copy of the string because dirname and mkdirhier may modify the
+   * string */
+  strncpy(buf, filename, sizeof(buf)-1);
+  buf[sizeof(buf)-1] = 0;
+
+  if (mkdirhier(dirname(buf)) == -1)
     return -1;
 
   if (unlink(filename) == -1 && errno != ENOENT)
+    {
     return -1;
+    }
 
 #ifdef DEBUG
   printf("  ==> extracting: %s (symlink to %s)\n",
@@ -416,6 +433,7 @@ tar_extract_chardev(TAR *t, char *realname)
   mode_t mode;
   unsigned long devmaj, devmin;
   char *filename;
+  char buf[T_BLOCKSIZE];
 
 #ifndef _WIN32
   if (!TH_ISCHR(t))
@@ -429,7 +447,12 @@ tar_extract_chardev(TAR *t, char *realname)
   devmaj = th_get_devmajor(t);
   devmin = th_get_devminor(t);
 
-  if (mkdirhier(dirname(filename)) == -1)
+  /* Make a copy of the string because dirname and mkdirhier may modify the
+   * string */
+  strncpy(buf, filename, sizeof(buf)-1);
+  buf[sizeof(buf)-1] = 0;
+
+  if (mkdirhier(dirname(buf)) == -1)
     return -1;
 
 #ifdef DEBUG
@@ -462,6 +485,7 @@ tar_extract_blockdev(TAR *t, char *realname)
   mode_t mode;
   unsigned long devmaj, devmin;
   char *filename;
+  char buf[T_BLOCKSIZE];
 
   if (!TH_ISBLK(t))
   {
@@ -474,7 +498,12 @@ tar_extract_blockdev(TAR *t, char *realname)
   devmaj = th_get_devmajor(t);
   devmin = th_get_devminor(t);
 
-  if (mkdirhier(dirname(filename)) == -1)
+  /* Make a copy of the string because dirname and mkdirhier may modify the
+   * string */
+  strncpy(buf, filename, sizeof(buf)-1);
+  buf[sizeof(buf)-1] = 0;
+
+  if (mkdirhier(dirname(buf)) == -1)
     return -1;
 
 #ifdef DEBUG
@@ -506,6 +535,7 @@ tar_extract_dir(TAR *t, char *realname)
 {
   mode_t mode;
   char *filename;
+  char buf[T_BLOCKSIZE];
 
   if (!TH_ISDIR(t))
   {
@@ -516,7 +546,12 @@ tar_extract_dir(TAR *t, char *realname)
   filename = (realname ? realname : th_get_pathname(t));
   mode = th_get_mode(t);
 
-  if (mkdirhier(dirname(filename)) == -1)
+  /* Make a copy of the string because dirname and mkdirhier may modify the
+   * string */
+  strncpy(buf, filename, sizeof(buf)-1);
+  buf[sizeof(buf)-1] = 0;
+
+  if (mkdirhier(dirname(buf)) == -1)
     return -1;
 
 #ifdef DEBUG
@@ -565,6 +600,7 @@ tar_extract_fifo(TAR *t, char *realname)
 {
   mode_t mode;
   char *filename;
+  char buf[T_BLOCKSIZE];
 
   if (!TH_ISFIFO(t))
   {
@@ -575,7 +611,12 @@ tar_extract_fifo(TAR *t, char *realname)
   filename = (realname ? realname : th_get_pathname(t));
   mode = th_get_mode(t);
 
-  if (mkdirhier(dirname(filename)) == -1)
+  /* Make a copy of the string because dirname and mkdirhier may modify the
+   * string */
+  strncpy(buf, filename, sizeof(buf)-1);
+  buf[sizeof(buf)-1] = 0;
+
+  if (mkdirhier(dirname(buf)) == -1)
     return -1;
 
 #ifdef DEBUG