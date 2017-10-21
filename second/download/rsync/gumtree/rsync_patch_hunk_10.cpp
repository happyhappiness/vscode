 	 always_checksum && memcmp(sum,flist->files[i].sum,SUM_LENGTH) == 0)))) {
     if (verbose > 1)
       fprintf(stderr,"%s is uptodate\n",fname);
     return;
   }
 
+  if (dry_run) {
+    write_int(f_out,i);
+    return;
+  }
+
   /* open the file */  
   fd = open(fname,O_RDONLY);
 
   if (fd == -1) {
     fprintf(stderr,"failed to open %s : %s\n",fname,strerror(errno));
     return;
