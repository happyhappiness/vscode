     return;
   }
 #endif
 
   if (preserve_hard_links && check_hard_link(file)) {
     if (verbose > 1)
-      fprintf(FINFO,"%s is a hard link\n",file->name);
+      fprintf(FINFO,"%s is a hard link\n",f_name(file));
     return;
   }
 
   if (!S_ISREG(file->mode)) {
-    fprintf(FERROR,"skipping non-regular file %s\n",fname);
+    fprintf(FINFO,"skipping non-regular file %s\n",fname);
     return;
   }
 
   if (statret == -1) {
     if (errno == ENOENT) {
       write_int(f_out,i);
