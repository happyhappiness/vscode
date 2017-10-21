 {
   struct stat st;
 
   if (stat(name,&st) == 0) {
     if (S_ISDIR(st.st_mode)) {
       if (chdir(name) != 0) {
-	fprintf(FERROR,"chdir %s : %s\n",name,strerror(errno));
+	fprintf(FERROR,"chdir %s : %s (1)\n",name,strerror(errno));
 	exit_cleanup(1);
       }
       return NULL;
     }
     if (flist->count > 1) {
       fprintf(FERROR,"ERROR: destination must be a directory when copying more than 1 file\n");
