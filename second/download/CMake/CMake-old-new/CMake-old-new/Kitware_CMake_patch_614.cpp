@@ -69,8 +69,10 @@ tar_append_file(TAR *t, char *realname, char *savename)
   tar_ino_t *ti = NULL;
 #if !defined(_WIN32) || defined(__CYGWIN__)
   int i;
-  char path[TAR_MAXPATHLEN];
+#else
+  size_t plen;
 #endif
+  char path[TAR_MAXPATHLEN];
 
 #ifdef DEBUG
   printf("==> tar_append_file(TAR=0x%lx (\"%s\"), realname=\"%s\", "
@@ -79,7 +81,14 @@ tar_append_file(TAR *t, char *realname, char *savename)
 #endif
 
 #if defined(_WIN32) && !defined(__CYGWIN__)
-  if (stat(realname, &s) != 0)
+  strncpy(path, realname, sizeof(path)-1);
+  path[sizeof(path)-1] = 0;
+  plen = strlen(path);
+  if (path[plen-1] == '/' )
+    {
+    path[plen-1] = 0;
+    }
+  if (stat(path, &s) != 0)
 #else
   if (lstat(realname, &s) != 0)
 #endif
@@ -126,6 +135,7 @@ tar_append_file(TAR *t, char *realname, char *savename)
       return -1;
   }
   libtar_hashptr_reset(&hp);
+#if !defined(_WIN32) || defined(__CYGWIN__)
   if (libtar_hash_getkey(td->td_h, &hp, &(s.st_ino),
              (libtar_matchfunc_t)ino_match) != 0)
   {
@@ -138,6 +148,7 @@ tar_append_file(TAR *t, char *realname, char *savename)
     th_set_link(t, ti->ti_name);
   }
   else
+#endif
   {
 #ifdef DEBUG
     printf("+++ adding entry: device (0x%lx,0x%lx), inode %ld "