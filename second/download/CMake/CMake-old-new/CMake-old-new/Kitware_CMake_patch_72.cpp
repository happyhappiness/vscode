@@ -1,6 +1,7 @@
 /*-
  * Copyright (c) 2003-2007 Tim Kientzle
  * Copyright (c) 2011-2012 Michihiro NAKAJIMA
+ * Copyright (c) 2016 Martin Matuska
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -136,6 +137,7 @@ struct tar {
 	int64_t			 entry_padding;
 	int64_t 		 entry_bytes_unconsumed;
 	int64_t			 realsize;
+	int			 sparse_allowed;
 	struct sparse_block	*sparse_list;
 	struct sparse_block	*sparse_last;
 	int64_t			 sparse_offset;
@@ -202,9 +204,14 @@ static int	archive_read_format_tar_read_header(struct archive_read *,
 		    struct archive_entry *);
 static int	checksum(struct archive_read *, const void *);
 static int 	pax_attribute(struct archive_read *, struct tar *,
-		    struct archive_entry *, const char *key, const char *value);
+		    struct archive_entry *, const char *key, const char *value,
+		    size_t value_length);
+static int	pax_attribute_acl(struct archive_read *, struct tar *,
+		    struct archive_entry *, const char *, int);
+static int	pax_attribute_xattr(struct archive_entry *, const char *,
+		    const char *);
 static int 	pax_header(struct archive_read *, struct tar *,
-		    struct archive_entry *, char *attr);
+		    struct archive_entry *, struct archive_string *);
 static void	pax_time(const char *, int64_t *sec, long *nanos);
 static ssize_t	readline(struct archive_read *, struct tar *, const char **,
 		    ssize_t limit, size_t *);
@@ -293,6 +300,57 @@ archive_read_format_tar_cleanup(struct archive_read *a)
 	return (ARCHIVE_OK);
 }
 
+/*
+ * Validate number field
+ *
+ * This has to be pretty lenient in order to accommodate the enormous
+ * variety of tar writers in the world:
+ *  = POSIX (IEEE Std 1003.1-1988) ustar requires octal values with leading
+ *    zeros and allows fields to be terminated with space or null characters
+ *  = Many writers use different termination (in particular, libarchive
+ *    omits terminator bytes to squeeze one or two more digits)
+ *  = Many writers pad with space and omit leading zeros
+ *  = GNU tar and star write base-256 values if numbers are too
+ *    big to be represented in octal
+ *
+ *  Examples of specific tar headers that we should support:
+ *  = Perl Archive::Tar terminates uid, gid, devminor and devmajor with two
+ *    null bytes, pads size with spaces and other numeric fields with zeroes
+ *  = plexus-archiver prior to 2.6.3 (before switching to commons-compress)
+ *    may have uid and gid fields filled with spaces without any octal digits
+ *    at all and pads all numeric fields with spaces
+ *
+ * This should tolerate all variants in use.  It will reject a field
+ * where the writer just left garbage after a trailing NUL.
+ */
+static int
+validate_number_field(const char* p_field, size_t i_size)
+{
+	unsigned char marker = (unsigned char)p_field[0];
+	if (marker == 128 || marker == 255 || marker == 0) {
+		/* Base-256 marker, there's nothing we can check. */
+		return 1;
+	} else {
+		/* Must be octal */
+		size_t i = 0;
+		/* Skip any leading spaces */
+		while (i < i_size && p_field[i] == ' ') {
+			++i;
+		}
+		/* Skip octal digits. */
+		while (i < i_size && p_field[i] >= '0' && p_field[i] <= '7') {
+			++i;
+		}
+		/* Any remaining characters must be space or NUL padding. */
+		while (i < i_size) {
+			if (p_field[i] != ' ' && p_field[i] != 0) {
+				return 0;
+			}
+			++i;
+		}
+		return 1;
+	}
+}
 
 static int
 archive_read_format_tar_bid(struct archive_read *a, int best_bid)
@@ -345,23 +403,19 @@ archive_read_format_tar_bid(struct archive_read *a, int best_bid)
 		return (0);
 	bid += 2;  /* 6 bits of variation in an 8-bit field leaves 2 bits. */
 
