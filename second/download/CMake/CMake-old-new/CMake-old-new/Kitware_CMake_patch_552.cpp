@@ -61,8 +61,18 @@ tar_set_file_perms(TAR *t, char *realname)
   gid_t gid;
   struct utimbuf ut;
   char *filename;
+  char *pathname = 0;
+
+  if (realname)
+    {
+    filename = realname;
+    }
+  else
+    {
+    pathname = th_get_pathname(t);
+    filename = pathname;
+    }
 
-  filename = (realname ? realname : th_get_pathname(t));
   mode = th_get_mode(t);
   uid = th_get_uid(t);
   gid = th_get_gid(t);
@@ -86,6 +96,10 @@ tar_set_file_perms(TAR *t, char *realname)
         filename, uid, gid, strerror(errno));
 # endif
 #endif /* HAVE_LCHOWN */
+    if (pathname)
+      {
+      free(pathname);
+      }
       return -1;
     }
 
@@ -95,6 +109,10 @@ tar_set_file_perms(TAR *t, char *realname)
 #ifdef DEBUG
     perror("utime()");
 #endif
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
   }
   /* change permissions */
@@ -103,6 +121,10 @@ tar_set_file_perms(TAR *t, char *realname)
 #ifdef DEBUG
     perror("chmod()");
 #endif
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
   }
 
@@ -113,6 +135,10 @@ tar_set_file_perms(TAR *t, char *realname)
   (void)mode;
 #endif /* WIN32 */
 
+  if (pathname)
+    {
+    free(pathname);
+    }
   return 0;
 }
 
@@ -123,6 +149,7 @@ tar_extract_file(TAR *t, char *realname)
 {
   int i;
   linkname_t *lnp;
+  char *pathname = 0;
 
   if (t->options & TAR_NOOVERWRITE)
   {
@@ -170,12 +197,17 @@ tar_extract_file(TAR *t, char *realname)
   lnp = (linkname_t *)calloc(1, sizeof(linkname_t));
   if (lnp == NULL)
     return -1;
-  strlcpy(lnp->ln_save, th_get_pathname(t), sizeof(lnp->ln_save));
+  pathname = th_get_pathname(t);
+  strlcpy(lnp->ln_save, pathname, sizeof(lnp->ln_save));
   strlcpy(lnp->ln_real, realname, sizeof(lnp->ln_real));
 #ifdef DEBUG
   printf("tar_extract_file(): calling libtar_hash_add(): key=\"%s\", "
-         "value=\"%s\"\n", th_get_pathname(t), realname);
+         "value=\"%s\"\n", pathname, realname);
 #endif
+  if (pathname)
+    {
+    free(pathname);
+    }
   if (libtar_hash_add(t->h, lnp) != 0)
     return -1;
 
@@ -195,6 +227,7 @@ tar_extract_regfile(TAR *t, char *realname)
   int i, k;
   char buf[T_BLOCKSIZE];
   char *filename;
+  char *pathname = 0;
 
 #ifdef DEBUG
   printf("==> tar_extract_regfile(t=0x%lx, realname=\"%s\")\n", t,
@@ -207,7 +240,15 @@ tar_extract_regfile(TAR *t, char *realname)
     return -1;
   }
 
-  filename = (realname ? realname : th_get_pathname(t));
+  if (realname)
+    {
+    filename = realname;
+    }
+  else
+    {
+    pathname = th_get_pathname(t);
+    filename = pathname;
+    }
   mode = th_get_mode(t);
   size = th_get_size(t);
   uid = th_get_uid(t);
@@ -220,6 +261,10 @@ tar_extract_regfile(TAR *t, char *realname)
 
   if (mkdirhier(dirname(buf)) == -1)
     {
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
     }
 
@@ -237,6 +282,10 @@ tar_extract_regfile(TAR *t, char *realname)
 #ifdef DEBUG
     perror("open()");
 #endif
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
   }
 
@@ -247,6 +296,10 @@ tar_extract_regfile(TAR *t, char *realname)
 #ifdef DEBUG
     perror("fchown()");
 #endif
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
   }
 
@@ -256,6 +309,10 @@ tar_extract_regfile(TAR *t, char *realname)
 #ifdef DEBUG
     perror("fchmod()");
 #endif
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
   }
 #endif
@@ -268,18 +325,34 @@ tar_extract_regfile(TAR *t, char *realname)
     {
       if (k != -1)
         errno = EINVAL;
+      if (pathname)
+        {
+        free(pathname);
+        }
       return -1;
     }
 
     /* write block to output file */
     if (write(fdout, buf,
         ((i > T_BLOCKSIZE) ? T_BLOCKSIZE : i)) == -1)
