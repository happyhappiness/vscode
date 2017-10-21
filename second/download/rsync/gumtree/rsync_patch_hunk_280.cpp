 
     l = strlen(fname);
     if (l != 1 && fname[l-1] == '/') {
       strcat(fname,".");
     }
 
-    if (lstat(fname,&st) != 0) {
+    if (link_stat(fname,&st) != 0) {
       fprintf(FERROR,"%s : %s\n",fname,strerror(errno));
       continue;
     }
 
     if (S_ISDIR(st.st_mode) && !recurse) {
       fprintf(FERROR,"skipping directory %s\n",fname);
