 
   /* open the file */  
   fd = open(fname,O_RDONLY);
 
   if (fd == -1) {
     fprintf(FERROR,"failed to open %s : %s\n",fname,strerror(errno));
+    fprintf(FERROR,"skipping %s\n",fname);
     return;
   }
 
   if (st.st_size > 0) {
     buf = map_file(fd,st.st_size);
   } else {
