@@ -151,6 +151,8 @@ struct tar {
 	struct archive_string_conv *sconv_default;
 	int			 init_default_conversion;
 	int			 compat_2x;
+	int			 process_mac_extensions;
+	int			 read_concatenated_archives;
 };
 
 static int	archive_block_is_null(const char *p);
@@ -241,6 +243,10 @@ archive_read_support_format_tar(struct archive *_a)
 	    ARCHIVE_STATE_NEW, "archive_read_support_format_tar");
 
 	tar = (struct tar *)calloc(1, sizeof(*tar));
+#ifdef HAVE_COPYFILE_H
+	/* Set this by default on Mac OS. */
+	tar->process_mac_extensions = 1;
+#endif
 	if (tar == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate tar data");
@@ -254,7 +260,9 @@ archive_read_support_format_tar(struct archive *_a)
 	    archive_read_format_tar_read_data,
 	    archive_read_format_tar_skip,
 	    NULL,
-	    archive_read_format_tar_cleanup);
+	    archive_read_format_tar_cleanup,
+	    NULL,
+	    NULL);
 
 	if (r != ARCHIVE_OK)
 		free(tar);
@@ -368,7 +376,7 @@ archive_read_format_tar_options(struct archive_read *a,
 	tar = (struct tar *)(a->format->data);
 	if (strcmp(key, "compat-2x")  == 0) {
 		/* Handle UTF-8 filnames as libarchive 2.x */
-		tar->compat_2x = (val != NULL)?1:0;
+		tar->compat_2x = (val != NULL && val[0] != 0);
 		tar->init_default_conversion = tar->compat_2x;
 		return (ARCHIVE_OK);
 	} else if (strcmp(key, "hdrcharset")  == 0) {
@@ -385,6 +393,12 @@ archive_read_format_tar_options(struct archive_read *a,
 				ret = ARCHIVE_FATAL;
 		}
 		return (ret);
+	} else if (strcmp(key, "mac-ext") == 0) {
+		tar->process_mac_extensions = (val != NULL && val[0] != 0);
+		return (ARCHIVE_OK);
+	} else if (strcmp(key, "read_concatenated_archives") == 0) {
+		tar->read_concatenated_archives = (val != NULL && val[0] != 0);
+		return (ARCHIVE_OK);
 	}
 
 	/* Note: The "warn" return is just to inform the options
@@ -397,7 +411,7 @@ archive_read_format_tar_options(struct archive_read *a,
  * how much unconsumed data we have floating around, and to consume
  * anything outstanding since we're going to do read_aheads
  */
-static void 
+static void
 tar_flush_unconsumed(struct archive_read *a, size_t *unconsumed)
 {
 	if (*unconsumed) {
@@ -590,7 +604,7 @@ archive_read_format_tar_skip(struct archive_read *a)
 	tar = (struct tar *)(a->format->data);
 
 	bytes_skipped = __archive_read_consume(a,
-	    tar->entry_bytes_remaining + tar->entry_padding + 
+	    tar->entry_bytes_remaining + tar->entry_padding +
 	    tar->entry_bytes_unconsumed);
 	if (bytes_skipped < 0)
 		return (ARCHIVE_FATAL);
@@ -619,36 +633,50 @@ tar_read_header(struct archive_read *a, struct tar *tar,
 	const struct archive_entry_header_ustar *header;
 	const struct archive_entry_header_gnutar *gnuheader;
 
-	tar_flush_unconsumed(a, unconsumed);
+	/* Loop until we find a workable header record. */
+	for (;;) {
+		tar_flush_unconsumed(a, unconsumed);
 
-	/* Read 512-byte header record */
-	h = __archive_read_ahead(a, 512, &bytes);
-	if (bytes < 0)
-		return ((int)bytes);
-	if (bytes == 0) { /* EOF at a block boundary. */
-		/* Some writers do omit the block of nulls. <sigh> */
-		return (ARCHIVE_EOF);
-	}
-	if (bytes < 512) {  /* Short block at EOF; this is bad. */
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
-		    "Truncated tar archive");
-		return (ARCHIVE_FATAL);
-	}
-	*unconsumed = 512;
+		/* Read 512-byte header record */
+		h = __archive_read_ahead(a, 512, &bytes);
+		if (bytes < 0)
+			return ((int)bytes);
+		if (bytes == 0) { /* EOF at a block boundary. */
+			/* Some writers do omit the block of nulls. <sigh> */
+			return (ARCHIVE_EOF);
+		}
+		if (bytes < 512) {  /* Short block at EOF; this is bad. */
+			archive_set_error(&a->archive,
+			    ARCHIVE_ERRNO_FILE_FORMAT,
+			    "Truncated tar archive");
+			return (ARCHIVE_FATAL);
+		}
+		*unconsumed = 512;
 
-	/* Check for end-of-archive mark. */
-	if (h[0] == 0 && archive_block_is_null(h)) {
-		/* Try to consume a second all-null record, as well. */
-		tar_flush_unconsumed(a, unconsumed);
-		h = __archive_read_ahead(a, 512, NULL);
-		if (h != NULL)
-			__archive_read_consume(a, 512);
-		archive_clear_error(&a->archive);
+		/* Header is workable if it's not an end-of-archive mark. */
+		if (h[0] != 0 || !archive_block_is_null(h))
+			break;
+
+		/* Ensure format is set for archives with only null blocks. */
 		if (a->archive.archive_format_name == NULL) {
 			a->archive.archive_format = ARCHIVE_FORMAT_TAR;
 			a->archive.archive_format_name = "tar";
 		}
-		return (ARCHIVE_EOF);
+
+		if (!tar->read_concatenated_archives) {
+			/* Try to consume a second all-null record, as well. */
+			tar_flush_unconsumed(a, unconsumed);
+			h = __archive_read_ahead(a, 512, NULL);
+			if (h != NULL && h[0] == 0 && archive_block_is_null(h))
+				__archive_read_consume(a, 512);
+			archive_clear_error(&a->archive);
+			return (ARCHIVE_EOF);
+		}
+
+		/*
+		 * We're reading concatenated archives, ignore this block and
+		 * loop to get the next.
+		 */
 	}
 
 	/*
@@ -683,6 +711,8 @@ tar_read_header(struct archive_read *a, struct tar *tar,
 		a->archive.archive_format = ARCHIVE_FORMAT_TAR_PAX_INTERCHANGE;
 		a->archive.archive_format_name = "POSIX pax interchange format";
 		err = header_pax_global(a, tar, entry, h, unconsumed);
+		if (err == ARCHIVE_EOF)
+			return (err);
 		break;
 	case 'K': /* Long link name (GNU tar, others) */
 		err = header_longlink(a, tar, entry, h, unconsumed);
@@ -735,9 +765,9 @@ tar_read_header(struct archive_read *a, struct tar *tar,
 	 * extensions for both the AppleDouble extension entry and the
 	 * regular entry.
 	 */
-	/* TODO: Should this be disabled on non-Mac platforms? */
 	if ((err == ARCHIVE_WARN || err == ARCHIVE_OK) &&
-	    tar->header_recursion_depth == 0) {
+	    tar->header_recursion_depth == 0 &&
+	    tar->process_mac_extensions) {
 		int err2 = read_mac_metadata_blob(a, tar, entry, h, unconsumed);
 		if (err2 < err)
 			err = err2;
@@ -780,12 +810,20 @@ checksum(struct archive_read *a, const void *h)
 {
 	const unsigned char *bytes;
 	const struct archive_entry_header_ustar	*header;
-	int check, i, sum;
+	int check, sum;
+	size_t i;
 
 	(void)a; /* UNUSED */
 	bytes = (const unsigned char *)h;
 	header = (const struct archive_entry_header_ustar *)h;
 
+	/* Checksum field must hold an octal number */
+	for (i = 0; i < sizeof(header->checksum); ++i) {
+		char c = header->checksum[i];
+		if (c != ' ' && c != '\0' && (c < '0' || c > '7'))
+			return 0;
+	}
+
 	/*
 	 * Test the checksum.  Note that POSIX specifies _unsigned_
 	 * bytes for this calculation.
@@ -1277,7 +1315,7 @@ read_mac_metadata_blob(struct archive_read *a, struct tar *tar,
 			if (wp[0] == '/' && wp[1] != L'\0')
 				wname = wp + 1;
 		}
-		/* 
+		/*
 		 * If last path element starts with "._", then
 		 * this is a Mac extension.
 		 */
@@ -1292,7 +1330,7 @@ read_mac_metadata_blob(struct archive_read *a, struct tar *tar,
 			if (p[0] == '/' && p[1] != '\0')
 				name = p + 1;
 		}
-		/* 
+		/*
 		 * If last path element starts with "._", then
 		 * this is a Mac extension.
 		 */