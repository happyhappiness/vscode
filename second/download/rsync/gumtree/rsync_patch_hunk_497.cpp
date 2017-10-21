 	flist->count=0;
 	flist->malloced = 1000;
 	flist->files = (struct file_struct **)malloc(sizeof(flist->files[0])*
 						     flist->malloced);
 	if (!flist->files) out_of_memory("send_file_list");
 
+	if (f != -1) {
+		io_start_buffering(f);
+	}
+
 	for (i=0;i<argc;i++) {
 		char fname2[MAXPATHLEN];
 		char *fname = fname2;
 
 		strlcpy(fname,argv[i],MAXPATHLEN-1);
 
