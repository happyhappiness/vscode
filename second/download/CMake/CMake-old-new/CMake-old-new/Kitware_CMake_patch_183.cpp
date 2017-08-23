@@ -180,7 +180,7 @@ _ar_read_header(struct archive_read *a, struct archive_entry *entry,
 	if (strncmp(h + AR_fmag_offset, "`\n", 2) != 0) {
 		archive_set_error(&a->archive, EINVAL,
 		    "Incorrect file header signature");
-		return (ARCHIVE_WARN);
+		return (ARCHIVE_FATAL);
 	}
 
 	/* Copy filename into work buffer. */
@@ -239,8 +239,15 @@ _ar_read_header(struct archive_read *a, struct archive_entry *entry,
 	 * and are not terminated in '/', so we don't trim anything
 	 * that starts with '/'.)
 	 */
-	if (filename[0] != '/' && *p == '/')
+	if (filename[0] != '/' && p > filename && *p == '/') {
 		*p = '\0';
+	}
+
+	if (p < filename) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Found entry with empty filename");
+		return (ARCHIVE_FATAL);
+	}
 
 	/*
 	 * '//' is the GNU filename table.
@@ -262,12 +269,12 @@ _ar_read_header(struct archive_read *a, struct archive_entry *entry,
 		if (entry_size == 0) {
 			archive_set_error(&a->archive, EINVAL,
 			    "Invalid string table");
-			return (ARCHIVE_WARN);
+			return (ARCHIVE_FATAL);
 		}
 		if (ar->strtab != NULL) {
 			archive_set_error(&a->archive, EINVAL,
 			    "More than one string tables exist");
-			return (ARCHIVE_WARN);
+			return (ARCHIVE_FATAL);
 		}
 
 		/* Read the filename table into memory. */
@@ -311,11 +318,11 @@ _ar_read_header(struct archive_read *a, struct archive_entry *entry,
 		 */
 		if (ar->strtab == NULL || number > ar->strtab_size) {
 			archive_set_error(&a->archive, EINVAL,
-			    "Can't find long filename for entry");
+			    "Can't find long filename for GNU/SVR4 archive entry");
 			archive_entry_copy_pathname(entry, filename);
 			/* Parse the time, owner, mode, size fields. */
 			ar_parse_common_header(ar, entry, h);
-			return (ARCHIVE_WARN);
+			return (ARCHIVE_FATAL);
 		}
 
 		archive_entry_copy_pathname(entry, &ar->strtab[(size_t)number]);
@@ -573,7 +580,7 @@ ar_parse_gnu_filename_table(struct archive_read *a)
 	    "Invalid string table");
 	free(ar->strtab);
 	ar->strtab = NULL;
-	return (ARCHIVE_WARN);
+	return (ARCHIVE_FATAL);
 }
 
 static uint64_t