 	if (lp_ignore_nonreadable(module_id) && access(fname, R_OK) != 0)
 		return NULL;
 
       skip_excludes:
 
 	if (verbose > 2)
-		rprintf(FINFO, "make_file(%d,%s)\n", f, fname);
+		rprintf(FINFO, "make_file(%s,*,%d)\n", fname, exclude_level);
 
 	file = new(struct file_struct);
 	if (!file)
 		out_of_memory("make_file");
 	memset((char *) file, 0, sizeof(*file));
 
