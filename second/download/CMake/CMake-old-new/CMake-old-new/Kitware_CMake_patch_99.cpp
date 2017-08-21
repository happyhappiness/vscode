@@ -116,12 +116,11 @@ archive_write_set_format_cpio_newc(struct archive *_a)
 	if (a->format_free != NULL)
 		(a->format_free)(a);
 
-	cpio = (struct cpio *)malloc(sizeof(*cpio));
+	cpio = (struct cpio *)calloc(1, sizeof(*cpio));
 	if (cpio == NULL) {
 		archive_set_error(&a->archive, ENOMEM, "Can't allocate cpio data");
 		return (ARCHIVE_FATAL);
 	}
-	memset(cpio, 0, sizeof(*cpio));
 	a->format_data = cpio;
 	a->format_name = "cpio";
 	a->format_options = archive_write_newc_options;
@@ -232,7 +231,7 @@ write_header(struct archive_write *a, struct archive_entry *entry)
 	sconv = get_sconv(a);
 
 #if defined(_WIN32) && !defined(__CYGWIN__)
-	/* Make sure the path separators in pahtname, hardlink and symlink
+	/* Make sure the path separators in pathname, hardlink and symlink
 	 * are all slash '/', not the Windows path separator '\'. */
 	entry_main = __la_win_entry_in_posix_pathseparator(entry);
 	if (entry_main == NULL) {