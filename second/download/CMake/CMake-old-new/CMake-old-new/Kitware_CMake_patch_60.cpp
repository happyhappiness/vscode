@@ -165,7 +165,7 @@ struct filesystem {
 	int		synthetic;
 	int		remote;
 	int		noatime;
-#if defined(HAVE_READDIR_R)
+#if defined(USE_READDIR_R)
 	size_t		name_max;
 #endif
 	long		incr_xfer_size;
@@ -200,7 +200,7 @@ struct tree {
 	DIR			*d;
 #define	INVALID_DIR_HANDLE NULL
 	struct dirent		*de;
-#if defined(HAVE_READDIR_R)
+#if defined(USE_READDIR_R)
 	struct dirent		*dirent;
 	size_t			 dirent_allocated;
 #endif
@@ -244,7 +244,7 @@ struct tree {
 	int			 initial_filesystem_id;
 	int			 current_filesystem_id;
 	int			 max_filesystem_id;
-	int			 allocated_filesytem;
+	int			 allocated_filesystem;
 
 	int			 entry_fd;
 	int			 entry_eof;
@@ -675,7 +675,7 @@ setup_suitable_read_buffer(struct archive_read_disk *a)
 				asize = cf->min_xfer_size;
 
 			/* Increase a buffer size up to 64K bytes in
-			 * a proper incremant size. */
+			 * a proper increment size. */
 			while (asize < 1024*64)
 				asize += incr;
 			/* Take a margin to adjust to the filesystem
@@ -938,7 +938,7 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 		r = archive_match_path_excluded(a->matching, entry);
 		if (r < 0) {
 			archive_set_error(&(a->archive), errno,
-			    "Faild : %s", archive_error_string(a->matching));
+			    "Failed : %s", archive_error_string(a->matching));
 			return (r);
 		}
 		if (r) {
@@ -1026,7 +1026,7 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 
 	/* Save the times to be restored. This must be in before
 	 * calling archive_read_disk_descend() or any chance of it,
-	 * especially, invokng a callback. */
+	 * especially, invoking a callback. */
 	t->restore_time.mtime = archive_entry_mtime(entry);
 	t->restore_time.mtime_nsec = archive_entry_mtime_nsec(entry);
 	t->restore_time.atime = archive_entry_atime(entry);
@@ -1041,7 +1041,7 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 		r = archive_match_time_excluded(a->matching, entry);
 		if (r < 0) {
 			archive_set_error(&(a->archive), errno,
-			    "Faild : %s", archive_error_string(a->matching));
+			    "Failed : %s", archive_error_string(a->matching));
 			return (r);
 		}
 		if (r) {
@@ -1067,7 +1067,7 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 		r = archive_match_owner_excluded(a->matching, entry);
 		if (r < 0) {
 			archive_set_error(&(a->archive), errno,
-			    "Faild : %s", archive_error_string(a->matching));
+			    "Failed : %s", archive_error_string(a->matching));
 			return (r);
 		}
 		if (r) {
@@ -1382,18 +1382,18 @@ update_current_filesystem(struct archive_read_disk *a, int64_t dev)
 
 	for (i = 0; i < t->max_filesystem_id; i++) {
 		if (t->filesystem_table[i].dev == dev) {
-			/* There is the filesytem ID we've already generated. */
+			/* There is the filesystem ID we've already generated. */
 			t->current_filesystem_id = i;
 			t->current_filesystem = &(t->filesystem_table[i]);
 			return (ARCHIVE_OK);
 		}
 	}
 
 	/*
-	 * This is the new filesytem which we have to generate a new ID for.
+	 * This is the new filesystem which we have to generate a new ID for.
 	 */
 	fid = t->max_filesystem_id++;
-	if (t->max_filesystem_id > t->allocated_filesytem) {
+	if (t->max_filesystem_id > t->allocated_filesystem) {
 		size_t s;
 		void *p;
 
@@ -1406,7 +1406,7 @@ update_current_filesystem(struct archive_read_disk *a, int64_t dev)
 			return (ARCHIVE_FATAL);
 		}
 		t->filesystem_table = (struct filesystem *)p;
-		t->allocated_filesytem = s;
+		t->allocated_filesystem = s;
 	}
 	t->current_filesystem_id = fid;
 	t->current_filesystem = &(t->filesystem_table[fid]);
@@ -1504,7 +1504,20 @@ setup_current_filesystem(struct archive_read_disk *a)
 	struct tree *t = a->tree;
 	struct statfs sfs;
 #if defined(HAVE_GETVFSBYNAME) && defined(VFCF_SYNTHETIC)
+/* TODO: configure should set GETVFSBYNAME_ARG_TYPE to make
+ * this accurate; some platforms have both and we need the one that's
+ * used by getvfsbyname()
+ *
+ * Then the following would become:
+ *  #if defined(GETVFSBYNAME_ARG_TYPE)
+ *   GETVFSBYNAME_ARG_TYPE vfc;
+ *  #endif
+ */
+#  if defined(HAVE_STRUCT_XVFSCONF)
 	struct xvfsconf vfc;
+#  else
+	struct vfsconf vfc;
+#  endif
 #endif
 	int r, xr = 0;
 #if !defined(HAVE_STRUCT_STATFS_F_NAMEMAX)
@@ -1579,7 +1592,7 @@ setup_current_filesystem(struct archive_read_disk *a)
 #endif
 		t->current_filesystem->noatime = 0;
 
-#if defined(HAVE_READDIR_R)
+#if defined(USE_READDIR_R)
 	/* Set maximum filename length. */
 #if defined(HAVE_STRUCT_STATFS_F_NAMEMAX)
 	t->current_filesystem->name_max = sfs.f_namemax;
@@ -1602,7 +1615,7 @@ setup_current_filesystem(struct archive_read_disk *a)
 	else
 		t->current_filesystem->name_max = nm;
 #endif
-#endif /* HAVE_READDIR_R */
+#endif /* USE_READDIR_R */
 	return (ARCHIVE_OK);
 }
 
@@ -1643,7 +1656,7 @@ setup_current_filesystem(struct archive_read_disk *a)
 		archive_set_error(&a->archive, errno, "statvfs failed");
 		return (ARCHIVE_FAILED);
 	} else if (xr == 1) {
-		/* Usuall come here unless NetBSD supports _PC_REC_XFER_ALIGN
+		/* Usually come here unless NetBSD supports _PC_REC_XFER_ALIGN
 		 * for pathconf() function. */
 		t->current_filesystem->xfer_align = sfs.f_frsize;
 		t->current_filesystem->max_xfer_size = -1;
@@ -1804,7 +1817,7 @@ setup_current_filesystem(struct archive_read_disk *a)
 #endif
 		t->current_filesystem->noatime = 0;
 
-#if defined(HAVE_READDIR_R)
+#if defined(USE_READDIR_R)
 	/* Set maximum filename length. */
 	t->current_filesystem->name_max = sfs.f_namelen;
 #endif
@@ -1888,7 +1901,7 @@ setup_current_filesystem(struct archive_read_disk *a)
 #endif
 		t->current_filesystem->noatime = 0;
 
-#if defined(HAVE_READDIR_R)
+#if defined(USE_READDIR_R)
 	/* Set maximum filename length. */
 	t->current_filesystem->name_max = sfs.f_namemax;
 #endif
@@ -1905,7 +1918,7 @@ static int
 setup_current_filesystem(struct archive_read_disk *a)
 {
 	struct tree *t = a->tree;
-#if defined(_PC_NAME_MAX) && defined(HAVE_READDIR_R)
+#if defined(_PC_NAME_MAX) && defined(USE_READDIR_R)
 	long nm;
 #endif
 	t->current_filesystem->synthetic = -1;/* Not supported */
@@ -1917,7 +1930,7 @@ setup_current_filesystem(struct archive_read_disk *a)
 	t->current_filesystem->min_xfer_size = -1;
 	t->current_filesystem->incr_xfer_size = -1;
 
-#if defined(HAVE_READDIR_R)
+#if defined(USE_READDIR_R)
 	/* Set maximum filename length. */
 #  if defined(_PC_NAME_MAX)
 	if (tree_current_is_symblic_link_target(t)) {
@@ -1931,7 +1944,7 @@ setup_current_filesystem(struct archive_read_disk *a)
 	if (nm == -1)
 #  endif /* _PC_NAME_MAX */
 		/*
-		 * Some sysmtes (HP-UX or others?) incorrectly defined
+		 * Some systems (HP-UX or others?) incorrectly defined
 		 * NAME_MAX macro to be a smaller value.
 		 */
 #  if defined(NAME_MAX) && NAME_MAX >= 255
@@ -1945,7 +1958,7 @@ setup_current_filesystem(struct archive_read_disk *a)
 	else
 		t->current_filesystem->name_max = nm;
 #  endif /* _PC_NAME_MAX */
-#endif /* HAVE_READDIR_R */
+#endif /* USE_READDIR_R */
 	return (ARCHIVE_OK);
 }
 
@@ -2050,8 +2063,7 @@ tree_push(struct tree *t, const char *path, int filesystem_id,
 {
 	struct tree_entry *te;
 
-	te = malloc(sizeof(*te));
-	memset(te, 0, sizeof(*te));
+	te = calloc(1, sizeof(*te));
 	te->next = t->stack;
 	te->parent = t->current;
 	if (te->parent)
@@ -2109,9 +2121,8 @@ tree_open(const char *path, int symlink_mode, int restore_time)
 {
 	struct tree *t;
 
-	if ((t = malloc(sizeof(*t))) == NULL)
+	if ((t = calloc(1, sizeof(*t))) == NULL)
 		return (NULL);
-	memset(t, 0, sizeof(*t));
 	archive_string_init(&t->path);
 	archive_string_ensure(&t->path, 31);
 	t->initial_symlink_mode = symlink_mode;
@@ -2353,7 +2364,7 @@ tree_dir_next_posix(struct tree *t)
 	size_t namelen;
 
 	if (t->d == NULL) {
-#if defined(HAVE_READDIR_R)
+#if defined(USE_READDIR_R)
 		size_t dirent_size;
 #endif
 
@@ -2374,7 +2385,7 @@ tree_dir_next_posix(struct tree *t)
 			t->visit_type = r != 0 ? r : TREE_ERROR_DIR;
 			return (t->visit_type);
 		}
-#if defined(HAVE_READDIR_R)
+#if defined(USE_READDIR_R)
 		dirent_size = offsetof(struct dirent, d_name) +
 		  t->filesystem_table[t->current->filesystem_id].name_max + 1;
 		if (t->dirent == NULL || t->dirent_allocated < dirent_size) {
@@ -2391,11 +2402,11 @@ tree_dir_next_posix(struct tree *t)
 			}
 			t->dirent_allocated = dirent_size;
 		}
-#endif /* HAVE_READDIR_R */
+#endif /* USE_READDIR_R */
 	}
 	for (;;) {
 		errno = 0;
-#if defined(HAVE_READDIR_R)
+#if defined(USE_READDIR_R)
 		r = readdir_r(t->d, t->dirent, &t->de);
 #ifdef _AIX
 		/* Note: According to the man page, return value 9 indicates
@@ -2647,7 +2658,7 @@ tree_free(struct tree *t)
 	if (t == NULL)
 		return;
 	archive_string_free(&t->path);
-#if defined(HAVE_READDIR_R)
+#if defined(USE_READDIR_R)
 	free(t->dirent);
 #endif
 	free(t->sparse_list);