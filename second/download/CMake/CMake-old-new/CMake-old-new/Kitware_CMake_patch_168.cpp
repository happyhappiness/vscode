@@ -66,6 +66,9 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_write_set_format_zip.c 201168 20
 #define ZIP_ENTRY_FLAG_LENGTH_AT_END	(1<<3)
 #define ZIP_ENTRY_FLAG_UTF8_NAME	(1 << 11)
 
+#define ZIP_4GB_MAX ARCHIVE_LITERAL_LL(0xffffffff)
+#define ZIP_4GB_MAX_UNCOMPRESSED ARCHIVE_LITERAL_LL(0xff000000)
+
 enum compression {
 	COMPRESSION_UNSPECIFIED = -1,
 	COMPRESSION_STORE = 0,
@@ -532,14 +535,13 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 	if (zip->flags & ZIP_FLAG_AVOID_ZIP64) {
 		/* Reject entries over 4GB. */
 		if (archive_entry_size_is_set(entry)
-		    && (archive_entry_size(entry) >
-			ARCHIVE_LITERAL_LL(0xffffffff))) {
+		    && (archive_entry_size(entry) > ZIP_4GB_MAX)) {
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 			    "Files > 4GB require Zip64 extensions");
 			return ARCHIVE_FAILED;
 		}
 		/* Reject entries if archive is > 4GB. */
-		if (zip->written_bytes > ARCHIVE_LITERAL_LL(0xffffffff)) {
+		if (zip->written_bytes > ZIP_4GB_MAX) {
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 			    "Archives > 4GB require Zip64 extensions");
 			return ARCHIVE_FAILED;
@@ -727,10 +729,8 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 		 *    (compression might make file larger)
 		 */
 		if ((zip->flags & ZIP_FLAG_FORCE_ZIP64)
-		    || (zip->entry_uncompressed_size + additional_size >
-			ARCHIVE_LITERAL_LL(0xffffffff))
-		    || (zip->entry_uncompressed_size >
-			ARCHIVE_LITERAL_LL(0xff000000)
+		    || (zip->entry_uncompressed_size + additional_size > ZIP_4GB_MAX)
+		    || (zip->entry_uncompressed_size > ZIP_4GB_MAX_UNCOMPRESSED
 			&& zip->entry_compression != COMPRESSION_STORE)) {
 			zip->entry_uses_zip64 = 1;
 			version_needed = 45;
@@ -788,8 +788,8 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 		 * are included only if these are 0xffffffff;
 		 * THEREFORE these must be set this way, even if we
 		 * know one of them is smaller. */
-		archive_le32enc(local_header + 18, ARCHIVE_LITERAL_LL(0xffffffff));
-		archive_le32enc(local_header + 22, ARCHIVE_LITERAL_LL(0xffffffff));
+		archive_le32enc(local_header + 18, ZIP_4GB_MAX);
+		archive_le32enc(local_header + 22, ZIP_4GB_MAX);
 	} else {
 		archive_le32enc(local_header + 18, (uint32_t)zip->entry_compressed_size);
 		archive_le32enc(local_header + 22, (uint32_t)zip->entry_uncompressed_size);
@@ -1217,22 +1217,22 @@ archive_write_zip_finish_entry(struct archive_write *a)
 	}
 
 	/* Append Zip64 extra data to central directory information. */
-	if (zip->entry_compressed_written > ARCHIVE_LITERAL_LL(0xffffffff)
-	    || zip->entry_uncompressed_written > ARCHIVE_LITERAL_LL(0xffffffff)
-	    || zip->entry_offset > ARCHIVE_LITERAL_LL(0xffffffff)) {
+	if (zip->entry_compressed_written > ZIP_4GB_MAX
+	    || zip->entry_uncompressed_written > ZIP_4GB_MAX
+	    || zip->entry_offset > ZIP_4GB_MAX) {
 		unsigned char zip64[32];
 		unsigned char *z = zip64, *zd;
 		memcpy(z, "\001\000\000\000", 4);
 		z += 4;
-		if (zip->entry_uncompressed_written >= ARCHIVE_LITERAL_LL(0xffffffff)) {
+		if (zip->entry_uncompressed_written >= ZIP_4GB_MAX) {
 			archive_le64enc(z, zip->entry_uncompressed_written);
 			z += 8;
 		}
-		if (zip->entry_compressed_written >= ARCHIVE_LITERAL_LL(0xffffffff)) {
+		if (zip->entry_compressed_written >= ZIP_4GB_MAX) {
 			archive_le64enc(z, zip->entry_compressed_written);
 			z += 8;
 		}
-		if (zip->entry_offset >= ARCHIVE_LITERAL_LL(0xffffffff)) {
+		if (zip->entry_offset >= ZIP_4GB_MAX) {
 			archive_le64enc(z, zip->entry_offset);
 			z += 8;
 		}
@@ -1256,15 +1256,15 @@ archive_write_zip_finish_entry(struct archive_write *a)
 		archive_le32enc(zip->file_header + 16, zip->entry_crc32);
 	archive_le32enc(zip->file_header + 20,
 		(uint32_t)zipmin(zip->entry_compressed_written,
-				 ARCHIVE_LITERAL_LL(0xffffffff)));
+				 ZIP_4GB_MAX));
 	archive_le32enc(zip->file_header + 24,
 		(uint32_t)zipmin(zip->entry_uncompressed_written,
-				 ARCHIVE_LITERAL_LL(0xffffffff)));
+				 ZIP_4GB_MAX));
 	archive_le16enc(zip->file_header + 30,
 	    (uint16_t)(zip->central_directory_bytes - zip->file_header_extra_offset));
 	archive_le32enc(zip->file_header + 42,
 		(uint32_t)zipmin(zip->entry_offset,
-				 ARCHIVE_LITERAL_LL(0xffffffff)));
+				 ZIP_4GB_MAX));
 
 	return (ARCHIVE_OK);
 }
@@ -1291,8 +1291,8 @@ archive_write_zip_close(struct archive_write *a)
 	offset_end = zip->written_bytes;
 
 	/* If central dir info is too large, write Zip64 end-of-cd */
-	if (offset_end - offset_start > ARCHIVE_LITERAL_LL(0xffffffff)
-	    || offset_start > ARCHIVE_LITERAL_LL(0xffffffff)
+	if (offset_end - offset_start > ZIP_4GB_MAX
+	    || offset_start > ZIP_4GB_MAX
 	    || zip->central_directory_entries > 0xffffUL
 	    || (zip->flags & ZIP_FLAG_FORCE_ZIP64)) {
 	  /* Zip64 end-of-cd record */
@@ -1332,11 +1332,9 @@ archive_write_zip_close(struct archive_write *a)
 	archive_le16enc(buff + 10, (uint16_t)zipmin(0xffffU,
 		zip->central_directory_entries));
 	archive_le32enc(buff + 12,
-		(uint32_t)zipmin(ARCHIVE_LITERAL_LL(0xffffffff),
-				 (offset_end - offset_start)));
+		(uint32_t)zipmin(ZIP_4GB_MAX, (offset_end - offset_start)));
 	archive_le32enc(buff + 16,
-		(uint32_t)zipmin(ARCHIVE_LITERAL_LL(0xffffffff),
-				 offset_start));
+		(uint32_t)zipmin(ZIP_4GB_MAX, offset_start));
 	ret = __archive_write_output(a, buff, 22);
 	if (ret != ARCHIVE_OK)
 		return (ARCHIVE_FATAL);