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
@@ -2412,9 +2450,10 @@ tar_atol(const char *p, size_t char_cnt)
 static int64_t
 tar_atol_base_n(const char *p, size_t char_cnt, int base)
 {
-	int64_t	l, limit, last_digit_limit;
+	int64_t	l, maxval, limit, last_digit_limit;
 	int digit, sign;
 
+	maxval = INT64_MAX;
 	limit = INT64_MAX / base;
 	last_digit_limit = INT64_MAX % base;
 
@@ -2431,15 +2470,18 @@ tar_atol_base_n(const char *p, size_t char_cnt, int base)
 		sign = -1;
 		p++;
 		char_cnt--;
+
+		maxval = INT64_MIN;
+		limit = -(INT64_MIN / base);
+		last_digit_limit = INT64_MIN % base;
 	}
 
 	l = 0;
 	if (char_cnt != 0) {
 		digit = *p - '0';
 		while (digit >= 0 && digit < base  && char_cnt != 0) {
 			if (l>limit || (l == limit && digit > last_digit_limit)) {
-				l = INT64_MAX; /* Truncate on overflow. */
-				break;
+				return maxval; /* Truncate on overflow. */
 			}
 			l = (l * base) + digit;
 			digit = *++p - '0';
@@ -2462,36 +2504,56 @@ tar_atol10(const char *p, size_t char_cnt)
 }
 
 /*
- * Parse a base-256 integer.  This is just a straight signed binary
- * value in big-endian order, except that the high-order bit is
- * ignored.
+ * Parse a base-256 integer.  This is just a variable-length
+ * twos-complement signed binary value in big-endian order, except
+ * that the high-order bit is ignored.  The values here can be up to
+ * 12 bytes, so we need to be careful about overflowing 64-bit
+ * (8-byte) integers.
+ *
+ * This code unashamedly assumes that the local machine uses 8-bit
+ * bytes and twos-complement arithmetic.
  */
 static int64_t
 tar_atol256(const char *_p, size_t char_cnt)
 {
-	int64_t	l, upper_limit, lower_limit;
+	uint64_t l;
 	const unsigned char *p = (const unsigned char *)_p;
+	unsigned char c, neg;
+
+	/* Extend 7-bit 2s-comp to 8-bit 2s-comp, decide sign. */
+	c = *p;
+	if (c & 0x40) {
+		neg = 0xff;
+		c |= 0x80;
+		l = ~ARCHIVE_LITERAL_ULL(0);
+	} else {
+		neg = 0;
+		c &= 0x7f;
+		l = 0;
+	}
 
-	upper_limit = INT64_MAX / 256;
-	lower_limit = INT64_MIN / 256;
+	/* If more than 8 bytes, check that we can ignore
+	 * high-order bits without overflow. */
+	while (char_cnt > sizeof(int64_t)) {
+		--char_cnt;
+		if (c != neg)
+			return neg ? INT64_MIN : INT64_MAX;
+		c = *++p;
+	}
 
-	/* Pad with 1 or 0 bits, depending on sign. */
-	if ((0x40 & *p) == 0x40)
-		l = (int64_t)-1;
-	else
-		l = 0;
-	l = (l << 6) | (0x3f & *p++);
+	/* c is first byte that fits; if sign mismatch, return overflow */
+	if ((c ^ neg) & 0x80) {
+		return neg ? INT64_MIN : INT64_MAX;
+	}
+
+	/* Accumulate remaining bytes. */
 	while (--char_cnt > 0) {
-		if (l > upper_limit) {
-			l = INT64_MAX; /* Truncate on overflow */
-			break;
-		} else if (l < lower_limit) {
-			l = INT64_MIN;
-			break;
-		}
-		l = (l << 8) | (0xff & (int64_t)*p++);
+		l = (l << 8) | c;
+		c = *++p;
 	}
-	return (l);
+	l = (l << 8) | c;
+	/* Return signed twos-complement value. */
+	return (int64_t)(l);
 }
 
 /*