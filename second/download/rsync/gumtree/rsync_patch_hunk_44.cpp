   int i,l;
   struct stat st;
   char *p,*dir;
   char dbuf[MAXPATHLEN];
   struct file_list *flist;
 
+  if (verbose && recurse)
+    fprintf(am_server?stderr:stdout,"building file list ... ");
+
   flist = (struct file_list *)malloc(sizeof(flist[0]));
   if (!flist) out_of_memory("send_file_list");
 
   flist->count=0;
-  flist_malloced = 100;
+  flist->malloced = 100;
   flist->files = (struct file_struct *)malloc(sizeof(flist->files[0])*
-					      flist_malloced);
+					      flist->malloced);
   if (!flist->files) out_of_memory("send_file_list");
 
   for (i=0;i<argc;i++) {
     char fname2[MAXPATHLEN];
     char *fname = fname2;
 
