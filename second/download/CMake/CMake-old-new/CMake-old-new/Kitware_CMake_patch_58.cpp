@@ -398,8 +398,7 @@ archive_read_disk_new(void)
 	a->entry = archive_entry_new2(&a->archive);
 	a->lookup_uname = trivial_lookup_uname;
 	a->lookup_gname = trivial_lookup_gname;
-	a->enable_copyfile = 1;
-	a->traverse_mount_points = 1;
+	a->flags = ARCHIVE_READDISK_MAC_COPYFILE;
 	return (&a->archive);
 }
 
@@ -495,7 +494,7 @@ archive_read_disk_set_atime_restored(struct archive *_a)
 	struct archive_read_disk *a = (struct archive_read_disk *)_a;
 	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
 	    ARCHIVE_STATE_ANY, "archive_read_disk_restore_atime");
-	a->restore_time = 1;
+	a->flags |= ARCHIVE_READDISK_RESTORE_ATIME;
 	if (a->tree != NULL)
 		a->tree->flags |= needsRestoreTimes;
 	return (ARCHIVE_OK);
@@ -510,25 +509,14 @@ archive_read_disk_set_behavior(struct archive *_a, int flags)
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
 	return (r);
 }
 
@@ -852,7 +840,7 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 	}
 	if (t->initial_filesystem_id == -1)
 		t->initial_filesystem_id = t->current_filesystem_id;
-	if (!a->traverse_mount_points) {
+	if (a->flags & ARCHIVE_READDISK_NO_TRAVERSE_MOUNTS) {
 		if (t->initial_filesystem_id != t->current_filesystem_id)
 			return (ARCHIVE_RETRY);
 	}
@@ -1219,9 +1207,11 @@ _archive_read_disk_open_w(struct archive *_a, const wchar_t *pathname)
 	struct archive_read_disk *a = (struct archive_read_disk *)_a;
 
 	if (a->tree != NULL)
-		a->tree = tree_reopen(a->tree, pathname, a->restore_time);
+		a->tree = tree_reopen(a->tree, pathname,
+		    a->flags & ARCHIVE_READDISK_RESTORE_ATIME);
 	else
-		a->tree = tree_open(pathname, a->symlink_mode, a->restore_time);
+		a->tree = tree_open(pathname, a->symlink_mode,
+		    a->flags & ARCHIVE_READDISK_RESTORE_ATIME);
 	if (a->tree == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate directory traversal data");
@@ -1519,7 +1509,7 @@ tree_reopen(struct tree *t, const wchar_t *path, int restore_time)
 	struct archive_wstring ws;
 	wchar_t *pathname, *p, *base;
 
-	t->flags = (restore_time)?needsRestoreTimes:0;
+	t->flags = (restore_time != 0)?needsRestoreTimes:0;
 	t->visit_type = 0;
 	t->tree_errno = 0;
 	t->full_path_dir_length = 0;