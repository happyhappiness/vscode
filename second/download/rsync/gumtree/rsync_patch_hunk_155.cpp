 {
   int i;
   char *dir = argv[0];
   struct file_list *flist;
 
   if (verbose > 2)
-    fprintf(stderr,"server_sender starting pid=%d\n",(int)getpid());
+    fprintf(FERROR,"server_sender starting pid=%d\n",(int)getpid());
   
   if (chdir(dir) != 0) {
-    fprintf(stderr,"chdir %s: %s\n",dir,strerror(errno));
+    fprintf(FERROR,"chdir %s: %s\n",dir,strerror(errno));
     exit_cleanup(1);
   }
   argc--;
   argv++;
   
   if (strcmp(dir,".")) {
