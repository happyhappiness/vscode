@@ -96,11 +96,13 @@ enum compression {
 #endif
 };
 
-static ssize_t archive_write_zip_data(struct archive_write *, const void *buff, size_t s);
+static ssize_t archive_write_zip_data(struct archive_write *,
+		   const void *buff, size_t s);
 static int archive_write_zip_close(struct archive_write *);
 static int archive_write_zip_free(struct archive_write *);
 static int archive_write_zip_finish_entry(struct archive_write *);
-static int archive_write_zip_header(struct archive_write *, struct archive_entry *);
+static int archive_write_zip_header(struct archive_write *,
+	      struct archive_entry *);
 static int archive_write_zip_options(struct archive_write *,
 	      const char *, const char *);
 static unsigned int dos_time(const time_t);
@@ -270,7 +272,8 @@ archive_write_set_format_zip(struct archive *_a)
 
 	zip = (struct zip *) calloc(1, sizeof(*zip));
 	if (zip == NULL) {
-		archive_set_error(&a->archive, ENOMEM, "Can't allocate zip data");
+		archive_set_error(&a->archive, ENOMEM,
+		    "Can't allocate zip data");
 		return (ARCHIVE_FATAL);
 	}
 	zip->central_directory = NULL;
@@ -284,7 +287,8 @@ archive_write_set_format_zip(struct archive *_a)
 	zip->len_buf = 65536;
 	zip->buf = malloc(zip->len_buf);
 	if (zip->buf == NULL) {
-		archive_set_error(&a->archive, ENOMEM, "Can't allocate compression buffer");
+		archive_set_error(&a->archive, ENOMEM,
+		    "Can't allocate compression buffer");
 		return (ARCHIVE_FATAL);
 	}
 #else
@@ -335,7 +339,7 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 
 	/* Entries other than a regular file or a folder are skipped. */
 	type = archive_entry_filetype(entry);
-	if ((type != AE_IFREG) & (type != AE_IFDIR)) {
+	if (type != AE_IFREG && type != AE_IFDIR && type != AE_IFLNK) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 		    "Filetype not supported");
 		return ARCHIVE_FAILED;
@@ -410,8 +414,20 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 
 	/* Initialize the CRC variable and potentially the local crc32(). */
 	l->crc32 = crc32(0, NULL, 0);
-	l->compression = zip->compression;
-	l->compressed_size = 0;
+	if (type == AE_IFLNK) {
+		const char *p = archive_entry_symlink(l->entry);
+		if (p != NULL)
+			size = strlen(p);
+		else
+			size = 0;
+		zip->remaining_data_bytes = 0;
+		archive_entry_set_size(l->entry, size);
+		l->compression = COMPRESSION_STORE;
+		l->compressed_size = size;
+	} else {
+		l->compression = zip->compression;
+		l->compressed_size = 0;
+	}
 	l->next = NULL;
 	if (zip->central_directory == NULL) {
 		zip->central_directory = l;
@@ -420,22 +436,24 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 	}
 	zip->central_directory_end = l;
 
-	/* Store the offset of this header for later use in central directory. */
+	/* Store the offset of this header for later use in central
+	 * directory. */
 	l->offset = zip->written_bytes;
 
 	memset(&h, 0, sizeof(h));
 	archive_le32enc(&h.signature, ZIP_SIGNATURE_LOCAL_FILE_HEADER);
 	archive_le16enc(&h.version, ZIP_VERSION_EXTRACT);
 	archive_le16enc(&h.flags, l->flags);
-	archive_le16enc(&h.compression, zip->compression);
+	archive_le16enc(&h.compression, l->compression);
 	archive_le32enc(&h.timedate, dos_time(archive_entry_mtime(entry)));
 	archive_le16enc(&h.filename_length, (uint16_t)path_length(l->entry));
 
