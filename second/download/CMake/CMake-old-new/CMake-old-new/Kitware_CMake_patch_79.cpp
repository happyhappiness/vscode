@@ -114,9 +114,9 @@ static const char template_header[] = {
 	'0','0','0','0','0','0', ' ','\0',
 	/* gid, space-null termination: 8 bytes */
 	'0','0','0','0','0','0', ' ','\0',
-	/* size, space termation: 12 bytes */
+	/* size, space termination: 12 bytes */
 	'0','0','0','0','0','0','0','0','0','0','0', ' ',
-	/* mtime, space termation: 12 bytes */
+	/* mtime, space termination: 12 bytes */
 	'0','0','0','0','0','0','0','0','0','0','0', ' ',
 	/* Initial checksum value: 8 spaces */
 	' ',' ',' ',' ',' ',' ',' ',' ',
@@ -184,13 +184,12 @@ archive_write_set_format_ustar(struct archive *_a)
 		return (ARCHIVE_FATAL);
 	}
 
-	ustar = (struct ustar *)malloc(sizeof(*ustar));
+	ustar = (struct ustar *)calloc(1, sizeof(*ustar));
 	if (ustar == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate ustar data");
 		return (ARCHIVE_FATAL);
 	}
-	memset(ustar, 0, sizeof(*ustar));
 	a->format_data = ustar;
 	a->format_name = "ustar";
 	a->format_options = archive_write_ustar_options;
@@ -307,7 +306,7 @@ archive_write_ustar_header(struct archive_write *a, struct archive_entry *entry)
 		 * case getting WCS failed. On POSIX, this is a
 		 * normal operation.
 		 */
-		if (p != NULL && p[strlen(p) - 1] != '/') {
+		if (p != NULL && p[0] != '\0' && p[strlen(p) - 1] != '/') {
 			struct archive_string as;
 
 			archive_string_init(&as);
@@ -336,7 +335,7 @@ archive_write_ustar_header(struct archive_write *a, struct archive_entry *entry)
 	}
 
 #if defined(_WIN32) && !defined(__CYGWIN__)
-	/* Make sure the path separators in pahtname, hardlink and symlink
+	/* Make sure the path separators in pathname, hardlink and symlink
 	 * are all slash '/', not the Windows path separator '\'. */
 	entry_main = __la_win_entry_in_posix_pathseparator(entry);
 	if (entry_main == NULL) {