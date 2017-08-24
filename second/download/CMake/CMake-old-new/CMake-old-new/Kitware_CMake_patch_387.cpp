@@ -1,6 +1,6 @@
 /*-
  * Copyright (c) 2003-2007 Tim Kientzle
- * Copyright (c) 2011 Michihiro NAKAJIMA
+ * Copyright (c) 2011-2012 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -210,10 +210,10 @@ static int	read_body_to_string(struct archive_read *, struct tar *,
 		    struct archive_string *, const void *h, size_t *);
 static int	solaris_sparse_parse(struct archive_read *, struct tar *,
 		    struct archive_entry *, const char *);
-static int64_t	tar_atol(const char *, unsigned);
-static int64_t	tar_atol10(const char *, unsigned);
-static int64_t	tar_atol256(const char *, unsigned);
-static int64_t	tar_atol8(const char *, unsigned);
+static int64_t	tar_atol(const char *, size_t);
+static int64_t	tar_atol10(const char *, size_t);
+static int64_t	tar_atol256(const char *, size_t);
+static int64_t	tar_atol8(const char *, size_t);
 static int	tar_read_header(struct archive_read *, struct tar *,
 		    struct archive_entry *, size_t *);
 static int	tohex(int c);
@@ -253,6 +253,7 @@ archive_read_support_format_tar(struct archive *_a)
 	    archive_read_format_tar_read_header,
 	    archive_read_format_tar_read_data,
 	    archive_read_format_tar_skip,
+	    NULL,
 	    archive_read_format_tar_cleanup);
 
 	if (r != ARCHIVE_OK)
@@ -369,7 +370,7 @@ archive_read_format_tar_options(struct archive_read *a,
 		/* Handle UTF-8 filnames as libarchive 2.x */
 		tar->compat_2x = (val != NULL)?1:0;
 		tar->init_default_conversion = tar->compat_2x;
-		ret = ARCHIVE_OK;
+		return (ARCHIVE_OK);
 	} else if (strcmp(key, "hdrcharset")  == 0) {
 		if (val == NULL || val[0] == 0)
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
@@ -383,11 +384,13 @@ archive_read_format_tar_options(struct archive_read *a,
 			else
 				ret = ARCHIVE_FATAL;
 		}
-	} else
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "tar: unknown keyword ``%s''", key);
+		return (ret);
+	}
 
-	return (ret);
+	/* Note: The "warn" return is just to inform the options
+	 * supervisor that we didn't handle it.  It will generate
+	 * a suitable error if no one used this option. */
+	return (ARCHIVE_WARN);
 }
 
 /* utility function- this exists to centralize the logic of tracking
@@ -525,56 +528,57 @@ archive_read_format_tar_read_data(struct archive_read *a,
 
 	tar = (struct tar *)(a->format->data);
 
-skip_hole:
-	/* Remove exhausted entries from sparse list. */
-	while (tar->sparse_list != NULL &&
-	    tar->sparse_list->remaining == 0) {
-		p = tar->sparse_list;
-		tar->sparse_list = p->next;
-		free(p);
-	}
+	for (;;) {
+		/* Remove exhausted entries from sparse list. */
+		while (tar->sparse_list != NULL &&
+		    tar->sparse_list->remaining == 0) {
+			p = tar->sparse_list;
+			tar->sparse_list = p->next;
+			free(p);
+		}
 
-	if (tar->entry_bytes_unconsumed) {
-		__archive_read_consume(a, tar->entry_bytes_unconsumed);
-		tar->entry_bytes_unconsumed = 0;
-	}
+		if (tar->entry_bytes_unconsumed) {
+			__archive_read_consume(a, tar->entry_bytes_unconsumed);
+			tar->entry_bytes_unconsumed = 0;
+		}
 
-	/* If we're at end of file, return EOF. */
-	if (tar->sparse_list == NULL || tar->entry_bytes_remaining == 0) {
-		if (__archive_read_consume(a, tar->entry_padding) < 0)
-			return (ARCHIVE_FATAL);
-		tar->entry_padding = 0;
-		*buff = NULL;
-		*size = 0;
-		*offset = tar->realsize;
-		return (ARCHIVE_EOF);
-	}
+		/* If we're at end of file, return EOF. */
+		if (tar->sparse_list == NULL ||
+		    tar->entry_bytes_remaining == 0) {
+			if (__archive_read_consume(a, tar->entry_padding) < 0)
+				return (ARCHIVE_FATAL);
+			tar->entry_padding = 0;
+			*buff = NULL;
+			*size = 0;
+			*offset = tar->realsize;
+			return (ARCHIVE_EOF);
+		}
 
-	*buff = __archive_read_ahead(a, 1, &bytes_read);
-	if (bytes_read < 0)
-		return (ARCHIVE_FATAL);
-	if (*buff == NULL) {
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "Truncated tar archive");
-		return (ARCHIVE_FATAL);
+		*buff = __archive_read_ahead(a, 1, &bytes_read);
+		if (bytes_read < 0)
+			return (ARCHIVE_FATAL);
+		if (*buff == NULL) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Truncated tar archive");
+			return (ARCHIVE_FATAL);
+		}
+		if (bytes_read > tar->entry_bytes_remaining)
+			bytes_read = (ssize_t)tar->entry_bytes_remaining;
+		/* Don't read more than is available in the
+		 * current sparse block. */
+		if (tar->sparse_list->remaining < bytes_read)
+			bytes_read = (ssize_t)tar->sparse_list->remaining;
+		*size = bytes_read;
+		*offset = tar->sparse_list->offset;
+		tar->sparse_list->remaining -= bytes_read;
+		tar->sparse_list->offset += bytes_read;
+		tar->entry_bytes_remaining -= bytes_read;
+		tar->entry_bytes_unconsumed = bytes_read;
+
+		if (!tar->sparse_list->hole)
+			return (ARCHIVE_OK);
+		/* Current is hole data and skip this. */
 	}