-	switch (zip->compression) {
+	switch (l->compression) {
 	case COMPRESSION_STORE:
-		/* Setting compressed and uncompressed sizes even when specification says
-		 * to set to zero when using data descriptors. Otherwise the end of the
-		 * data for an entry is rather difficult to find. */
+		/* Setting compressed and uncompressed sizes even when
+		 * specification says to set to zero when using data
+		 * descriptors. Otherwise the end of the data for an
+		 * entry is rather difficult to find. */
 		archive_le32enc(&h.compressed_size, size);
 		archive_le32enc(&h.uncompressed_size, size);
 		break;
@@ -448,8 +466,8 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 		zip->stream.opaque = Z_NULL;
 		zip->stream.next_out = zip->buf;
 		zip->stream.avail_out = zip->len_buf;
-		if (deflateInit2(&zip->stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
-		    -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
+		if (deflateInit2(&zip->stream, Z_DEFAULT_COMPRESSION,
+		    Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
 			archive_set_error(&a->archive, ENOMEM,
 			    "Can't init deflate compressor");
 			return (ARCHIVE_FATAL);
@@ -495,6 +513,17 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 		return (ARCHIVE_FATAL);
 	zip->written_bytes += sizeof(e);
 
+	if (type == AE_IFLNK) {
+		const unsigned char *p;
+
+		p = (const unsigned char *)archive_entry_symlink(l->entry);
+		ret = __archive_write_output(a, p, size);
+		if (ret != ARCHIVE_OK)
+			return (ARCHIVE_FATAL);
+		zip->written_bytes += size;
+		l->crc32 = crc32(l->crc32, p, size);
+	}
+
 	if (ret2 != ARCHIVE_OK)
 		return (ret2);
 	return (ARCHIVE_OK);
@@ -512,7 +541,7 @@ archive_write_zip_data(struct archive_write *a, const void *buff, size_t s)
 
 	if (s == 0) return 0;
 
-	switch (zip->compression) {
+	switch (l->compression) {
 	case COMPRESSION_STORE:
 		ret = __archive_write_output(a, buff, s);
 		if (ret != ARCHIVE_OK) return (ret);
@@ -530,7 +559,8 @@ archive_write_zip_data(struct archive_write *a, const void *buff, size_t s)
 			if (ret == Z_STREAM_ERROR)
 				return (ARCHIVE_FATAL);
 			if (zip->stream.avail_out == 0) {
-				ret = __archive_write_output(a, zip->buf, zip->len_buf);
+				ret = __archive_write_output(a, zip->buf,
+					zip->len_buf);
 				if (ret != ARCHIVE_OK)
 					return (ret);
 				l->compressed_size += zip->len_buf;
@@ -564,7 +594,7 @@ archive_write_zip_finish_entry(struct archive_write *a)
 	size_t reminder;
 #endif
 
-	switch(zip->compression) {
+	switch(l->compression) {
 	case COMPRESSION_STORE:
 		break;
 #if HAVE_ZLIB_H
@@ -614,7 +644,8 @@ archive_write_zip_close(struct archive_write *a)
 	l = zip->central_directory;
 
 	/*
-	 * Formatting central directory file header fields that are fixed for all entries.
+	 * Formatting central directory file header fields that are
+	 * fixed for all entries.
 	 * Fields not used (and therefor 0) are:
 	 *
 	 *   - comment_length
@@ -634,18 +665,23 @@ archive_write_zip_close(struct archive_write *a)
 	while (l != NULL) {
 		archive_le16enc(&h.flags, l->flags);
 		archive_le16enc(&h.compression, l->compression);
-		archive_le32enc(&h.timedate, dos_time(archive_entry_mtime(l->entry)));
+		archive_le32enc(&h.timedate,
+			dos_time(archive_entry_mtime(l->entry)));
 		archive_le32enc(&h.crc32, l->crc32);
 		archive_le32enc(&h.compressed_size, l->compressed_size);
-		archive_le32enc(&h.uncompressed_size, archive_entry_size(l->entry));
-		archive_le16enc(&h.filename_length, (uint16_t)path_length(l->entry));
+		archive_le32enc(&h.uncompressed_size,
+			archive_entry_size(l->entry));
+		archive_le16enc(&h.filename_length,
+			(uint16_t)path_length(l->entry));
 		archive_le16enc(&h.extra_length, sizeof(e));
-		archive_le16enc(&h.attributes_external[2], archive_entry_mode(l->entry));
+		archive_le16enc(&h.attributes_external[2],
+			archive_entry_mode(l->entry));
 		archive_le32enc(&h.offset, l->offset);
 
 		/* Formatting extra data. */
 		archive_le16enc(&e.time_id, ZIP_SIGNATURE_EXTRA_TIMESTAMP);
-		archive_le16enc(&e.time_size, sizeof(e.mtime) + sizeof(e.time_flag));
+		archive_le16enc(&e.time_size,
+			sizeof(e.mtime) + sizeof(e.time_flag));
 		e.time_flag[0] = 0x07;
 		archive_le32enc(&e.mtime, archive_entry_mtime(l->entry));
 		archive_le16enc(&e.unix_id, ZIP_SIGNATURE_EXTRA_NEW_UNIX);