+      {
+      if (pathname)
+        {
+        free(pathname);
+        }
       return -1;
+      }
   }
 
   /* close output file */
   if (close(fdout) == -1)
+    {
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
+    }
 
 #ifdef DEBUG
   printf("### done extracting %s\n", filename);
@@ -290,6 +363,10 @@ tar_extract_regfile(TAR *t, char *realname)
   (void)uid;
   (void)mode;
 
+  if (pathname)
+    {
+    free(pathname);
+    }
   return 0;
 }
 
@@ -333,22 +410,37 @@ tar_extract_hardlink(TAR * t, char *realname)
   linkname_t *lnp;
   libtar_hashptr_t hp;
   char buf[T_BLOCKSIZE];
+  char *pathname = 0;
 
   if (!TH_ISLNK(t))
   {
     errno = EINVAL;
     return -1;
   }
 
-  filename = (realname ? realname : th_get_pathname(t));
+  if (realname)
+    {
+    filename = realname;
+    }
+  else
+    {
+    pathname = th_get_pathname(t);
+    filename = pathname;
+    }
 
   /* Make a copy of the string because dirname and mkdirhier may modify the
    * string */
   strncpy(buf, filename, sizeof(buf)-1);
   buf[sizeof(buf)-1] = 0;
 
   if (mkdirhier(dirname(buf)) == -1)
+    {
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
+    }
   libtar_hashptr_reset(&hp);
   if (libtar_hash_getkey(t->h, &hp, th_get_linkname(t),
              (libtar_matchfunc_t)libtar_str_match) != 0)
@@ -371,9 +463,17 @@ tar_extract_hardlink(TAR * t, char *realname)
 #ifdef DEBUG
     perror("link()");
 #endif
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
   }
 
+  if (pathname)
+    {
+    free(pathname);
+    }
   return 0;
 }
 
@@ -384,6 +484,7 @@ tar_extract_symlink(TAR *t, char *realname)
 {
   char *filename;
   char buf[T_BLOCKSIZE];
+  char *pathname = 0;
 
 #ifndef _WIN32
   if (!TH_ISSYM(t))
@@ -393,18 +494,36 @@ tar_extract_symlink(TAR *t, char *realname)
   }
 #endif
 
-  filename = (realname ? realname : th_get_pathname(t));
+  if (realname)
+    {
+    filename = realname;
+    }
+  else
+    {
+    pathname = th_get_pathname(t);
+    filename = pathname;
+    }
 
   /* Make a copy of the string because dirname and mkdirhier may modify the
    * string */
   strncpy(buf, filename, sizeof(buf)-1);
   buf[sizeof(buf)-1] = 0;
 
   if (mkdirhier(dirname(buf)) == -1)
+    {
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
+    }
 
   if (unlink(filename) == -1 && errno != ENOENT)
     {
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
     }
 
@@ -419,9 +538,17 @@ tar_extract_symlink(TAR *t, char *realname)
 #ifdef DEBUG
     perror("symlink()");
 #endif
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
   }
 
+  if (pathname)
+    {
+    free(pathname);
+    }
   return 0;
 }
 
@@ -434,6 +561,7 @@ tar_extract_chardev(TAR *t, char *realname)
   unsigned long devmaj, devmin;
   char *filename;
   char buf[T_BLOCKSIZE];
+  char *pathname = 0;
 
 #ifndef _WIN32
   if (!TH_ISCHR(t))
@@ -442,7 +570,15 @@ tar_extract_chardev(TAR *t, char *realname)
     return -1;
   }
 #endif
-  filename = (realname ? realname : th_get_pathname(t));
+  if (realname)
+    {
+    filename = realname;
+    }
+  else
+    {
+    pathname = th_get_pathname(t);
+    filename = pathname;
+    }
   mode = th_get_mode(t);
   devmaj = th_get_devmajor(t);
   devmin = th_get_devminor(t);
@@ -453,7 +589,13 @@ tar_extract_chardev(TAR *t, char *realname)
   buf[sizeof(buf)-1] = 0;
 
   if (mkdirhier(dirname(buf)) == -1)
+    {
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
+    }
 
 #ifdef DEBUG
   printf("  ==> extracting: %s (character device %ld,%ld)\n",
@@ -471,9 +613,17 @@ tar_extract_chardev(TAR *t, char *realname)
 #ifdef DEBUG
     perror("mknod()");
 #endif
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
   }
 