-	/* Sanity check: Look at first byte of mode field. */
-	switch (255 & (unsigned)header->mode[0]) {
-	case 0: case 255:
-		/* Base-256 value: No further verification possible! */
-		break;
-	case ' ': /* Not recommended, but not illegal, either. */
-		break;
-	case '0': case '1': case '2': case '3':
-	case '4': case '5': case '6': case '7':
-		/* Octal Value. */
-		/* TODO: Check format of remainder of this field. */
-		break;
-	default:
-		/* Not a valid mode; bail out here. */
-		return (0);
+	/*
+	 * Check format of mode/uid/gid/mtime/size/rdevmajor/rdevminor fields.
+	 */
+	if (bid > 0 && (
+	    validate_number_field(header->mode, sizeof(header->mode)) == 0
+	    || validate_number_field(header->uid, sizeof(header->uid)) == 0
+	    || validate_number_field(header->gid, sizeof(header->gid)) == 0
+	    || validate_number_field(header->mtime, sizeof(header->mtime)) == 0
+	    || validate_number_field(header->size, sizeof(header->size)) == 0
+	    || validate_number_field(header->rdevmajor, sizeof(header->rdevmajor)) == 0
+	    || validate_number_field(header->rdevminor, sizeof(header->rdevminor)) == 0)) {
+		bid = 0;
 	}
-	/* TODO: Sanity test uid/gid/size/mtime/rdevmajor/rdevminor fields. */
 
 	return (bid);
 }
