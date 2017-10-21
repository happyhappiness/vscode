 }
 
 
 int recv_files(int f_in,struct file_list *flist,char *local_name,int f_gen)
 {  
   int fd1,fd2;
-  struct stat st;
+  STRUCT_STAT st;
   char *fname;
   char fnametmp[MAXPATHLEN];
   struct map_struct *buf;
   int i;
   struct file_struct *file;
   int phase=0;
   int recv_ok;
 
   if (verbose > 2) {
-    fprintf(FINFO,"recv_files(%d) starting\n",flist->count);
+    rprintf(FINFO,"recv_files(%d) starting\n",flist->count);
   }
 
   if (recurse && delete_mode && !local_name && flist->count>0) {
     delete_files(flist);
   }
 
