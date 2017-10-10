 	} else if (!file_exists(git_path(NOTES_MERGE_WORKTREE)))
 		/* NOTES_MERGE_WORKTREE should already be established */
 		die("missing '%s'. This should not happen",
 		    git_path(NOTES_MERGE_WORKTREE));
 }
 
-static void write_buf_to_worktree(const unsigned char *obj,
+static void write_buf_to_worktree(const struct object_id *obj,
 				  const char *buf, unsigned long size)
 {
 	int fd;
-	char *path = git_pathdup(NOTES_MERGE_WORKTREE "/%s", sha1_to_hex(obj));
+	char *path = git_pathdup(NOTES_MERGE_WORKTREE "/%s", oid_to_hex(obj));
 	if (safe_create_leading_directories_const(path))
 		die_errno("unable to create directory for '%s'", path);
 
 	fd = xopen(path, O_WRONLY | O_EXCL | O_CREAT, 0666);
 
 	while (size > 0) {
