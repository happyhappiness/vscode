 			export_marks_file, strerror(saved_errno));
 		return;
 	}
 
 	dump_marks_helper(f, 0, marks);
 	if (commit_lock_file(&mark_lock)) {
-		failure |= error("Unable to write file %s: %s",
-			export_marks_file, strerror(errno));
+		failure |= error_errno("Unable to write file %s",
+				       export_marks_file);
 		return;
 	}
 }
 
 static void read_marks(void)
 {
 	char line[512];
 	FILE *f = fopen(import_marks_file, "r");
 	if (f)
 		;
 	else if (import_marks_file_ignore_missing && errno == ENOENT)
-		return; /* Marks file does not exist */
+		goto done; /* Marks file does not exist */
 	else
 		die_errno("cannot read '%s'", import_marks_file);
 	while (fgets(line, sizeof(line), f)) {
 		uintmax_t mark;
 		char *end;
 		unsigned char sha1[20];