-	if (bytes_read > tar->entry_bytes_remaining)
-		bytes_read = tar->entry_bytes_remaining;
-	/* Don't read more than is available in the
-	 * current sparse block. */
-	if (tar->sparse_list->remaining < bytes_read)
-		bytes_read = tar->sparse_list->remaining;
-	*size = bytes_read;
-	*offset = tar->sparse_list->offset;
-	tar->sparse_list->remaining -= bytes_read;
-	tar->sparse_list->offset += bytes_read;
-	tar->entry_bytes_remaining -= bytes_read;
-	tar->entry_bytes_unconsumed = bytes_read;
-
-	if (tar->sparse_list->hole)
-		goto skip_hole;
-
-	return (ARCHIVE_OK);
 }
 
 static int
@@ -613,13 +617,14 @@ tar_read_header(struct archive_read *a, struct tar *tar,
 	int err;
 	const char *h;
 	const struct archive_entry_header_ustar *header;
+	const struct archive_entry_header_gnutar *gnuheader;
 
 	tar_flush_unconsumed(a, unconsumed);
 
 	/* Read 512-byte header record */
 	h = __archive_read_ahead(a, 512, &bytes);
 	if (bytes < 0)
-		return (bytes);
+		return ((int)bytes);
 	if (bytes == 0) { /* EOF at a block boundary. */
 		/* Some writers do omit the block of nulls. <sigh> */
 		return (ARCHIVE_EOF);
@@ -700,7 +705,8 @@ tar_read_header(struct archive_read *a, struct tar *tar,
 		err = header_pax_extensions(a, tar, entry, h, unconsumed);
 		break;
 	default:
-		if (memcmp(header->magic, "ustar  \0", 8) == 0) {
+		gnuheader = (const struct archive_entry_header_gnutar *)h;
+		if (memcmp(gnuheader->magic, "ustar  \0", 8) == 0) {
 			a->archive.archive_format = ARCHIVE_FORMAT_TAR_GNUTAR;
 			a->archive.archive_format_name = "GNU tar format";
 			err = header_gnutar(a, tar, entry, h, unconsumed);
@@ -749,7 +755,7 @@ tar_read_header(struct archive_read *a, struct tar *tar,
 				bytes_read = gnu_sparse_10_read(a, tar, unconsumed);
 				tar->entry_bytes_remaining -= bytes_read;
 				if (bytes_read < 0)
-					return (bytes_read);
+					return ((int)bytes_read);
 			} else {
 				archive_set_error(&a->archive,
 				    ARCHIVE_ERRNO_MISC,
@@ -784,7 +790,7 @@ checksum(struct archive_read *a, const void *h)
 	 * Test the checksum.  Note that POSIX specifies _unsigned_
 	 * bytes for this calculation.
 	 */
-	sum = tar_atol(header->checksum, sizeof(header->checksum));
+	sum = (int)tar_atol(header->checksum, sizeof(header->checksum));
 	check = 0;
 	for (i = 0; i < 148; i++)
 		check += (unsigned char)bytes[i];
@@ -845,7 +851,7 @@ header_Solaris_ACL(struct archive_read *a, struct tar *tar,
 	 * more to make sure that we don't overrun acl_text later.
 	 */
 	header = (const struct archive_entry_header_ustar *)h;
-	size = tar_atol(header->size, sizeof(header->size));
+	size = (size_t)tar_atol(header->size, sizeof(header->size));
 	err = read_body_to_string(a, tar, &(tar->acl_text), h, unconsumed);
 	if (err != ARCHIVE_OK)
 		return (err);
@@ -1019,7 +1025,7 @@ read_body_to_string(struct archive_read *a, struct tar *tar,
 	}
 
 	/* Fail if we can't make our buffer big enough. */
-	if (archive_string_ensure(as, size+1) == NULL) {
+	if (archive_string_ensure(as, (size_t)size+1) == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "No memory");
 		return (ARCHIVE_FATAL);
@@ -1028,15 +1034,15 @@ read_body_to_string(struct archive_read *a, struct tar *tar,
 	tar_flush_unconsumed(a, unconsumed);
 
 	/* Read the body into the string. */
-	*unconsumed = (size + 511) & ~ 511;
+	*unconsumed = (size_t)((size + 511) & ~ 511);
 	src = __archive_read_ahead(a, *unconsumed, NULL);
 	if (src == NULL) {
 		*unconsumed = 0;
 		return (ARCHIVE_FATAL);
 	}
-	memcpy(as->s, src, size);
+	memcpy(as->s, src, (size_t)size);
 	as->s[size] = '\0';
-	as->length = size;
+	as->length = (size_t)size;
 	return (ARCHIVE_OK);
 }
 
@@ -1066,7 +1072,8 @@ header_common(struct archive_read *a, struct tar *tar,
 		archive_string_empty(&(tar->entry_linkpath));
 
 	/* Parse out the numeric fields (all are octal) */
-	archive_entry_set_mode(entry, tar_atol(header->mode, sizeof(header->mode)));
+	archive_entry_set_mode(entry,
+		(mode_t)tar_atol(header->mode, sizeof(header->mode)));
 	archive_entry_set_uid(entry, tar_atol(header->uid, sizeof(header->uid)));
 	archive_entry_set_gid(entry, tar_atol(header->gid, sizeof(header->gid)));
 	tar->entry_bytes_remaining = tar_atol(header->size, sizeof(header->size));
@@ -1308,13 +1315,13 @@ read_mac_metadata_blob(struct archive_read *a, struct tar *tar,
 	 * Q: Is the above idea really possible?  Even
 	 * when there are GNU or pax extension entries?
 	 */
-	data = __archive_read_ahead(a, size, NULL);
+	data = __archive_read_ahead(a, (size_t)size, NULL);
 	if (data == NULL) {
 		*unconsumed = 0;
 		return (ARCHIVE_FATAL);
 	}
-	archive_entry_copy_mac_metadata(entry, data, size);
-	*unconsumed = (size + 511) & ~ 511;
+	archive_entry_copy_mac_metadata(entry, data, (size_t)size);
+	*unconsumed = (size_t)((size + 511) & ~ 511);
 	tar_flush_unconsumed(a, unconsumed);
 	return (tar_read_header(a, tar, entry, unconsumed));
 }
@@ -1422,9 +1429,9 @@ header_ustar(struct archive_read *a, struct tar *tar,
 
 	/* Parse out device numbers only for char and block specials. */
 	if (header->typeflag[0] == '3' || header->typeflag[0] == '4') {
-		archive_entry_set_rdevmajor(entry,
+		archive_entry_set_rdevmajor(entry, (dev_t)
 		    tar_atol(header->rdevmajor, sizeof(header->rdevmajor)));
-		archive_entry_set_rdevminor(entry,
+		archive_entry_set_rdevminor(entry, (dev_t)
 		    tar_atol(header->rdevminor, sizeof(header->rdevminor)));
 	}
 
@@ -1661,6 +1668,9 @@ pax_attribute(struct archive_read *a, struct tar *tar,
 	long n;
 	int err = ARCHIVE_OK, r;
 
+	if (value == NULL)
+		value = "";	/* Disable compiler warning; do not pass
+				 * NULL pointer to strlen().  */
 	switch (key[0]) {
 	case 'G':
 		/* GNU "0.0" sparse pax format. */
@@ -1707,11 +1717,11 @@ pax_attribute(struct archive_read *a, struct tar *tar,
 
 		/* GNU "1.0" sparse pax format */
 		if (strcmp(key, "GNU.sparse.major") == 0) {
-			tar->sparse_gnu_major = tar_atol10(value, strlen(value));
+			tar->sparse_gnu_major = (int)tar_atol10(value, strlen(value));
 			tar->sparse_gnu_pending = 1;
 		}
 		if (strcmp(key, "GNU.sparse.minor") == 0) {
-			tar->sparse_gnu_minor = tar_atol10(value, strlen(value));
+			tar->sparse_gnu_minor = (int)tar_atol10(value, strlen(value));
 			tar->sparse_gnu_pending = 1;
 		}
 		if (strcmp(key, "GNU.sparse.name") == 0) {
@@ -1794,20 +1804,20 @@ pax_attribute(struct archive_read *a, struct tar *tar,
 			}
 		} else if (strcmp(key, "SCHILY.devmajor") == 0) {
 			archive_entry_set_rdevmajor(entry,
-			    tar_atol10(value, strlen(value)));
+			    (dev_t)tar_atol10(value, strlen(value)));
 		} else if (strcmp(key, "SCHILY.devminor") == 0) {
 			archive_entry_set_rdevminor(entry,
-			    tar_atol10(value, strlen(value)));
+			    (dev_t)tar_atol10(value, strlen(value)));
 		} else if (strcmp(key, "SCHILY.fflags") == 0) {
 			archive_entry_copy_fflags_text(entry, value);
 		} else if (strcmp(key, "SCHILY.dev") == 0) {
 			archive_entry_set_dev(entry,
-			    tar_atol10(value, strlen(value)));
+			    (dev_t)tar_atol10(value, strlen(value)));
 		} else if (strcmp(key, "SCHILY.ino") == 0) {
 			archive_entry_set_ino(entry,
 			    tar_atol10(value, strlen(value)));
 		} else if (strcmp(key, "SCHILY.nlink") == 0) {
-			archive_entry_set_nlink(entry,
+			archive_entry_set_nlink(entry, (unsigned)
 			    tar_atol10(value, strlen(value)));
 		} else if (strcmp(key, "SCHILY.realsize") == 0) {
 			tar->realsize = tar_atol10(value, strlen(value));
@@ -2016,9 +2026,9 @@ header_gnutar(struct archive_read *a, struct tar *tar,
 
 	/* Parse out device numbers only for char and block specials */
 	if (header->typeflag[0] == '3' || header->typeflag[0] == '4') {
-		archive_entry_set_rdevmajor(entry,
+		archive_entry_set_rdevmajor(entry, (dev_t)
 		    tar_atol(header->rdevmajor, sizeof(header->rdevmajor)));
-		archive_entry_set_rdevminor(entry,
+		archive_entry_set_rdevminor(entry, (dev_t)
 		    tar_atol(header->rdevminor, sizeof(header->rdevminor)));
 	} else
 		archive_entry_set_rdev(entry, 0);
@@ -2253,7 +2263,8 @@ gnu_sparse_10_atol(struct archive_read *a, struct tar *tar,
 	 * don't require this, but they should.
 	 */
 	do {
-		bytes_read = readline(a, tar, &p, tar_min(*remaining, 100), unconsumed);
+		bytes_read = readline(a, tar, &p,
+			(ssize_t)tar_min(*remaining, 100), unconsumed);
 		if (bytes_read <= 0)
 			return (ARCHIVE_FATAL);
 		*remaining -= bytes_read;
@@ -2294,7 +2305,7 @@ gnu_sparse_10_read(struct archive_read *a, struct tar *tar, size_t *unconsumed)
 	remaining = tar->entry_bytes_remaining;
 
 	/* Parse entries. */
-	entries = gnu_sparse_10_atol(a, tar, &remaining, unconsumed);
+	entries = (int)gnu_sparse_10_atol(a, tar, &remaining, unconsumed);
 	if (entries < 0)
 		return (ARCHIVE_FATAL);
 	/* Parse the individual entries. */
@@ -2312,16 +2323,16 @@ gnu_sparse_10_read(struct archive_read *a, struct tar *tar, size_t *unconsumed)
 	}
 	/* Skip rest of block... */
 	tar_flush_unconsumed(a, unconsumed);
-	bytes_read = tar->entry_bytes_remaining - remaining;
+	bytes_read = (ssize_t)(tar->entry_bytes_remaining - remaining);
 	to_skip = 0x1ff & -bytes_read;
 	if (to_skip != __archive_read_consume(a, to_skip))
 		return (ARCHIVE_FATAL);
-	return (bytes_read + to_skip);
+	return ((ssize_t)(bytes_read + to_skip));
 }
 
 /*
  * Solaris pax extension for a sparse file. This is recorded with the
- * data and hole pairs. The way recording sparse infomation by Solaris'
+ * data and hole pairs. The way recording sparse information by Solaris'
  * pax simply indicates where data and sparse are, so the stored contents
  * consist of both data and hole.
  */
@@ -2333,6 +2344,8 @@ solaris_sparse_parse(struct archive_read *a, struct tar *tar,
 	int64_t start, end;
 	int hole = 1;
 
+	(void)entry; /* UNUSED */
+
 	end = 0;
 	if (*p == ' ')
 		p++;
@@ -2380,7 +2393,7 @@ solaris_sparse_parse(struct archive_read *a, struct tar *tar,
  * On read, this implementation supports both extensions.
  */
 static int64_t
-tar_atol(const char *p, unsigned char_cnt)
+tar_atol(const char *p, size_t char_cnt)
 {
 	/*
 	 * Technically, GNU tar considers a field to be in base-256
@@ -2397,70 +2410,55 @@ tar_atol(const char *p, unsigned char_cnt)
  * it does obey locale.
  */
 static int64_t
-tar_atol8(const char *p, unsigned char_cnt)
+tar_atol_base_n(const char *p, size_t char_cnt, int base)
 {
 	int64_t	l, limit, last_digit_limit;
-	int digit, sign, base;
+	int digit, sign;
 
-	base = 8;
 	limit = INT64_MAX / base;
 	last_digit_limit = INT64_MAX % base;
 
-	while (*p == ' ' || *p == '\t')
+	/* the pointer will not be dereferenced if char_cnt is zero
+	 * due to the way the && operator is evaulated.
+	 */
+	while (char_cnt != 0 && (*p == ' ' || *p == '\t')) {
 		p++;
-	if (*p == '-') {
+		char_cnt--;
+	}
+
+	sign = 1;
+	if (char_cnt != 0 && *p == '-') {
 		sign = -1;
 		p++;
-	} else
-		sign = 1;
+		char_cnt--;
+	}
 
 	l = 0;
-	digit = *p - '0';
-	while (digit >= 0 && digit < base  && char_cnt-- > 0) {
-		if (l>limit || (l == limit && digit > last_digit_limit)) {
-			l = INT64_MAX; /* Truncate on overflow. */
-			break;
+	if (char_cnt != 0) {
+		digit = *p - '0';
+		while (digit >= 0 && digit < base  && char_cnt != 0) {
+			if (l>limit || (l == limit && digit > last_digit_limit)) {
+				l = INT64_MAX; /* Truncate on overflow. */
+				break;
+			}
+			l = (l * base) + digit;
+			digit = *++p - '0';
+			char_cnt--;
 		}
-		l = (l * base) + digit;
-		digit = *++p - '0';
 	}
 	return (sign < 0) ? -l : l;
 }
 
-/*
- * Note that this implementation does not (and should not!) obey
- * locale settings; you cannot simply substitute strtol here, since
- * it does obey locale.
- */
 static int64_t
-tar_atol10(const char *p, unsigned char_cnt)
+tar_atol8(const char *p, size_t char_cnt)
 {
-	int64_t l, limit, last_digit_limit;
-	int base, digit, sign;
-
-	base = 10;
-	limit = INT64_MAX / base;
-	last_digit_limit = INT64_MAX % base;
-
-	while (*p == ' ' || *p == '\t')
-		p++;
-	if (*p == '-') {
-		sign = -1;
-		p++;
-	} else
-		sign = 1;
+	return tar_atol_base_n(p, char_cnt, 8);
+}
 
-	l = 0;
-	digit = *p - '0';
-	while (digit >= 0 && digit < base  && char_cnt-- > 0) {
-		if (l > limit || (l == limit && digit > last_digit_limit)) {
-			l = INT64_MAX; /* Truncate on overflow. */
-			break;
-		}
-		l = (l * base) + digit;
-		digit = *++p - '0';
-	}
-	return (sign < 0) ? -l : l;
+static int64_t
+tar_atol10(const char *p, size_t char_cnt)
+{
+	return tar_atol_base_n(p, char_cnt, 10);
 }
 
 /*
@@ -2469,7 +2467,7 @@ tar_atol10(const char *p, unsigned char_cnt)
  * ignored.
  */
 static int64_t
-tar_atol256(const char *_p, unsigned char_cnt)
+tar_atol256(const char *_p, size_t char_cnt)
 {
 	int64_t	l, upper_limit, lower_limit;
 	const unsigned char *p = (const unsigned char *)_p;