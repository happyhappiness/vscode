 extern int copy_links;
 extern int remote_version;
 extern int io_error;
 
 static char **local_exclude_list;
 
-int link_stat(const char *Path, struct stat *Buffer) 
+int link_stat(const char *Path, STRUCT_STAT *Buffer) 
 {
 #if SUPPORT_LINKS
     if (copy_links) {
-	return stat(Path, Buffer);
+	return do_stat(Path, Buffer);
     } else {
-	return lstat(Path, Buffer);
+	return do_lstat(Path, Buffer);
     }
 #else
-    return stat(Path, Buffer);
+    return do_stat(Path, Buffer);
 #endif
 }
 
 /*
   This function is used to check if a file should be included/excluded
   from the list of files based on its name and type etc
  */
-static int match_file_name(char *fname,struct stat *st)
+static int match_file_name(char *fname,STRUCT_STAT *st)
 {
   if (check_exclude(fname,local_exclude_list)) {
     if (verbose > 2)
-      fprintf(FINFO,"excluding file %s\n",fname);
+      rprintf(FINFO,"excluding file %s\n",fname);
     return 0;
   }
   return 1;
 }
 
 /* used by the one_file_system code */
 static dev_t filesystem_dev;
 
 static void set_filesystem(char *fname)
 {
-  struct stat st;
+  STRUCT_STAT st;
   if (link_stat(fname,&st) != 0) return;
   filesystem_dev = st.st_dev;
 }
 
 
 static void send_directory(int f,struct file_list *flist,char *dir);
