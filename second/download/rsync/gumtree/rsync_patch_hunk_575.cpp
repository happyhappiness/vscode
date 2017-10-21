 			return NULL;
 	}
 	
 	/* f is set to -1 when calculating deletion file list */
 	if (((f != -1) || !delete_excluded) && !match_file_name(fname,&st))
 		return NULL;
-	
+
+
+	if (lp_ignore_nonreadable(module_id) && access(fname, R_OK) != 0) 
+		return NULL;
+
+ skip_excludes:
+
 	if (verbose > 2)
 		rprintf(FINFO,"make_file(%d,%s)\n",f,fname);
 	
 	file = (struct file_struct *)malloc(sizeof(*file));
 	if (!file) out_of_memory("make_file");
 	memset((char *)file,0,sizeof(*file));
