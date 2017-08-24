@@ -607,7 +607,7 @@ tar_extract_chardev(TAR *t, char *realname)
   printf("  ==> extracting: %s (character device %ld,%ld)\n",
          filename, devmaj, devmin);
 #endif
-#ifndef WIN32
+#if !defined(WIN32) && !defined(__VMS)
   if (mknod(filename, mode | S_IFCHR,
       compat_makedev(devmaj, devmin)) == -1)
 #else
@@ -683,7 +683,7 @@ tar_extract_blockdev(TAR *t, char *realname)
   printf("  ==> extracting: %s (block device %ld,%ld)\n",
          filename, devmaj, devmin);
 #endif
-#ifndef WIN32
+#if !defined(WIN32) && !defined(__VMS)
   if (mknod(filename, mode | S_IFBLK,
       compat_makedev(devmaj, devmin)) == -1)
 #else
@@ -871,7 +871,7 @@ tar_extract_fifo(TAR *t, char *realname)
 #ifdef DEBUG
   printf("  ==> extracting: %s (fifo)\n", filename);
 #endif
-#ifndef WIN32
+#if !defined(WIN32) && !defined(__VMS)
   if (mkfifo(filename, mode & 07777) == -1)
 #else
     (void)mode;