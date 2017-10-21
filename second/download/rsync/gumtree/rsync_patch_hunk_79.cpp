 
   if (verbose > 2)
     fprintf(stderr,"send_files starting\n");
 
   while (1) 
     {
+      read_check(f_in);
+
       i = read_int(f_in);
       if (i == -1) break;
 
       fname[0] = 0;
       if (flist->files[i].dir) {
 	strcpy(fname,flist->files[i].dir);
