   if (verbose > 2)
     fprintf(FERROR,"generator starting pid=%d count=%d\n",
 	    (int)getpid(),flist->count);
 
   for (i = 0; i < flist->count; i++) {
     struct file_struct *file = &flist->files[i];
+    mode_t saved_mode = file->mode;
     if (!file->name) continue;
-    if (S_ISDIR(file->mode)) {
-      if (dry_run) continue;
-      if (mkdir(file->name,file->mode) != 0 &&
-	  errno != EEXIST) {
-	fprintf(FERROR,"mkdir %s : %s\n",
-		file->name,strerror(errno));
-      }
-      continue;
+
+    /* we need to ensure that any directories we create have writeable
+       permissions initially so that we can create the files within
+       them. This is then fixed after the files are transferred */
+    if (!am_root && S_ISDIR(file->mode)) {
+      file->mode |= S_IWUSR; /* user write */
     }
+
     recv_generator(local_name?local_name:file->name,
 		   flist,i,f);
+
+    file->mode = saved_mode;
   }
 
   phase++;
   csum_length = SUM_LENGTH;
   ignore_times=1;
 
