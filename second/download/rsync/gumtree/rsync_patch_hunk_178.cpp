 
 void generate_files(int f,struct file_list *flist,char *local_name)
 {
   int i;
 
   if (verbose > 2)
-    fprintf(stderr,"generator starting pid=%d count=%d\n",
+    fprintf(FERROR,"generator starting pid=%d count=%d\n",
 	    (int)getpid(),flist->count);
 
   for (i = 0; i < flist->count; i++) {
-    if (!flist->files[i].name) continue;
-    if (S_ISDIR(flist->files[i].mode)) {
+    struct file_struct *file = &flist->files[i];
+    if (!file->name) continue;
+    if (S_ISDIR(file->mode)) {
       if (dry_run) continue;
-      if (mkdir(flist->files[i].name,flist->files[i].mode) != 0 &&
+      if (mkdir(file->name,file->mode) != 0 &&
 	  errno != EEXIST) {
-	fprintf(stderr,"mkdir %s : %s\n",
-		flist->files[i].name,strerror(errno));
+	fprintf(FERROR,"mkdir %s : %s\n",
+		file->name,strerror(errno));
       }
       continue;
     }
-    recv_generator(local_name?local_name:flist->files[i].name,
+    recv_generator(local_name?local_name:file->name,
 		   flist,i,f);
   }
   write_int(f,-1);
   write_flush(f);
   if (verbose > 2)
-    fprintf(stderr,"generator wrote %d\n",write_total());
+    fprintf(FERROR,"generator wrote %d\n",write_total());
 }
+
+
