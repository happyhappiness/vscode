 void generate_files(int f,struct file_list *flist,char *local_name,int f_recv)
 {
   int i;
   int phase=0;
 
   if (verbose > 2)
-    fprintf(FINFO,"generator starting pid=%d count=%d\n",
+    rprintf(FINFO,"generator starting pid=%d count=%d\n",
 	    (int)getpid(),flist->count);
 
   for (i = 0; i < flist->count; i++) {
     struct file_struct *file = flist->files[i];
     mode_t saved_mode = file->mode;
     if (!file->basename) continue;
