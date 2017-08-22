@@ -343,6 +343,7 @@ static int	restore_entry(struct archive_write_disk *);
 static int	set_mac_metadata(struct archive_write_disk *, const char *,
 				 const void *, size_t);
 static int	set_xattrs(struct archive_write_disk *);
+static int	clear_nochange_fflags(struct archive_write_disk *);
 static int	set_fflags(struct archive_write_disk *);
 static int	set_fflags_platform(struct archive_write_disk *, int fd,
 		    const char *name, mode_t mode,
@@ -1467,10 +1468,14 @@ _archive_write_disk_data_block(struct archive *_a,
 		return (r);
 	if ((size_t)r < size) {
 		archive_set_error(&a->archive, 0,
-		    "Write request too large");
+		    "Too much data: Truncating file at %ju bytes", (uintmax_t)a->filesize);
 		return (ARCHIVE_WARN);
 	}
+#if ARCHIVE_VERSION_NUMBER < 3999000
 	return (ARCHIVE_OK);
+#else
+	return (size);
+#endif
 }
 
 static ssize_t
@@ -1842,6 +1847,8 @@ restore_entry(struct archive_write_disk *a)
 		 * object is a dir, but that doesn't mean the old
 		 * object isn't a dir.
 		 */
+		if (a->flags & ARCHIVE_EXTRACT_CLEAR_NOCHANGE_FFLAGS)
+			(void)clear_nochange_fflags(a);
 		if (unlink(a->name) == 0) {
 			/* We removed it, reset cached stat. */
 			a->pst = NULL;
@@ -1869,6 +1876,13 @@ restore_entry(struct archive_write_disk *a)
 		en = create_filesystem_object(a);
 	}
 
