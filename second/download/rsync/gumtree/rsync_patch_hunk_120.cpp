 
   if (verbose > 2)
     fprintf(stderr,"server_sender starting pid=%d\n",(int)getpid());
   
   if (chdir(dir) != 0) {
     fprintf(stderr,"chdir %s: %s\n",dir,strerror(errno));
-    exit(1);
+    exit_cleanup(1);
   }
   argc--;
   argv++;
   
   if (strcmp(dir,".")) {
     int l = strlen(dir);
