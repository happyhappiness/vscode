 {
   struct stat st;
 
   if (stat(name,&st) == 0) {
     if (S_ISDIR(st.st_mode)) {
       if (chdir(name) != 0) {
-	fprintf(stderr,"chdir %s : %s\n",name,strerror(errno));
+	fprintf(FERROR,"chdir %s : %s\n",name,strerror(errno));
 	exit_cleanup(1);
       }
       return NULL;
     }
     if (flist->count > 1) {
-      fprintf(stderr,"ERROR: destination must be a directory when copying more than 1 file\n");
+      fprintf(FERROR,"ERROR: destination must be a directory when copying more than 1 file\n");
       exit_cleanup(1);
     }
     return name;
   }
 
   if (flist->count == 1)
     return name;
 
   if (!name) 
     return NULL;
 
   if (mkdir(name,0777) != 0) {
-    fprintf(stderr,"mkdir %s : %s\n",name,strerror(errno));
+    fprintf(FERROR,"mkdir %s : %s\n",name,strerror(errno));
     exit_cleanup(1);
   } else {
-    fprintf(am_server?stderr:stdout,"created directory %s\n",name);
+    fprintf(FINFO,"created directory %s\n",name);
   }
 
   if (chdir(name) != 0) {
-    fprintf(stderr,"chdir %s : %s\n",name,strerror(errno));
+    fprintf(FERROR,"chdir %s : %s\n",name,strerror(errno));
     exit_cleanup(1);
   }
 
   return NULL;
 }
 
