@@ -168,7 +168,7 @@ struct tree {
 	int			 initial_filesystem_id;
 	int			 current_filesystem_id;
 	int			 max_filesystem_id;
-	int			 allocated_filesytem;
+	int			 allocated_filesystem;
 
 	HANDLE			 entry_fh;
 	int			 entry_eof;
@@ -389,10 +389,9 @@ archive_read_disk_new(void)
 {
 	struct archive_read_disk *a;
 
-	a = (struct archive_read_disk *)malloc(sizeof(*a));
+	a = (struct archive_read_disk *)calloc(1, sizeof(*a));
 	if (a == NULL)
 		return (NULL);
-	memset(a, 0, sizeof(*a));
 	a->archive.magic = ARCHIVE_READ_DISK_MAGIC;
 	a->archive.state = ARCHIVE_STATE_NEW;
 	a->archive.vtable = archive_read_disk_vtable();
@@ -803,7 +802,7 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 		r = archive_match_path_excluded(a->matching, entry);
 		if (r < 0) {
 			archive_set_error(&(a->archive), errno,
-			    "Faild : %s", archive_error_string(a->matching));
+			    "Failed : %s", archive_error_string(a->matching));
 			return (r);
 		}
 		if (r) {
@@ -863,7 +862,7 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 
 	/* Save the times to be restored. This must be in before
 	 * calling archive_read_disk_descend() or any chance of it,
-	 * especially, invokng a callback. */
+	 * especially, invoking a callback. */
 	t->restore_time.lastWriteTime = st->ftLastWriteTime;
 	t->restore_time.lastAccessTime = st->ftLastAccessTime;
 	t->restore_time.filetype = archive_entry_filetype(entry);
@@ -875,7 +874,7 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 		r = archive_match_time_excluded(a->matching, entry);
 		if (r < 0) {
 			archive_set_error(&(a->archive), errno,
-			    "Faild : %s", archive_error_string(a->matching));
+			    "Failed : %s", archive_error_string(a->matching));
 			return (r);
 		}
 		if (r) {
@@ -901,7 +900,7 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 		r = archive_match_owner_excluded(a->matching, entry);
 		if (r < 0) {
 			archive_set_error(&(a->archive), errno,
-			    "Faild : %s", archive_error_string(a->matching));
+			    "Failed : %s", archive_error_string(a->matching));
 			return (r);
 		}
 		if (r) {
@@ -1261,18 +1260,18 @@ update_current_filesystem(struct archive_read_disk *a, int64_t dev)
 
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
-	 * There is a new filesytem, we generate a new ID for.
+	 * There is a new filesystem, we generate a new ID for.
 	 */
 	fid = t->max_filesystem_id++;
-	if (t->max_filesystem_id > t->allocated_filesytem) {
+	if (t->max_filesystem_id > t->allocated_filesystem) {
 		size_t s;
 		void *p;
 
@@ -1285,7 +1284,7 @@ update_current_filesystem(struct archive_read_disk *a, int64_t dev)
 			return (ARCHIVE_FATAL);
 		}
 		t->filesystem_table = (struct filesystem *)p;
-		t->allocated_filesytem = (int)s;
+		t->allocated_filesystem = (int)s;
 	}
 	t->current_filesystem_id = fid;
 	t->current_filesystem = &(t->filesystem_table[fid]);
@@ -1402,7 +1401,7 @@ close_and_restore_time(HANDLE h, struct tree *t, struct restore_time *rt)
 	if (h == INVALID_HANDLE_VALUE && AE_IFLNK == rt->filetype)
 		return (0);
 
-	/* Close a file descritor.
+	/* Close a file descriptor.
 	 * It will not be used for SetFileTime() because it has been opened
 	 * by a read only mode.
 	 */
@@ -1437,8 +1436,7 @@ tree_push(struct tree *t, const wchar_t *path, const wchar_t *full_path,
 {
 	struct tree_entry *te;
 
-	te = malloc(sizeof(*te));
-	memset(te, 0, sizeof(*te));
+	te = calloc(1, sizeof(*te));
 	te->next = t->stack;
 	te->parent = t->current;
 	if (te->parent)
@@ -1507,8 +1505,7 @@ tree_open(const wchar_t *path, int symlink_mode, int restore_time)
 {
 	struct tree *t;
 
-	t = malloc(sizeof(*t));
-	memset(t, 0, sizeof(*t));
+	t = calloc(1, sizeof(*t));
 	archive_string_init(&(t->full_path));
 	archive_string_init(&t->path);
 	archive_wstring_ensure(&t->path, 15);