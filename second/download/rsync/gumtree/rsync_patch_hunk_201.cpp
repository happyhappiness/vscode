 
   return total;
 }
 
 
 
-void generate_files(int f,struct file_list *flist,char *local_name)
+void generate_files(int f,struct file_list *flist,char *local_name,int f_recv)
 {
   int i;
+  int phase=0;
 
   if (verbose > 2)
     fprintf(FERROR,"generator starting pid=%d count=%d\n",
 	    (int)getpid(),flist->count);
 
   for (i = 0; i < flist->count; i++) {
