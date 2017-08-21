@@ -465,8 +465,7 @@ archive_read_disk_new(void)
 	a->entry = archive_entry_new2(&a->archive);
 	a->lookup_uname = trivial_lookup_uname;
 	a->lookup_gname = trivial_lookup_gname;
-	a->enable_copyfile = 1;
-	a->traverse_mount_points = 1;
+	a->flags = ARCHIVE_READDISK_MAC_COPYFILE;
 	a->open_on_current_dir = open_on_current_dir;
 	a->tree_current_dir_fd = tree_current_dir_fd;
 	a->tree_enter_working_dir = tree_enter_working_dir;
@@ -563,25 +562,19 @@ archive_read_disk_set_symlink_hybrid(struct archive *_a)
 int
 archive_read_disk_set_atime_restored(struct archive *_a)
 {
-#ifndef HAVE_UTIMES
-	static int warning_done = 0;
-#endif
 	struct archive_read_disk *a = (struct archive_read_disk *)_a;
 	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
 	    ARCHIVE_STATE_ANY, "archive_read_disk_restore_atime");
 #ifdef HAVE_UTIMES
-	a->restore_time = 1;
+	a->flags |= ARCHIVE_READDISK_RESTORE_ATIME;
 	if (a->tree != NULL)
 		a->tree->flags |= needsRestoreTimes;
 	return (ARCHIVE_OK);
 #else
-	if (warning_done)
-		/* Warning was already emitted; suppress further warnings. */
-		return (ARCHIVE_OK);
-
+	/* Display warning and unset flag */
 	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 	    "Cannot restore access time on this system");
-	warning_done = 1;
+	a->flags &= ~ARCHIVE_READDISK_RESTORE_ATIME;
 	return (ARCHIVE_WARN);
 #endif
 }
@@ -595,29 +588,14 @@ archive_read_disk_set_behavior(struct archive *_a, int flags)
 	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
 	    ARCHIVE_STATE_ANY, "archive_read_disk_honor_nodump");
 
+	a->flags = flags;
+
 	if (flags & ARCHIVE_READDISK_RESTORE_ATIME)
 		r = archive_read_disk_set_atime_restored(_a);
 	else {
-		a->restore_time = 0;
 		if (a->tree != NULL)
 			a->tree->flags &= ~needsRestoreTimes;
 	}
-	if (flags & ARCHIVE_READDISK_HONOR_NODUMP)
-		a->honor_nodump = 1;
-	else
-		a->honor_nodump = 0;
-	if (flags & ARCHIVE_READDISK_MAC_COPYFILE)
-		a->enable_copyfile = 1;
-	else
-		a->enable_copyfile = 0;
-	if (flags & ARCHIVE_READDISK_NO_TRAVERSE_MOUNTS)
-		a->traverse_mount_points = 0;
-	else
-		a->traverse_mount_points = 1;
-	if (flags & ARCHIVE_READDISK_NO_XATTR)
-		a->suppress_xattr = 1;
-	else
-		a->suppress_xattr = 0;
 	return (r);
 }
 
@@ -918,7 +896,7 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 	} while (lst == NULL);
 
 #ifdef __APPLE__
-	if (a->enable_copyfile) {
+	if (a->flags & ARCHIVE_READDISK_MAC_COPYFILE) {
 		/* If we're using copyfile(), ignore "._XXX" files. */
 		const char *bname = strrchr(tree_current_path(t), '/');
 		if (bname == NULL)
@@ -989,7 +967,7 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 	}
 	if (t->initial_filesystem_id == -1)
 		t->initial_filesystem_id = t->current_filesystem_id;
-	if (!a->traverse_mount_points) {
+	if (a->flags & ARCHIVE_READDISK_NO_TRAVERSE_MOUNTS) {
 		if (t->initial_filesystem_id != t->current_filesystem_id)
 			descend = 0;
 	}
@@ -999,12 +977,14 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 	 * Honor nodump flag.
 	 * If the file is marked with nodump flag, do not return this entry.
 	 */
-	if (a->honor_nodump) {
+	if (a->flags & ARCHIVE_READDISK_HONOR_NODUMP) {
 #if defined(HAVE_STRUCT_STAT_ST_FLAGS) && defined(UF_NODUMP)
 		if (st->st_flags & UF_NODUMP)
 			return (ARCHIVE_RETRY);
-#elif defined(EXT2_IOC_GETFLAGS) && defined(EXT2_NODUMP_FL) &&\
-      defined(HAVE_WORKING_EXT2_IOC_GETFLAGS)
+#elif (defined(FS_IOC_GETFLAGS) && defined(FS_NODUMP_FL) && \
+       defined(HAVE_WORKING_FS_IOC_GETFLAGS)) || \
+      (defined(EXT2_IOC_GETFLAGS) && defined(EXT2_NODUMP_FL) && \
+       defined(HAVE_WORKING_EXT2_IOC_GETFLAGS))
 		if (S_ISREG(st->st_mode) || S_ISDIR(st->st_mode)) {
 			int stflags;
 
@@ -1013,9 +993,18 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 			    O_RDONLY | O_NONBLOCK | O_CLOEXEC);
 			__archive_ensure_cloexec_flag(t->entry_fd);
 			if (t->entry_fd >= 0) {
-				r = ioctl(t->entry_fd, EXT2_IOC_GETFLAGS,
+				r = ioctl(t->entry_fd,
+#ifdef FS_IOC_GETFLAGS
+				FS_IOC_GETFLAGS,
+#else
+				EXT2_IOC_GETFLAGS,
+#endif
 					&stflags);
+#ifdef FS_NODUMP_FL
+				if (r == 0 && (stflags & FS_NODUMP_FL) != 0)
+#else
 				if (r == 0 && (stflags & EXT2_NODUMP_FL) != 0)
+#endif
 					return (ARCHIVE_RETRY);
 			}
 		}
@@ -1340,10 +1329,11 @@ _archive_read_disk_open(struct archive *_a, const char *pathname)
 	struct archive_read_disk *a = (struct archive_read_disk *)_a;
 
 	if (a->tree != NULL)
-		a->tree = tree_reopen(a->tree, pathname, a->restore_time);
+		a->tree = tree_reopen(a->tree, pathname,
+		    a->flags & ARCHIVE_READDISK_RESTORE_ATIME);
 	else
 		a->tree = tree_open(pathname, a->symlink_mode,
-		    a->restore_time);
+		    a->flags & ARCHIVE_READDISK_RESTORE_ATIME);
 	if (a->tree == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate tar data");
@@ -2132,7 +2122,7 @@ tree_open(const char *path, int symlink_mode, int restore_time)
 static struct tree *
 tree_reopen(struct tree *t, const char *path, int restore_time)
 {
-	t->flags = (restore_time)?needsRestoreTimes:0;
+	t->flags = (restore_time != 0)?needsRestoreTimes:0;
 	t->flags |= onInitialDir;
 	t->visit_type = 0;
 	t->tree_errno = 0;