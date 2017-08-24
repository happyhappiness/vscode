@@ -39,7 +39,8 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_support_format_zip.c 201102
  *
  * History of this code: The streaming Zip reader was first added to
  * libarchive in January 2005.  Support for seekable input sources was
- * added in Nov 2011.
+ * added in Nov 2011.  Zip64 support (including a significant code
+ * refactoring) was added in 2014.
  */
 
 #ifdef HAVE_ERRNO_H
@@ -419,8 +420,9 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 		unsigned short datasize = archive_le16dec(p + offset + 2);
 
 		offset += 4;
-		if (offset + datasize > extra_length)
+		if (offset + datasize > extra_length) {
 			break;
+		}
 #ifdef DEBUG
 		fprintf(stderr, "Header id 0x%04x, length %d\n",
 		    headerid, datasize);
@@ -555,7 +557,7 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 			 *  if bitmap & 1, 2 byte "version made by"
 			 *  if bitmap & 2, 2 byte "internal file attributes"
 			 *  if bitmap & 4, 4 byte "external file attributes"
-			 *  if bitmap * 7, 2 byte comment length + n byte comment
+			 *  if bitmap & 8, 2 byte comment length + n byte comment
 			 */
 			int bitmap, bitmap_last;
 
@@ -604,6 +606,19 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 				if (zip_entry->system == 3) {
 					zip_entry->mode
 					    = external_attributes >> 16;
+				} else if (zip_entry->system == 0) {
+					// Interpret MSDOS directory bit
+					if (0x10 == (external_attributes & 0x10)) {
+						zip_entry->mode = AE_IFDIR | 0775;
+					} else {
+						zip_entry->mode = AE_IFREG | 0664;
+					}
+					if (0x01 == (external_attributes & 0x01)) {
+						// Read-only bit; strip write permissions
+						zip_entry->mode &= 0555;
+					}
+				} else {
+					zip_entry->mode = 0;
 				}
 				offset += 4;
 				datasize -= 4;
@@ -810,6 +825,16 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 	}
 	__archive_read_consume(a, filename_length);
 
+	/* Read the extra data. */
+	if ((h = __archive_read_ahead(a, extra_length, NULL)) == NULL) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Truncated ZIP file header");
+		return (ARCHIVE_FATAL);
+	}
+
+	process_extra(h, extra_length, zip_entry);
+	__archive_read_consume(a, extra_length);
+
 	/* Work around a bug in Info-Zip: When reading from a pipe, it
 	 * stats the pipe instead of synthesizing a file entry. */
 	if ((zip_entry->mode & AE_IFMT) == AE_IFIFO) {
@@ -843,16 +868,31 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 		}
 	}
 
-	/* Read the extra data. */
-	if ((h = __archive_read_ahead(a, extra_length, NULL)) == NULL) {
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
-		    "Truncated ZIP file header");
-		return (ARCHIVE_FATAL);
+	/* Make sure directories end in '/' */
+	if ((zip_entry->mode & AE_IFMT) == AE_IFDIR) {
+		wp = archive_entry_pathname_w(entry);
+		if (wp != NULL) {
+			len = wcslen(wp);
+			if (len > 0 && wp[len - 1] != L'/') {
+				struct archive_wstring s;
+				archive_string_init(&s);
+				archive_wstrcat(&s, wp);
+				archive_wstrappend_wchar(&s, L'/');
+				archive_entry_copy_pathname_w(entry, s.s);
+			}
+		} else {
+			cp = archive_entry_pathname(entry);
+			len = (cp != NULL)?strlen(cp):0;
+			if (len > 0 && cp[len - 1] != '/') {
+				struct archive_string s;
+				archive_string_init(&s);
+				archive_strcat(&s, cp);
+				archive_strappend_char(&s, '/');
+				archive_entry_set_pathname(entry, s.s);
+			}
+		}
 	}
 
-	process_extra(h, extra_length, zip_entry);
-	__archive_read_consume(a, extra_length);
-
 	if (zip_entry->flags & LA_FROM_CENTRAL_DIRECTORY) {
 		/* If this came from the central dir, it's size info
 		 * is definitive, so ignore the length-at-end flag. */
@@ -2614,9 +2654,21 @@ slurp_central_directory(struct archive_read *a, struct zip *zip)
 		/* If we can't guess the mode, leave it zero here;
 		   when we read the local file header we might get
 		   more information. */
-		zip_entry->mode = 0;
 		if (zip_entry->system == 3) {
 			zip_entry->mode = external_attributes >> 16;
+		} else if (zip_entry->system == 0) {
+			// Interpret MSDOS directory bit
+			if (0x10 == (external_attributes & 0x10)) {
+				zip_entry->mode = AE_IFDIR | 0775;
+			} else {
+				zip_entry->mode = AE_IFREG | 0664;
+			}
+			if (0x01 == (external_attributes & 0x01)) {
+				// Read-only bit; strip write permissions
+				zip_entry->mode &= 0555;
+			}
+		} else {
+			zip_entry->mode = 0;
 		}
 
 		/* We're done with the regular data; get the filename and
@@ -2726,6 +2778,11 @@ zip_read_mac_metadata(struct archive_read *a, struct archive_entry *entry,
 
 	switch(rsrc->compression) {
 	case 0:  /* No compression. */
+		if (rsrc->uncompressed_size != rsrc->compressed_size) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+			    "Malformed OS X metadata entry: inconsistent size");
+			return (ARCHIVE_FATAL);
+		}
 #ifdef HAVE_ZLIB_H
 	case 8: /* Deflate compression. */
 #endif
@@ -2746,6 +2803,12 @@ zip_read_mac_metadata(struct archive_read *a, struct archive_entry *entry,
 		    (intmax_t)rsrc->uncompressed_size);
 		return (ARCHIVE_WARN);
 	}
+	if (rsrc->compressed_size > (4 * 1024 * 1024)) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Mac metadata is too large: %jd > 4M bytes",
+		    (intmax_t)rsrc->compressed_size);
+		return (ARCHIVE_WARN);
+	}
 
 	metadata = malloc((size_t)rsrc->uncompressed_size);
 	if (metadata == NULL) {
@@ -2784,6 +2847,8 @@ zip_read_mac_metadata(struct archive_read *a, struct archive_entry *entry,
 			bytes_avail = remaining_bytes;
 		switch(rsrc->compression) {
 		case 0:  /* No compression. */
+			if ((size_t)bytes_avail > metadata_bytes)
+				bytes_avail = metadata_bytes;
 			memcpy(mp, p, bytes_avail);
 			bytes_used = (size_t)bytes_avail;
 			metadata_bytes -= bytes_used;