 
 static void dump_marks(void)
 {
 	static struct lock_file mark_lock;
 	FILE *f;
 
-	if (!export_marks_file)
+	if (!export_marks_file || (import_marks_file && !import_marks_file_done))
 		return;
 
 	if (hold_lock_file_for_update(&mark_lock, export_marks_file, 0) < 0) {
-		failure |= error("Unable to write marks file %s: %s",
-			export_marks_file, strerror(errno));
+		failure |= error_errno("Unable to write marks file %s",
+				       export_marks_file);
 		return;
 	}
 
 	f = fdopen_lock_file(&mark_lock, "w");
 	if (!f) {
 		int saved_errno = errno;