+  if (pathname)
+    {
+    free(pathname);
+    }
   return 0;
 }
 
@@ -486,14 +636,23 @@ tar_extract_blockdev(TAR *t, char *realname)
   unsigned long devmaj, devmin;
   char *filename;
   char buf[T_BLOCKSIZE];
+  char *pathname = 0;
 
   if (!TH_ISBLK(t))
   {
     errno = EINVAL;
     return -1;
   }
 
-  filename = (realname ? realname : th_get_pathname(t));
+  if (realname)
+    {
+    filename = realname;
+    }
+  else
+    {
+    pathname = th_get_pathname(t);
+    filename = pathname;
+    }
   mode = th_get_mode(t);
   devmaj = th_get_devmajor(t);
   devmin = th_get_devminor(t);
@@ -504,7 +663,13 @@ tar_extract_blockdev(TAR *t, char *realname)
   buf[sizeof(buf)-1] = 0;
 
   if (mkdirhier(dirname(buf)) == -1)
+    {
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
+    }
 
 #ifdef DEBUG
   printf("  ==> extracting: %s (block device %ld,%ld)\n",
@@ -522,9 +687,17 @@ tar_extract_blockdev(TAR *t, char *realname)
 #ifdef DEBUG
     perror("mknod()");
 #endif
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
   }
 
+  if (pathname)
+    {
+    free(pathname);
+    }
   return 0;
 }
 
@@ -536,14 +709,23 @@ tar_extract_dir(TAR *t, char *realname)
   mode_t mode;
   char *filename;
   char buf[T_BLOCKSIZE];
+  char *pathname = 0;
 
   if (!TH_ISDIR(t))
   {
     errno = EINVAL;
     return -1;
   }
 
-  filename = (realname ? realname : th_get_pathname(t));
+  if (realname)
+    {
+    filename = realname;
+    }
+  else
+    {
+    pathname = th_get_pathname(t);
+    filename = pathname;
+    }
   mode = th_get_mode(t);
 
   /* Make a copy of the string because dirname and mkdirhier may modify the
@@ -552,7 +734,13 @@ tar_extract_dir(TAR *t, char *realname)
   buf[sizeof(buf)-1] = 0;
 
   if (mkdirhier(dirname(buf)) == -1)
+    {
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
+    }
 
 #ifdef DEBUG
   printf("  ==> extracting: %s (mode %04o, directory)\n", filename,
@@ -581,13 +769,21 @@ tar_extract_dir(TAR *t, char *realname)
 #ifdef DEBUG
         perror("chmod()");
 #endif
+        if (pathname)
+          {
+          free(pathname);
+          }
         return -1;
       }
       else
       {
 #ifdef DEBUG
         puts("  *** using existing directory");
 #endif
+        if (pathname)
+          {
+          free(pathname);
+          }
         return 1;
       }
     }
@@ -596,10 +792,18 @@ tar_extract_dir(TAR *t, char *realname)
 #ifdef DEBUG
       perror("mkdir()");
 #endif
+      if (pathname)
+        {
+        free(pathname);
+        }
       return -1;
     }
   }
 
+  if (pathname)
+    {
+    free(pathname);
+    }
   return 0;
 }
 
@@ -611,14 +815,23 @@ tar_extract_fifo(TAR *t, char *realname)
   mode_t mode;
   char *filename;
   char buf[T_BLOCKSIZE];
+  char *pathname = 0;
 
   if (!TH_ISFIFO(t))
   {
     errno = EINVAL;
     return -1;
   }
 
-  filename = (realname ? realname : th_get_pathname(t));
+  if (realname)
+    {
+    filename = realname;
+    }
+  else
+    {
+    pathname = th_get_pathname(t);
+    filename = pathname;
+    }
   mode = th_get_mode(t);
 
   /* Make a copy of the string because dirname and mkdirhier may modify the
@@ -627,7 +840,13 @@ tar_extract_fifo(TAR *t, char *realname)
   buf[sizeof(buf)-1] = 0;
 
   if (mkdirhier(dirname(buf)) == -1)
+    {
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
+    }
 
 #ifdef DEBUG
   printf("  ==> extracting: %s (fifo)\n", filename);
@@ -641,10 +860,16 @@ tar_extract_fifo(TAR *t, char *realname)
 #ifdef DEBUG
     perror("mkfifo()");
 #endif
+    if (pathname)
+      {
+      free(pathname);
+      }
     return -1;
   }
 
+  if (pathname)
+    {
+    free(pathname);
+    }
   return 0;
 }
-
-