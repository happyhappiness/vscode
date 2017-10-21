   int i,l;
   struct stat st;
   char *p,*dir;
   char dbuf[MAXPATHLEN];
   struct file_list *flist;
 
-  if (verbose && recurse && !am_server) {
+  if (verbose && recurse && !am_server && f != -1) {
     fprintf(FINFO,"building file list ... ");
     fflush(FINFO);
   }
 
   flist = (struct file_list *)malloc(sizeof(flist[0]));
   if (!flist) out_of_memory("send_file_list");
