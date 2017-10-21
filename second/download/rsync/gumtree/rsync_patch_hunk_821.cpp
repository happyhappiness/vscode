 
 	if (dir)
 		free(dir);
 
 	return ret;
 
-oom:
+  oom:
 	out_of_memory("do_cmd");
 	return 0; /* not reached */
 }
 
-
-static char *get_local_name(struct file_list *flist,char *name)
+/* The receiving side operates in one of two modes:
+ *
+ * 1. it receives any number of files into a destination directory,
+ * placing them according to their names in the file-list.
+ *
+ * 2. it receives a single file and saves it using the name in the
+ * destination path instead of its file-list name.  This requires a
+ * "local name" for writing out the destination file.
+ *
+ * So, our task is to figure out what mode/local-name we need and return
+ * either a NULL for mode 1, or the local-name for mode 2.  We also
+ * change directory if there are any path components in dest_path. */
+static char *get_local_name(struct file_list *flist, char *dest_path)
 {
 	STRUCT_STAT st;
-	int e;
+	char *cp;
 
-	if (verbose > 2)
-		rprintf(FINFO,"get_local_name count=%d %s\n",
-			flist->count, NS(name));
+	if (verbose > 2) {
+		rprintf(FINFO, "get_local_name count=%d %s\n",
+			flist->count, NS(dest_path));
+	}
 
-	if (!name)
+	if (!dest_path || list_only)
 		return NULL;
 
-	if (do_stat(name,&st) == 0) {
+	/* If the destination path refers to an existing directory, enter
+	 * it and use mode 1.  If there is something other than a directory
+	 * at the destination path, we must be transferring one file
+	 * (anything at the destination will be overwritten). */
+	if (do_stat(dest_path, &st) == 0) {
 		if (S_ISDIR(st.st_mode)) {
-			if (!push_dir(name)) {
+			if (!push_dir(dest_path)) {
 				rsyserr(FERROR, errno, "push_dir#1 %s failed",
-					full_fname(name));
+					full_fname(dest_path));
 				exit_cleanup(RERR_FILESELECT);
 			}
 			return NULL;
 		}
 		if (flist->count > 1) {
-			rprintf(FERROR,"ERROR: destination must be a directory when copying more than 1 file\n");
+			rprintf(FERROR,
+				"ERROR: destination must be a directory when"
+				" copying more than 1 file\n");
 			exit_cleanup(RERR_FILESELECT);
 		}
-		return name;
+		/* Caution: flist->count could be 0! */
+		if (flist->count == 1 && S_ISDIR(flist->files[0]->mode)) {
+			rprintf(FERROR,
+				"ERROR: cannot overwrite non-directory"
+				" with a directory\n");
+			exit_cleanup(RERR_FILESELECT);
+		}
+	} else if (errno != ENOENT) {
+		rsyserr(FERROR, errno, "cannot stat destination %s",
+			full_fname(dest_path));
+		exit_cleanup(RERR_FILESELECT);
 	}
 
-	if (flist->count <= 1 && ((e = strlen(name)) <= 1 || name[e-1] != '/'))
-		return name;
+	cp = strrchr(dest_path, '/');
 
-	if (do_mkdir(name,0777 & ~orig_umask) != 0) {
-		rsyserr(FERROR, errno, "mkdir %s failed", full_fname(name));
-		exit_cleanup(RERR_FILEIO);
-	}
-	if (verbose > 0)
-		rprintf(FINFO, "created directory %s\n", safe_fname(name));
+	/* If the destination path ends in a slash or we are transferring
+	 * multiple files, create a directory at the destination path,
+	 * enter the new directory, and use mode 1. */
+	if (flist->count > 1 || (cp && !cp[1])) {
+		/* Lop off the final slash (if any). */
+		if (cp && !cp[1])
+			*cp = '\0';
+
+		if (mkdir_defmode(dest_path) != 0) {
+			rsyserr(FERROR, errno, "mkdir %s failed",
+				full_fname(dest_path));
+			exit_cleanup(RERR_FILEIO);
+		}
+
+		if (verbose)
+			rprintf(FINFO, "created directory %s\n", dest_path);
+
+		if (dry_run) {
+			/* Indicate that the destination directory doesn't
+			 * really exist and return mode 1. */
+			dry_run++;
+			return NULL;
+		}
+
+		if (!push_dir(dest_path)) {
+			rsyserr(FERROR, errno, "push_dir#2 %s failed",
+				full_fname(dest_path));
+			exit_cleanup(RERR_FILESELECT);
+		}
 
-	if (dry_run) {
-		dry_run++;
 		return NULL;
 	}
 
-	if (!push_dir(name)) {
-		rsyserr(FERROR, errno, "push_dir#2 %s failed",
-			full_fname(name));
+	/* Otherwise, we are writing a single file, possibly on top of an
+	 * existing non-directory.  Change to the item's parent directory
+	 * (if it has a path component), return the basename of the
+	 * destination file as the local name, and use mode 2. */
+	if (!cp)
+		return dest_path;
+
+	if (cp == dest_path)
+		dest_path = "/";
+
+	*cp = '\0';
+	if (!push_dir(dest_path)) {
+		rsyserr(FERROR, errno, "push_dir#3 %s failed",
+			full_fname(dest_path));
 		exit_cleanup(RERR_FILESELECT);
 	}
+	*cp = '/';
 
-	return NULL;
+	return cp + 1;
 }
 
 
 /* This is only called by the sender. */
 static void read_final_goodbye(int f_in, int f_out)
 {
