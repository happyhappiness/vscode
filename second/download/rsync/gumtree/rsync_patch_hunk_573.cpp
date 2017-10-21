 		rprintf(FINFO,"building file list ... ");
 		rflush(FINFO);
 	}
 
 	start_write = stats.total_written;
 
-	flist = (struct file_list *)malloc(sizeof(flist[0]));
-	if (!flist) out_of_memory("send_file_list");
-
-	flist->count=0;
-	flist->malloced = 1000;
-	flist->files = (struct file_struct **)malloc(sizeof(flist->files[0])*
-						     flist->malloced);
-	if (!flist->files) out_of_memory("send_file_list");
+	flist = flist_new();
 
 	if (f != -1) {
 		io_start_buffering(f);
 	}
 
 	for (i=0;i<argc;i++) {
