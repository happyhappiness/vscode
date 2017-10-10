 	}
 }
 
 static void dump_marks(void)
 {
 	static struct lock_file mark_lock;
-	int mark_fd;
 	FILE *f;
 
 	if (!export_marks_file)
 		return;
 
-	mark_fd = hold_lock_file_for_update(&mark_lock, export_marks_file, 0);
-	if (mark_fd < 0) {
+	if (hold_lock_file_for_update(&mark_lock, export_marks_file, 0) < 0) {
 		failure |= error("Unable to write marks file %s: %s",
 			export_marks_file, strerror(errno));
 		return;
 	}
 
-	f = fdopen(mark_fd, "w");
+	f = fdopen_lock_file(&mark_lock, "w");
 	if (!f) {
 		int saved_errno = errno;
 		rollback_lock_file(&mark_lock);
 		failure |= error("Unable to write marks file %s: %s",
 			export_marks_file, strerror(saved_errno));
 		return;
 	}
 
-	/*
-	 * Since the lock file was fdopen()'ed, it should not be close()'ed.
-	 * Assign -1 to the lock file descriptor so that commit_lock_file()
-	 * won't try to close() it.
-	 */
-	mark_lock.fd = -1;
-
 	dump_marks_helper(f, 0, marks);
-	if (ferror(f) || fclose(f)) {
-		int saved_errno = errno;
-		rollback_lock_file(&mark_lock);
-		failure |= error("Unable to write marks file %s: %s",
-			export_marks_file, strerror(saved_errno));
-		return;
-	}
-
 	if (commit_lock_file(&mark_lock)) {
-		int saved_errno = errno;
-		rollback_lock_file(&mark_lock);
 		failure |= error("Unable to commit marks file %s: %s",
-			export_marks_file, strerror(saved_errno));
+			export_marks_file, strerror(errno));
 		return;
 	}
 }
 
 static void read_marks(void)
 {
