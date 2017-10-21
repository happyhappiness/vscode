 {
   char **list=list1;
   FILE *f = fopen(fname,"r");
   char line[MAXPATHLEN];
   if (!f) {
     if (fatal) {
-      fprintf(FERROR,"%s : %s\n",fname,strerror(errno));
+      rprintf(FERROR,"%s : %s\n",fname,strerror(errno));
       exit_cleanup(1);
     }
     return list;
   }
 
   while (fgets(line,MAXPATHLEN,f)) {
