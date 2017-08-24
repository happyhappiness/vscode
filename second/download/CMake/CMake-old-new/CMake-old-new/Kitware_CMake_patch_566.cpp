@@ -64,11 +64,13 @@ int
 tar_append_file(TAR *t, char *realname, char *savename)
 {
   struct stat s;
-  int i;
   libtar_hashptr_t hp;
   tar_dev_t *td = NULL;
   tar_ino_t *ti = NULL;
+#if !defined(_WIN32) || defined(__CYGWIN__)
+  int i;
   char path[TAR_MAXPATHLEN];
+#endif
 
 #ifdef DEBUG
   printf("==> tar_append_file(TAR=0x%lx (\"%s\"), realname=\"%s\", "
@@ -151,7 +153,7 @@ tar_append_file(TAR *t, char *realname, char *savename)
     libtar_hash_add(td->td_h, ti);
   }
 
-#ifndef WIN32
+#if !defined(_WIN32) || defined(__CYGWIN__)
   /* check if it's a symlink */
   if (TH_ISSYM(t))
   {
@@ -172,6 +174,7 @@ tar_append_file(TAR *t, char *realname, char *savename)
     th_set_link(t, path);
   }
 #endif
+
   /* print file info */
   if (t->options & TAR_VERBOSE)
     th_print_long_ls(t);