   char fname[MAXPATHLEN];
   int l;
   char *p;
 
   d = opendir(dir);
   if (!d) {
-    fprintf(stderr,"%s: %s\n",
+    fprintf(FERROR,"%s: %s\n",
 	    dir,strerror(errno));
     return;
   }
 
   strcpy(fname,dir);
   l = strlen(fname);
