@@ -387,7 +387,7 @@ static int	archive_read_format_iso9660_read_data(struct archive_read *,
 static int	archive_read_format_iso9660_read_data_skip(struct archive_read *);
 static int	archive_read_format_iso9660_read_header(struct archive_read *,
 		    struct archive_entry *);
-static const char *build_pathname(struct archive_string *, struct file_info *);
+static const char *build_pathname(struct archive_string *, struct file_info *, int);
 static int	build_pathname_utf16be(unsigned char *, size_t, size_t *,
 		    struct file_info *);
 #if DEBUG
@@ -1225,6 +1225,7 @@ archive_read_format_iso9660_read_header(struct archive_read *a,
 			archive_set_error(&a->archive,
 			    ARCHIVE_ERRNO_FILE_FORMAT,
 			    "Pathname is too long");
+			return (ARCHIVE_FATAL);
 		}
 
 		r = archive_entry_copy_pathname_l(entry,
@@ -1247,9 +1248,16 @@ archive_read_format_iso9660_read_header(struct archive_read *a,
 			rd_r = ARCHIVE_WARN;
 		}
 	} else {
-		archive_string_empty(&iso9660->pathname);
-		archive_entry_set_pathname(entry,
-		    build_pathname(&iso9660->pathname, file));
+		const char *path = build_pathname(&iso9660->pathname, file, 0);
+		if (path == NULL) {
+			archive_set_error(&a->archive,
+			    ARCHIVE_ERRNO_FILE_FORMAT,
+			    "Pathname is too long");
+			return (ARCHIVE_FATAL);
+		} else {
+			archive_string_empty(&iso9660->pathname);
+			archive_entry_set_pathname(entry, path);
+		}
 	}
 
 	iso9660->entry_bytes_remaining = file->size;
@@ -1744,12 +1752,12 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
     const unsigned char *isodirrec)
 {
 	struct iso9660 *iso9660;
-	struct file_info *file;
+	struct file_info *file, *filep;
 	size_t name_len;
 	const unsigned char *rr_start, *rr_end;
 	const unsigned char *p;
 	size_t dr_len;
-	uint64_t fsize;
+	uint64_t fsize, offset;
 	int32_t location;
 	int flags;
 
@@ -1793,6 +1801,16 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 		return (NULL);
 	}
 
+	/* Sanity check that this entry does not create a cycle. */
+	offset = iso9660->logical_block_size * (uint64_t)location;
+	for (filep = parent; filep != NULL; filep = filep->parent) {
+		if (filep->offset == offset) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+			    "Directory structure contains loop");
+			return (NULL);
+		}
+	}
+
 	/* Create a new file entry and copy data from the ISO dir record. */
 	file = (struct file_info *)calloc(1, sizeof(*file));
 	if (file == NULL) {
@@ -1801,7 +1819,7 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 		return (NULL);
 	}
 	file->parent = parent;
-	file->offset = iso9660->logical_block_size * (uint64_t)location;
+	file->offset = offset;
 	file->size = fsize;
 	file->mtime = isodate7(isodirrec + DR_date_offset);
 	file->ctime = file->atime = file->mtime;
@@ -3147,29 +3165,39 @@ static time_t
 time_from_tm(struct tm *t)
 {
 #if HAVE_TIMEGM
-	/* Use platform timegm() if available. */
-	return (timegm(t));
+        /* Use platform timegm() if available. */
+        return (timegm(t));
 #elif HAVE__MKGMTIME64
-	return (_mkgmtime64(t));
+        return (_mkgmtime64(t));
 #else
-	/* Else use direct calculation using POSIX assumptions. */
-	/* First, fix up tm_yday based on the year/month/day. */
-	if (mktime(t) == (time_t)-1)
-		return ((time_t)-1);
-	/* Then we can compute timegm() from first principles. */
-	return (t->tm_sec + t->tm_min * 60 + t->tm_hour * 3600
-	    + t->tm_yday * 86400 + (t->tm_year - 70) * 31536000
-	    + ((t->tm_year - 69) / 4) * 86400 -
-	    ((t->tm_year - 1) / 100) * 86400
-	    + ((t->tm_year + 299) / 400) * 86400);
+        /* Else use direct calculation using POSIX assumptions. */
+        /* First, fix up tm_yday based on the year/month/day. */
+        if (mktime(t) == (time_t)-1)
+                return ((time_t)-1);
+        /* Then we can compute timegm() from first principles. */
+        return (t->tm_sec
+            + t->tm_min * 60
+            + t->tm_hour * 3600
+            + t->tm_yday * 86400
+            + (t->tm_year - 70) * 31536000
+            + ((t->tm_year - 69) / 4) * 86400
+            - ((t->tm_year - 1) / 100) * 86400
+            + ((t->tm_year + 299) / 400) * 86400);
 #endif
 }
 
 static const char *
-build_pathname(struct archive_string *as, struct file_info *file)
+build_pathname(struct archive_string *as, struct file_info *file, int depth)
 {
+	// Plain ISO9660 only allows 8 dir levels; if we get
+	// to 1000, then something is very, very wrong.
+	if (depth > 1000) {
+		return NULL;
+	}
 	if (file->parent != NULL && archive_strlen(&file->parent->name) > 0) {
-		build_pathname(as, file->parent);
+		if (build_pathname(as, file->parent, depth + 1) == NULL) {
+			return NULL;
+		}
 		archive_strcat(as, "/");
 	}
 	if (archive_strlen(&file->name) == 0)