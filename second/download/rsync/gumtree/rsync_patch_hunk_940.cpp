 	if (verbose >= 5 && !set_path_only)
 		rprintf(FINFO, "[%s] change_dir(%s)\n", who_am_i(), curr_dir);
 
 	return 1;
 }
 
+/* This will make a relative path absolute and clean it up via clean_fname().
+ * Returns the string, which might be newly allocated, or NULL on error. */
+char *normalize_path(char *path, BOOL force_newbuf, unsigned int *len_ptr)
+{
+	unsigned int len;
+
+	if (*path != '/') { /* Make path absolute. */
+		int len = strlen(path);
+		if (curr_dir_len + 1 + len >= sizeof curr_dir)
+			return NULL;
+		curr_dir[curr_dir_len] = '/';
+		memcpy(curr_dir + curr_dir_len + 1, path, len + 1);
+		if (!(path = strdup(curr_dir)))
+			out_of_memory("normalize_path");
+		curr_dir[curr_dir_len] = '\0';
+	} else if (force_newbuf) {
+		if (!(path = strdup(path)))
+			out_of_memory("normalize_path");
+	}
+
+	len = clean_fname(path, CFN_COLLAPSE_DOT_DOT_DIRS | CFN_DROP_TRAILING_DOT_DIR);
+
+	if (len_ptr)
+		*len_ptr = len;
+
+	return path;
+}
+
 /**
  * Return a quoted string with the full pathname of the indicated filename.
  * The string " (in MODNAME)" may also be appended.  The returned pointer
  * remains valid until the next time full_fname() is called.
  **/
 char *full_fname(const char *fn)