@@ -375,7 +429,7 @@ archive_read_format_tar_options(struct archive_read *a,
 
 	tar = (struct tar *)(a->format->data);
 	if (strcmp(key, "compat-2x")  == 0) {
-		/* Handle UTF-8 filnames as libarchive 2.x */
+		/* Handle UTF-8 filenames as libarchive 2.x */
 		tar->compat_2x = (val != NULL && val[0] != 0);
 		tar->init_default_conversion = tar->compat_2x;
 		return (ARCHIVE_OK);
@@ -793,9 +847,9 @@ tar_read_header(struct archive_read *a, struct tar *tar,
 				tar->sparse_gnu_pending = 0;
 				/* Read initial sparse map. */
 				bytes_read = gnu_sparse_10_read(a, tar, unconsumed);
-				tar->entry_bytes_remaining -= bytes_read;
 				if (bytes_read < 0)
 					return ((int)bytes_read);
+				tar->entry_bytes_remaining -= bytes_read;
 			} else {
 				archive_set_error(&a->archive,
 				    ARCHIVE_ERRNO_MISC,
@@ -890,7 +944,7 @@ header_Solaris_ACL(struct archive_read *a, struct tar *tar,
 {
 	const struct archive_entry_header_ustar *header;
 	size_t size;
-	int err;
+	int err, acl_type;
 	int64_t type;
 	char *acl, *p;
 
@@ -935,11 +989,12 @@ header_Solaris_ACL(struct archive_read *a, struct tar *tar,
 	switch ((int)type & ~0777777) {
 	case 01000000:
 		/* POSIX.1e ACL */
+		acl_type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
 		break;
 	case 03000000:
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "Solaris NFSv4 ACLs not supported");
-		return (ARCHIVE_WARN);
+		/* NFSv4 ACL */
+		acl_type = ARCHIVE_ENTRY_ACL_TYPE_NFS4;
+		break;
 	default:
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 		    "Malformed Solaris ACL attribute (unsupported type %o)",
@@ -968,8 +1023,8 @@ header_Solaris_ACL(struct archive_read *a, struct tar *tar,
 			return (ARCHIVE_FATAL);
 	}
 	archive_strncpy(&(tar->localname), acl, p - acl);
-	err = archive_acl_parse_l(archive_entry_acl(entry),
-	    tar->localname.s, ARCHIVE_ENTRY_ACL_TYPE_ACCESS, tar->sconv_acl);
+	err = archive_acl_from_text_l(archive_entry_acl(entry),
+	    tar->localname.s, acl_type, tar->sconv_acl);
 	if (err != ARCHIVE_OK) {
 		if (errno == ENOMEM) {
 			archive_set_error(&a->archive, ENOMEM,
@@ -1128,8 +1183,15 @@ header_common(struct archive_read *a, struct tar *tar,
 	if (tar->entry_bytes_remaining < 0) {
 		tar->entry_bytes_remaining = 0;
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "Tar entry has negative size?");
-		err = ARCHIVE_WARN;
+		    "Tar entry has negative size");
+		return (ARCHIVE_FATAL);
+	}
+	if (tar->entry_bytes_remaining == INT64_MAX) {
+		/* Note: tar_atol returns INT64_MAX on overflow */
+		tar->entry_bytes_remaining = 0;
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Tar entry size overflow");
+		return (ARCHIVE_FATAL);
 	}
 	tar->realsize = tar->entry_bytes_remaining;
 	archive_entry_set_size(entry, tar->entry_bytes_remaining);
@@ -1264,6 +1326,14 @@ header_common(struct archive_read *a, struct tar *tar,
 		 * sparse information in the extended area.
 		 */
 		/* FALLTHROUGH */
+	case '0':
+		/*
+		 * Enable sparse file "read" support only for regular
+		 * files and explicit GNU sparse files.  However, we
+		 * don't allow non-standard file types to be sparse.
+		 */
+		tar->sparse_allowed = 1;
+		/* FALLTHROUGH */
 	default: /* Regular file  and non-standard types */
 		/*
 		 * Per POSIX: non-recognized types should always be
@@ -1415,7 +1485,7 @@ header_pax_extensions(struct archive_read *a, struct tar *tar,
 	 * and then skip any fields in the standard header that were
 	 * defined in the pax header.
 	 */
-	err2 = pax_header(a, tar, entry, tar->pax_header.s);
+	err2 = pax_header(a, tar, entry, &tar->pax_header);
 	err =  err_combine(err, err2);
 	tar->entry_padding = 0x1ff & (-tar->entry_bytes_remaining);
 	return (err);
@@ -1496,16 +1566,17 @@ header_ustar(struct archive_read *a, struct tar *tar,
  */
 static int
 pax_header(struct archive_read *a, struct tar *tar,
-    struct archive_entry *entry, char *attr)
+    struct archive_entry *entry, struct archive_string *in_as)
 {
-	size_t attr_length, l, line_length;
+	size_t attr_length, l, line_length, value_length;
 	char *p;
 	char *key, *value;
 	struct archive_string *as;
 	struct archive_string_conv *sconv;
 	int err, err2;
+	char *attr = in_as->s;
 
-	attr_length = strlen(attr);
+	attr_length = in_as->length;
 	tar->pax_hdrcharset_binary = 0;
 	archive_string_empty(&(tar->entry_gname));
 	archive_string_empty(&(tar->entry_linkpath));
@@ -1570,11 +1641,13 @@ pax_header(struct archive_read *a, struct tar *tar,
 		}
 		*p = '\0';
 
-		/* Identify null-terminated 'value' portion. */
 		value = p + 1;
 
+		/* Some values may be binary data */
+		value_length = attr + line_length - 1 - value;
+
 		/* Identify this attribute and set it in the entry. */
-		err2 = pax_attribute(a, tar, entry, key, value);
+		err2 = pax_attribute(a, tar, entry, key, value, value_length);
 		if (err2 == ARCHIVE_FATAL)
 			return (err2);
 		err = err_combine(err, err2);
@@ -1695,6 +1768,66 @@ pax_attribute_xattr(struct archive_entry *entry,
 	return 0;
 }
 
+static int
+pax_attribute_schily_xattr(struct archive_entry *entry,
+	const char *name, const char *value, size_t value_length)
+{
+	if (strlen(name) < 14 || (memcmp(name, "SCHILY.xattr.", 13)) != 0)
+		return 1;
+
+	name += 13;
+
+	archive_entry_xattr_add_entry(entry, name, value, value_length);
+
+	return 0;
+}
+
+static int
+pax_attribute_acl(struct archive_read *a, struct tar *tar,
+    struct archive_entry *entry, const char *value, int type)
+{
+	int r;
+	const char* errstr;
+
+	switch (type) {
+	case ARCHIVE_ENTRY_ACL_TYPE_ACCESS:
+		errstr = "SCHILY.acl.access";
+		break;
+	case ARCHIVE_ENTRY_ACL_TYPE_DEFAULT:
+		errstr = "SCHILY.acl.default";
+		break;
+	case ARCHIVE_ENTRY_ACL_TYPE_NFS4:
+		errstr = "SCHILY.acl.ace";
+		break;
+	default:
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Unknown ACL type: %d", type);
+		return(ARCHIVE_FATAL);
+	}
+
+	if (tar->sconv_acl == NULL) {
+		tar->sconv_acl =
+		    archive_string_conversion_from_charset(
+			&(a->archive), "UTF-8", 1);
+		if (tar->sconv_acl == NULL)
+			return (ARCHIVE_FATAL);
+	}
+
+	r = archive_acl_from_text_l(archive_entry_acl(entry), value, type,
+	    tar->sconv_acl);
+	if (r != ARCHIVE_OK) {
+		if (r == ARCHIVE_FATAL) {
+			archive_set_error(&a->archive, ENOMEM,
+			    "%s %s", "Can't allocate memory for ",
+			    errstr);
+			return (r);
+		}
+		archive_set_error(&a->archive,
+		    ARCHIVE_ERRNO_MISC, "%s %s", "Parse error: ", errstr);
+	}
+	return (r);
+}
+
 /*
  * Parse a single key=value attribute.  key/value pointers are
  * assumed to point into reasonably long-lived storage.
@@ -1710,7 +1843,7 @@ pax_attribute_xattr(struct archive_entry *entry,
  */
 static int
 pax_attribute(struct archive_read *a, struct tar *tar,
-    struct archive_entry *entry, const char *key, const char *value)
+    struct archive_entry *entry, const char *key, const char *value, size_t value_length)
 {
 	int64_t s;
 	long n;
@@ -1721,6 +1854,14 @@ pax_attribute(struct archive_read *a, struct tar *tar,
 				 * NULL pointer to strlen().  */
 	switch (key[0]) {
 	case 'G':
+		/* Reject GNU.sparse.* headers on non-regular files. */
+		if (strncmp(key, "GNU.sparse", 10) == 0 &&
+		    !tar->sparse_allowed) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Non-regular file cannot be sparse");
+			return (ARCHIVE_FATAL);
+		}
+
 		/* GNU "0.0" sparse pax format. */
 		if (strcmp(key, "GNU.sparse.numblocks") == 0) {
 			tar->sparse_offset = -1;
@@ -1803,53 +1944,20 @@ pax_attribute(struct archive_read *a, struct tar *tar,
 	case 'S':
 		/* We support some keys used by the "star" archiver */
 		if (strcmp(key, "SCHILY.acl.access") == 0) {
-			if (tar->sconv_acl == NULL) {
-				tar->sconv_acl =
-				    archive_string_conversion_from_charset(
-					&(a->archive), "UTF-8", 1);
-				if (tar->sconv_acl == NULL)
-					return (ARCHIVE_FATAL);
-			}
-
-			r = archive_acl_parse_l(archive_entry_acl(entry),
-			    value, ARCHIVE_ENTRY_ACL_TYPE_ACCESS,
-			    tar->sconv_acl);
-			if (r != ARCHIVE_OK) {
-				err = r;
-				if (err == ARCHIVE_FATAL) {
-					archive_set_error(&a->archive, ENOMEM,
-					    "Can't allocate memory for "
-					    "SCHILY.acl.access");
-					return (err);
-				}
-				archive_set_error(&a->archive,
-				    ARCHIVE_ERRNO_MISC,
-				    "Parse error: SCHILY.acl.access");
-			}
+			r = pax_attribute_acl(a, tar, entry, value,
+			    ARCHIVE_ENTRY_ACL_TYPE_ACCESS);
+			if (r == ARCHIVE_FATAL)
+				return (r);
 		} else if (strcmp(key, "SCHILY.acl.default") == 0) {
-			if (tar->sconv_acl == NULL) {
-				tar->sconv_acl =
-				    archive_string_conversion_from_charset(
-					&(a->archive), "UTF-8", 1);
-				if (tar->sconv_acl == NULL)
-					return (ARCHIVE_FATAL);
-			}
-
-			r = archive_acl_parse_l(archive_entry_acl(entry),
-			    value, ARCHIVE_ENTRY_ACL_TYPE_DEFAULT,
-			    tar->sconv_acl);
-			if (r != ARCHIVE_OK) {
-				err = r;
-				if (err == ARCHIVE_FATAL) {
-					archive_set_error(&a->archive, ENOMEM,
-					    "Can't allocate memory for "
-					    "SCHILY.acl.default");
-					return (err);
-				}
-				archive_set_error(&a->archive,
-				    ARCHIVE_ERRNO_MISC,
-				    "Parse error: SCHILY.acl.default");
-			}
+			r = pax_attribute_acl(a, tar, entry, value,
+			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT);
+			if (r == ARCHIVE_FATAL)
+				return (r);
+		} else if (strcmp(key, "SCHILY.acl.ace") == 0) {
+			r = pax_attribute_acl(a, tar, entry, value,
+			    ARCHIVE_ENTRY_ACL_TYPE_NFS4);
+			if (r == ARCHIVE_FATAL)
+				return (r);
 		} else if (strcmp(key, "SCHILY.devmajor") == 0) {
 			archive_entry_set_rdevmajor(entry,
 			    (dev_t)tar_atol10(value, strlen(value)));
@@ -1870,6 +1978,9 @@ pax_attribute(struct archive_read *a, struct tar *tar,
 		} else if (strcmp(key, "SCHILY.realsize") == 0) {
 			tar->realsize = tar_atol10(value, strlen(value));
 			archive_entry_set_size(entry, tar->realsize);
+		} else if (strncmp(key, "SCHILY.xattr.", 13) == 0) {
+			pax_attribute_schily_xattr(entry, key, value,
+			    value_length);
 		} else if (strcmp(key, "SUN.holesdata") == 0) {
 			/* A Solaris extension for sparse. */
 			r = solaris_sparse_parse(a, tar, entry, value);
@@ -2116,12 +2227,11 @@ gnu_add_sparse_entry(struct archive_read *a, struct tar *tar,
 {
 	struct sparse_block *p;
 
-	p = (struct sparse_block *)malloc(sizeof(*p));
+	p = (struct sparse_block *)calloc(1, sizeof(*p));
 	if (p == NULL) {
 		archive_set_error(&a->archive, ENOMEM, "Out of memory");
 		return (ARCHIVE_FATAL);
 	}
-	memset(p, 0, sizeof(*p));
 	if (tar->sparse_last != NULL)
 		tar->sparse_last->next = p;
 	else
@@ -2377,6 +2487,9 @@ gnu_sparse_10_read(struct archive_read *a, struct tar *tar, size_t *unconsumed)
 	tar_flush_unconsumed(a, unconsumed);
 	bytes_read = (ssize_t)(tar->entry_bytes_remaining - remaining);
 	to_skip = 0x1ff & -bytes_read;
+	/* Fail if tar->entry_bytes_remaing would get negative */
+	if (to_skip > remaining)
+		return (ARCHIVE_FATAL);
 	if (to_skip != __archive_read_consume(a, to_skip))
 		return (ARCHIVE_FATAL);
 	return ((ssize_t)(bytes_read + to_skip));
@@ -2472,7 +2585,7 @@ tar_atol_base_n(const char *p, size_t char_cnt, int base)
 	last_digit_limit = INT64_MAX % base;
 
 	/* the pointer will not be dereferenced if char_cnt is zero
-	 * due to the way the && operator is evaulated.
+	 * due to the way the && operator is evaluated.
 	 */
 	while (char_cnt != 0 && (*p == ' ' || *p == '\t')) {
 		p++;