@@ -98,9 +98,9 @@ static const char template_header[] = {
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
@@ -161,13 +161,12 @@ archive_write_set_format_v7tar(struct archive *_a)
 		return (ARCHIVE_FATAL);
 	}
 
-	v7tar = (struct v7tar *)malloc(sizeof(*v7tar));
+	v7tar = (struct v7tar *)calloc(1, sizeof(*v7tar));
 	if (v7tar == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate v7tar data");
 		return (ARCHIVE_FATAL);
 	}
-	memset(v7tar, 0, sizeof(*v7tar));
 	a->format_data = v7tar;
 	a->format_name = "tar (non-POSIX)";
 	a->format_options = archive_write_v7tar_options;
@@ -314,7 +313,7 @@ archive_write_v7tar_header(struct archive_write *a, struct archive_entry *entry)
 	}
 
 #if defined(_WIN32) && !defined(__CYGWIN__)
-	/* Make sure the path separators in pahtname, hardlink and symlink
+	/* Make sure the path separators in pathname, hardlink and symlink
 	 * are all slash '/', not the Windows path separator '\'. */
 	entry_main = __la_win_entry_in_posix_pathseparator(entry);
 	if (entry_main == NULL) {