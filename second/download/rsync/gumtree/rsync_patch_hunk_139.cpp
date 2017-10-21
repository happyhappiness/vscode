   from the list of files based on its name and type etc
  */
 static int match_file_name(char *fname,struct stat *st)
 {
   if (check_exclude(fname,local_exclude_list)) {
     if (verbose > 2)
-      fprintf(stderr,"excluding file %s\n",fname);
+      fprintf(FERROR,"excluding file %s\n",fname);
     return 0;
   }
   return 1;
 }
 
 /* used by the one_file_system code */
