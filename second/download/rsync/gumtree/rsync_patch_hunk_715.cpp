 oom:
 	out_of_memory("do_cmd");
 	return 0; /* not reached */
 }
 
 
-
-
 static char *get_local_name(struct file_list *flist,char *name)
 {
 	STRUCT_STAT st;
 	int e;
-	extern int orig_umask;
 
 	if (verbose > 2)
 		rprintf(FINFO,"get_local_name count=%d %s\n",
 			flist->count, NS(name));
 
 	if (!name)
 		return NULL;
 
 	if (do_stat(name,&st) == 0) {
 		if (S_ISDIR(st.st_mode)) {
-			if (!push_dir(name, 0)) {
+			if (!push_dir(name)) {
 				rprintf(FERROR, "push_dir %s failed: %s (1)\n",
 					full_fname(name), strerror(errno));
 				exit_cleanup(RERR_FILESELECT);
 			}
 			return NULL;
 		}
