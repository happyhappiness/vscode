  * stat()ing the file in some circumstances, which has a certain cost.
  * We are called immediately after doing readdir(), and so we may
  * already know the d_type of the file.  We could for example avoid
  * statting directories if we're not recursing, but this is not a very
  * important case.  Some systems may not have d_type.
  **/
-struct file_struct *make_file(char *fname, struct string_area **ap,
-			      int exclude_level)
+struct file_struct *make_file(char *fname,
+    struct file_list *flist, int exclude_level)
 {
+	static char *lastdir;
+	static int lastdir_len = -1;
 	struct file_struct *file;
 	STRUCT_STAT st;
 	char sum[SUM_LENGTH];
-	char *p;
-	char cleaned_name[MAXPATHLEN];
-	char linkbuf[MAXPATHLEN];
-	extern int module_id;
-
-	strlcpy(cleaned_name, fname, MAXPATHLEN);
-	cleaned_name[MAXPATHLEN - 1] = 0;
-	clean_fname(cleaned_name);
-	if (sanitize_paths) {
-		sanitize_path(cleaned_name, NULL);
+	char thisname[MAXPATHLEN];
+	char linkname[MAXPATHLEN];
+	int alloc_len, basename_len, dirname_len, linkname_len, sum_len;
+	char *basename, *dirname, *bp;
+	unsigned short flags = 0;
+
+	if (!flist)	/* lastdir isn't valid if flist is NULL */
+		lastdir_len = -1;
+
+	if (strlcpy(thisname, fname, sizeof thisname)
+	    >= sizeof thisname - flist_dir_len) {
+		rprintf(FINFO, "skipping overly long name: %s\n", fname);
+		return NULL;
 	}
-	fname = cleaned_name;
+	clean_fname(thisname);
+	if (sanitize_paths)
+		sanitize_path(thisname, NULL);
 
 	memset(sum, 0, SUM_LENGTH);
 
-	if (readlink_stat(fname, &st, linkbuf) != 0) {
+	if (readlink_stat(thisname, &st, linkname) != 0) {
 		int save_errno = errno;
-		if (errno == ENOENT && exclude_level != NO_EXCLUDES) {
+		if (errno == ENOENT) {
+			enum logcode c = am_daemon && protocol_version < 28
+			    ? FERROR : FINFO;
 			/* either symlink pointing nowhere or file that
 			 * was removed during rsync run; see if excluded
 			 * before reporting an error */
-			if (check_exclude_file(fname, 0, exclude_level)) {
+			if (exclude_level != NO_EXCLUDES
+			    && check_exclude_file(thisname, 0, exclude_level)) {
 				/* file is excluded anyway, ignore silently */
 				return NULL;
 			}
+			io_error |= IOERR_VANISHED;
+			rprintf(c, "file has vanished: %s\n",
+			    full_fname(thisname));
+		}
+		else {
+			io_error |= IOERR_GENERAL;
+			rprintf(FERROR, "readlink %s failed: %s\n",
+			    full_fname(thisname), strerror(save_errno));
 		}
-		io_error |= IOERR_GENERAL;
-		rprintf(FERROR, "readlink %s failed: %s\n",
-			full_fname(fname), strerror(save_errno));
 		return NULL;
 	}
 
 	/* backup.c calls us with exclude_level set to NO_EXCLUDES. */
 	if (exclude_level == NO_EXCLUDES)
 		goto skip_excludes;
 
 	if (S_ISDIR(st.st_mode) && !recurse && !files_from) {
-		rprintf(FINFO, "skipping directory %s\n", fname);
+		rprintf(FINFO, "skipping directory %s\n", thisname);
 		return NULL;
 	}
 
-	if (one_file_system && st.st_dev != filesystem_dev) {
-		if (skip_filesystem(fname, &st))
-			return NULL;
-	}
+	/* We only care about directories because we need to avoid recursing
+	 * into a mount-point directory, not to avoid copying a symlinked
+	 * file if -L (or similar) was specified. */
+	if (one_file_system && st.st_dev != filesystem_dev
+	    && S_ISDIR(st.st_mode))
+		flags |= FLAG_MOUNT_POINT;
 
-	if (check_exclude_file(fname, S_ISDIR(st.st_mode) != 0, exclude_level))
+	if (check_exclude_file(thisname, S_ISDIR(st.st_mode) != 0, exclude_level))
 		return NULL;
 
-	if (lp_ignore_nonreadable(module_id) && access(fname, R_OK) != 0)
+	if (lp_ignore_nonreadable(module_id) && access(thisname, R_OK) != 0)
 		return NULL;
 
-      skip_excludes:
+skip_excludes:
 
-	if (verbose > 2)
-		rprintf(FINFO, "make_file(%s,*,%d)\n", fname, exclude_level);
+	if (verbose > 2) {
+		rprintf(FINFO, "[%s] make_file(%s,*,%d)\n",
+			who_am_i(), thisname, exclude_level);
+	}
 
-	file = new(struct file_struct);
-	if (!file)
-		out_of_memory("make_file");
-	memset((char *) file, 0, sizeof(*file));
+	if ((basename = strrchr(thisname, '/')) != NULL) {
+		dirname_len = ++basename - thisname; /* counts future '\0' */
+		if (lastdir_len == dirname_len - 1
+		    && strncmp(thisname, lastdir, lastdir_len) == 0) {
+			dirname = lastdir;
+			dirname_len = 0; /* indicates no copy is needed */
+		} else
+			dirname = thisname;
+	} else {
+		basename = thisname;
+		dirname = NULL;
+		dirname_len = 0;
+	}
+	basename_len = strlen(basename) + 1; /* count the '\0' */
 
-	if ((p = strrchr(fname, '/'))) {
-		static char *lastdir;
-		*p = 0;
-		if (lastdir && strcmp(fname, lastdir) == 0) {
-			file->dirname = lastdir;
-		} else {
-			file->dirname = strdup(fname);
-			lastdir = file->dirname;
-		}
-		file->basename = STRDUP(ap, p + 1);
-		*p = '/';
+#if SUPPORT_LINKS
+	linkname_len = S_ISLNK(st.st_mode) ? strlen(linkname) + 1 : 0;
+#else
+	linkname_len = 0;
+#endif
+
+	sum_len = always_checksum && S_ISREG(st.st_mode) ? MD4_SUM_LENGTH : 0;
+
+	alloc_len = file_struct_len + dirname_len + basename_len
+	    + linkname_len + sum_len;
+	if (flist) {
+		bp = pool_alloc(flist->file_pool, alloc_len,
+		    "receive_file_entry");
 	} else {
-		file->dirname = NULL;
-		file->basename = STRDUP(ap, fname);
+		if (!(bp = new_array(char, alloc_len)))
+			out_of_memory("receive_file_entry");
 	}
 
+	file = (struct file_struct *)bp;
+	memset(bp, 0, file_struct_len);
+	bp += file_struct_len;
+
+	file->flags = flags;
 	file->modtime = st.st_mtime;
 	file->length = st.st_size;
 	file->mode = st.st_mode;
 	file->uid = st.st_uid;
 	file->gid = st.st_gid;
-	file->dev = st.st_dev;
-	file->inode = st.st_ino;
+
+#if SUPPORT_HARD_LINKS
+	if (flist && flist->hlink_pool) {
+		if (protocol_version < 28) {
+			if (S_ISREG(st.st_mode))
+				file->link_u.idev = pool_talloc(
+				    flist->hlink_pool, struct idev, 1,
+				    "inode_table");
+		} else {
+			if (!S_ISDIR(st.st_mode) && st.st_nlink > 1)
+				file->link_u.idev = pool_talloc(
+				    flist->hlink_pool, struct idev, 1,
+				    "inode_table");
+		}
+	}
+	if (file->link_u.idev) {
+		file->F_DEV = st.st_dev;
+		file->F_INODE = st.st_ino;
+	}
+#endif
+
+	if (dirname_len) {
+		file->dirname = lastdir = bp;
+		lastdir_len = dirname_len - 1;
+		memcpy(bp, dirname, dirname_len - 1);
+		bp += dirname_len;
+		bp[-1] = '\0';
+	} else if (dirname)
+		file->dirname = dirname;
+
+	file->basename = bp;
+	memcpy(bp, basename, basename_len);
+	bp += basename_len;
+
 #ifdef HAVE_STRUCT_STAT_ST_RDEV
-	file->rdev = st.st_rdev;
+	if (preserve_devices && IS_DEVICE(st.st_mode))
+		file->u.rdev = st.st_rdev;
 #endif
 
 #if SUPPORT_LINKS
-	if (S_ISLNK(st.st_mode)) {
-		file->link = STRDUP(ap, linkbuf);
+	if (linkname_len) {
+		file->u.link = bp;
+		memcpy(bp, linkname, linkname_len);
+		bp += linkname_len;
 	}
 #endif
 
-	if (always_checksum) {
-		file->sum = (char *) MALLOC(ap, MD4_SUM_LENGTH);
-		if (!file->sum)
-			out_of_memory("md4 sum");
-		/* drat. we have to provide a null checksum for non-regular
-		   files in order to be compatible with earlier versions
-		   of rsync */
-		if (S_ISREG(st.st_mode)) {
-			file_checksum(fname, file->sum, st.st_size);
-		} else {
-			memset(file->sum, 0, MD4_SUM_LENGTH);
-		}
+	if (sum_len) {
+		file->u.sum = bp;
+		file_checksum(thisname, bp, st.st_size);
+		/*bp += sum_len;*/
 	}
 
-	if (flist_dir) {
-		static char *lastdir;
-		if (lastdir && strcmp(lastdir, flist_dir) == 0) {
-			file->basedir = lastdir;
-		} else {
-			file->basedir = strdup(flist_dir);
-			lastdir = file->basedir;
-		}
-	} else {
-		file->basedir = NULL;
-	}
+	file->basedir = flist_dir;
 
 	if (!S_ISDIR(st.st_mode))
 		stats.total_size += st.st_size;
 
 	return file;
 }
