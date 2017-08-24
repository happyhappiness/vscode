@@ -717,6 +717,7 @@ _archive_read_data_block(struct archive *_a, const void **buff,
 	int r;
 	ssize_t bytes;
 	size_t buffbytes;
+	int empty_sparse_region = 0;
 
 	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC, ARCHIVE_STATE_DATA,
 	    "archive_read_data_block");
@@ -798,6 +799,9 @@ _archive_read_data_block(struct archive *_a, const void **buff,
 	if ((int64_t)buffbytes > t->current_sparse->length)
 		buffbytes = t->current_sparse->length;
 
+	if (t->current_sparse->length == 0)
+		empty_sparse_region = 1;
+
 	/*
 	 * Skip hole.
 	 * TODO: Should we consider t->current_filesystem->xfer_align?
@@ -828,7 +832,11 @@ _archive_read_data_block(struct archive *_a, const void **buff,
 		}
 	} else
 		bytes = 0;
-	if (bytes == 0) {
+	/*
+	 * Return an EOF unless we've read a leading empty sparse region, which
+	 * is used to represent fully-sparse files.
+	*/
+	if (bytes == 0 && !empty_sparse_region) {
 		/* Get EOF */
 		t->entry_eof = 1;
 		r = ARCHIVE_EOF;
@@ -1576,6 +1584,7 @@ setup_current_filesystem(struct archive_read_disk *a)
 #if defined(HAVE_STRUCT_STATFS_F_NAMEMAX)
 	t->current_filesystem->name_max = sfs.f_namemax;
 #else
+# if defined(_PC_NAME_MAX)
 	/* Mac OS X does not have f_namemax in struct statfs. */
 	if (tree_current_is_symblic_link_target(t)) {
 		if (tree_enter_working_dir(t) != 0) {
@@ -1585,6 +1594,9 @@ setup_current_filesystem(struct archive_read_disk *a)
 		nm = pathconf(tree_current_access_path(t), _PC_NAME_MAX);
 	} else
 		nm = fpathconf(tree_current_dir_fd(t), _PC_NAME_MAX);
+# else
+	nm = -1;
+# endif
 	if (nm == -1)
 		t->current_filesystem->name_max = NAME_MAX;
 	else
@@ -1681,7 +1693,9 @@ setup_current_filesystem(struct archive_read_disk *a)
 {
 	struct tree *t = a->tree;
 	struct statfs sfs;
+#if defined(HAVE_STATVFS)
 	struct statvfs svfs;
+#endif
 	int r, vr = 0, xr = 0;
 
 	if (tree_current_is_symblic_link_target(t)) {
@@ -1698,7 +1712,9 @@ setup_current_filesystem(struct archive_read_disk *a)
 			    "openat failed");
 			return (ARCHIVE_FAILED);
 		}
+#if defined(HAVE_FSTATVFS)
 		vr = fstatvfs(fd, &svfs);/* for f_flag, mount flags */
+#endif
 		r = fstatfs(fd, &sfs);
 		if (r == 0)
 			xr = get_xfer_size(t, fd, NULL);
@@ -1708,14 +1724,18 @@ setup_current_filesystem(struct archive_read_disk *a)
 			archive_set_error(&a->archive, errno, "fchdir failed");
 			return (ARCHIVE_FAILED);
 		}
+#if defined(HAVE_STATVFS)
 		vr = statvfs(tree_current_access_path(t), &svfs);
+#endif
 		r = statfs(tree_current_access_path(t), &sfs);
 		if (r == 0)
 			xr = get_xfer_size(t, -1, tree_current_access_path(t));
 #endif
 	} else {
 #ifdef HAVE_FSTATFS
+#if defined(HAVE_FSTATVFS)
 		vr = fstatvfs(tree_current_dir_fd(t), &svfs);
+#endif
 		r = fstatfs(tree_current_dir_fd(t), &sfs);
 		if (r == 0)
 			xr = get_xfer_size(t, tree_current_dir_fd(t), NULL);
@@ -1724,7 +1744,9 @@ setup_current_filesystem(struct archive_read_disk *a)
 			archive_set_error(&a->archive, errno, "fchdir failed");
 			return (ARCHIVE_FAILED);
 		}
+#if defined(HAVE_STATVFS)
 		vr = statvfs(".", &svfs);
+#endif
 		r = statfs(".", &sfs);
 		if (r == 0)
 			xr = get_xfer_size(t, -1, ".");
@@ -1737,10 +1759,17 @@ setup_current_filesystem(struct archive_read_disk *a)
 		return (ARCHIVE_FAILED);
 	} else if (xr == 1) {
 		/* pathconf(_PC_REX_*) operations are not supported. */
+#if defined(HAVE_STATVFS)
 		t->current_filesystem->xfer_align = svfs.f_frsize;
 		t->current_filesystem->max_xfer_size = -1;
 		t->current_filesystem->min_xfer_size = svfs.f_bsize;
 		t->current_filesystem->incr_xfer_size = svfs.f_bsize;
+#else
+		t->current_filesystem->xfer_align = sfs.f_frsize;
+		t->current_filesystem->max_xfer_size = -1;
+		t->current_filesystem->min_xfer_size = sfs.f_bsize;
+		t->current_filesystem->incr_xfer_size = sfs.f_bsize;
+#endif
 	}
 	switch (sfs.f_type) {
 	case AFS_SUPER_MAGIC:
@@ -1765,7 +1794,11 @@ setup_current_filesystem(struct archive_read_disk *a)
 	}
 
 #if defined(ST_NOATIME)
+#if defined(HAVE_STATVFS)
 	if (svfs.f_flag & ST_NOATIME)
+#else
+	if (sfs.f_flag & ST_NOATIME)
+#endif
 		t->current_filesystem->noatime = 1;
 	else
 #endif