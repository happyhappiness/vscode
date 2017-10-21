 	char *p;
 	char cleaned_name[MAXPATHLEN];
 	char linkbuf[MAXPATHLEN];
 	extern int module_id;
 
 	strlcpy(cleaned_name, fname, MAXPATHLEN);
-	cleaned_name[MAXPATHLEN-1] = 0;
+	cleaned_name[MAXPATHLEN - 1] = 0;
 	clean_fname(cleaned_name);
 	if (sanitize_paths) {
 		sanitize_path(cleaned_name, NULL);
 	}
 	fname = cleaned_name;
 
-	memset(sum,0,SUM_LENGTH);
+	memset(sum, 0, SUM_LENGTH);
 
-	if (readlink_stat(fname,&st,linkbuf) != 0) {
+	if (readlink_stat(fname, &st, linkbuf) != 0) {
 		int save_errno = errno;
 		if ((errno == ENOENT) && copy_links && !noexcludes) {
 			/* symlink pointing nowhere, see if excluded */
-			memset((char *)&st, 0, sizeof(st));
-			if (check_exclude_file(f,fname,&st)) {
+			memset((char *) &st, 0, sizeof(st));
+			if (check_exclude_file(f, fname, &st)) {
 				/* file is excluded anyway, ignore silently */
 				return NULL;
 			}
 		}
 		io_error = 1;
-		rprintf(FERROR,"readlink %s: %s\n",
-			fname,strerror(save_errno));
+		rprintf(FERROR, "readlink %s: %s\n",
+			fname, strerror(save_errno));
 		return NULL;
 	}
 
 	/* we use noexcludes from backup.c */
-	if (noexcludes) goto skip_excludes;
+	if (noexcludes)
+		goto skip_excludes;
 
 	if (S_ISDIR(st.st_mode) && !recurse) {
-		rprintf(FINFO,"skipping directory %s\n",fname);
+		rprintf(FINFO, "skipping directory %s\n", fname);
 		return NULL;
 	}
-	
+
 	if (one_file_system && st.st_dev != filesystem_dev) {
 		if (skip_filesystem(fname, &st))
 			return NULL;
 	}
-	
-	if (check_exclude_file(f,fname,&st))
+
+	if (check_exclude_file(f, fname, &st))
 		return NULL;
 
 
-	if (lp_ignore_nonreadable(module_id) && access(fname, R_OK) != 0) 
+	if (lp_ignore_nonreadable(module_id) && access(fname, R_OK) != 0)
 		return NULL;
 
- skip_excludes:
+      skip_excludes:
 
 	if (verbose > 2)
-		rprintf(FINFO,"make_file(%d,%s)\n",f,fname);
-	
-	file = (struct file_struct *)malloc(sizeof(*file));
-	if (!file) out_of_memory("make_file");
-	memset((char *)file,0,sizeof(*file));
+		rprintf(FINFO, "make_file(%d,%s)\n", f, fname);
+
+	file = (struct file_struct *) malloc(sizeof(*file));
+	if (!file)
+		out_of_memory("make_file");
+	memset((char *) file, 0, sizeof(*file));
 
-	if ((p = strrchr(fname,'/'))) {
+	if ((p = strrchr(fname, '/'))) {
 		static char *lastdir;
 		*p = 0;
-		if (lastdir && strcmp(fname, lastdir)==0) {
+		if (lastdir && strcmp(fname, lastdir) == 0) {
 			file->dirname = lastdir;
 		} else {
 			file->dirname = strdup(fname);
 			lastdir = file->dirname;
 		}
-		file->basename = STRDUP(ap, p+1);
+		file->basename = STRDUP(ap, p + 1);
 		*p = '/';
 	} else {
 		file->dirname = NULL;
 		file->basename = STRDUP(ap, fname);
 	}
 