+	if ((en == ENOENT) && (archive_entry_hardlink(a->entry) != NULL)) {
+		archive_set_error(&a->archive, en,
+		    "Hard-link target '%s' does not exist.",
+		    archive_entry_hardlink(a->entry));
+		return (ARCHIVE_FAILED);
+	}
+
 	if ((en == EISDIR || en == EEXIST)
 	    && (a->flags & ARCHIVE_EXTRACT_NO_OVERWRITE)) {
 		/* If we're not overwriting, we're done. */
@@ -1940,6 +1954,8 @@ restore_entry(struct archive_write_disk *a)
 
 		if (!S_ISDIR(a->st.st_mode)) {
 			/* A non-dir is in the way, unlink it. */
+			if (a->flags & ARCHIVE_EXTRACT_CLEAR_NOCHANGE_FFLAGS)
+				(void)clear_nochange_fflags(a);
 			if (unlink(a->name) != 0) {
 				archive_set_error(&a->archive, errno,
 				    "Can't unlink already-existing object");
@@ -1950,6 +1966,8 @@ restore_entry(struct archive_write_disk *a)
 			en = create_filesystem_object(a);
 		} else if (!S_ISDIR(a->mode)) {
 			/* A dir is in the way of a non-dir, rmdir it. */
+			if (a->flags & ARCHIVE_EXTRACT_CLEAR_NOCHANGE_FFLAGS)
+				(void)clear_nochange_fflags(a);
 			if (rmdir(a->name) != 0) {
 				archive_set_error(&a->archive, errno,
 				    "Can't replace existing directory with non-directory");
@@ -2505,8 +2523,9 @@ cleanup_pathname_win(struct archive_write_disk *a)
 /*
  * Canonicalize the pathname.  In particular, this strips duplicate
  * '/' characters, '.' elements, and trailing '/'.  It also raises an
- * error for an empty path, a trailing '..' or (if _SECURE_NODOTDOT is
- * set) any '..' in the path.
+ * error for an empty path, a trailing '..', (if _SECURE_NODOTDOT is
+ * set) any '..' in the path or (if ARCHIVE_EXTRACT_SECURE_NOABSOLUTEPATHS
+ * is set) if the path is absolute.
  */
 static int
 cleanup_pathname(struct archive_write_disk *a)
@@ -2525,8 +2544,15 @@ cleanup_pathname(struct archive_write_disk *a)
 	cleanup_pathname_win(a);
 #endif
 	/* Skip leading '/'. */
-	if (*src == '/')
+	if (*src == '/') {
+		if (a->flags & ARCHIVE_EXTRACT_SECURE_NOABSOLUTEPATHS) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			                  "Path is absolute");
+			return (ARCHIVE_FAILED);
+		}
+
 		separator = *src++;
+	}
 
 	/* Scan the pathname one element at a time. */
 	for (;;) {
@@ -2862,27 +2888,29 @@ set_time(int fd, int mode, const char *name,
 #endif
 }
 
-#ifdef F_SETTIMES /* Tru64 */
+#ifdef F_SETTIMES
 static int
 set_time_tru64(int fd, int mode, const char *name,
     time_t atime, long atime_nsec,
     time_t mtime, long mtime_nsec,
     time_t ctime, long ctime_nsec)
 {
 	struct attr_timbuf tstamp;
-	struct timeval times[3];
-	times[0].tv_sec = atime;
-	times[0].tv_usec = atime_nsec / 1000;
-	times[1].tv_sec = mtime;
-	times[1].tv_usec = mtime_nsec / 1000;
-	times[2].tv_sec = ctime;
-	times[2].tv_usec = ctime_nsec / 1000;
-	tstamp.atime = times[0];
-	tstamp.mtime = times[1];
-	tstamp.ctime = times[2];
+	tstamp.atime.tv_sec = atime;
+	tstamp.mtime.tv_sec = mtime;
+	tstamp.ctime.tv_sec = ctime;
+#if defined (__hpux) && defined (__ia64)
+	tstamp.atime.tv_nsec = atime_nsec;
+	tstamp.mtime.tv_nsec = mtime_nsec;
+	tstamp.ctime.tv_nsec = ctime_nsec;
+#else
+	tstamp.atime.tv_usec = atime_nsec / 1000;
+	tstamp.mtime.tv_usec = mtime_nsec / 1000;
+	tstamp.ctime.tv_usec = ctime_nsec / 1000;
+#endif
 	return (fcntl(fd,F_SETTIMES,&tstamp));
 }
-#endif /* Tru64 */
+#endif /* F_SETTIMES */
 
 static int
 set_times(struct archive_write_disk *a,
@@ -3054,9 +3082,23 @@ set_mode(struct archive_write_disk *a, int mode)
 		 * impact.
 		 */
 		if (lchmod(a->name, mode) != 0) {
-			archive_set_error(&a->archive, errno,
-			    "Can't set permissions to 0%o", (int)mode);
-			r = ARCHIVE_WARN;
+			switch (errno) {
+			case ENOTSUP:
+			case ENOSYS:
+#if ENOTSUP != EOPNOTSUPP
+			case EOPNOTSUPP:
+#endif
+				/*
+				 * if lchmod is defined but the platform
+				 * doesn't support it, silently ignore
+				 * error
+				 */
+				break;
+			default:
+				archive_set_error(&a->archive, errno,
+				    "Can't set permissions to 0%o", (int)mode);
+				r = ARCHIVE_WARN;
+			}
 		}
 #endif
 	} else if (!S_ISDIR(a->mode)) {
@@ -3157,6 +3199,36 @@ set_fflags(struct archive_write_disk *a)
 	return (ARCHIVE_OK);
 }
 
+static int
+clear_nochange_fflags(struct archive_write_disk *a)
+{
+	int		nochange_flags;
+	mode_t		mode = archive_entry_mode(a->entry);
+
+	/* Hopefully, the compiler will optimize this mess into a constant. */
+	nochange_flags = 0;
+#ifdef SF_IMMUTABLE
+	nochange_flags |= SF_IMMUTABLE;
+#endif
+#ifdef UF_IMMUTABLE
+	nochange_flags |= UF_IMMUTABLE;
+#endif
+#ifdef SF_APPEND
+	nochange_flags |= SF_APPEND;
+#endif
+#ifdef UF_APPEND
+	nochange_flags |= UF_APPEND;
+#endif
+#ifdef EXT2_APPEND_FL
+	nochange_flags |= EXT2_APPEND_FL;
+#endif
+#ifdef EXT2_IMMUTABLE_FL
+	nochange_flags |= EXT2_IMMUTABLE_FL;
+#endif
+
+	return (set_fflags_platform(a, a->fd, a->name, mode, 0, nochange_flags));
+}
+
 
 #if ( defined(HAVE_LCHFLAGS) || defined(HAVE_CHFLAGS) || defined(HAVE_FCHFLAGS) ) && defined(HAVE_STRUCT_STAT_ST_FLAGS)
 /*
@@ -3364,6 +3436,7 @@ copy_xattrs(struct archive_write_disk *a, int tmpfd, int dffd)
 	}
 	for (xattr_i = 0; xattr_i < xattr_size;
 	    xattr_i += strlen(xattr_names + xattr_i) + 1) {
+		char *xattr_val_saved;
 		ssize_t s;
 		int f;
 
@@ -3374,11 +3447,13 @@ copy_xattrs(struct archive_write_disk *a, int tmpfd, int dffd)
 			ret = ARCHIVE_WARN;
 			goto exit_xattr;
 		}
+		xattr_val_saved = xattr_val;
 		xattr_val = realloc(xattr_val, s);
 		if (xattr_val == NULL) {
 			archive_set_error(&a->archive, ENOMEM,
 			    "Failed to get metadata(xattr)");
 			ret = ARCHIVE_WARN;
+			free(xattr_val_saved);
 			goto exit_xattr;
 		}
 		s = fgetxattr(tmpfd, xattr_names + xattr_i, xattr_val, s, 0, 0);