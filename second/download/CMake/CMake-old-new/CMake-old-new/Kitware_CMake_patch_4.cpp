@@ -130,9 +130,7 @@ static ssize_t	readline(struct archive_read *, struct mtree *, char **, ssize_t)
 static int	skip(struct archive_read *a);
 static int	read_header(struct archive_read *,
 		    struct archive_entry *);
-static int64_t	mtree_atol10(char **);
-static int64_t	mtree_atol8(char **);
-static int64_t	mtree_atol(char **);
+static int64_t	mtree_atol(char **, int base);
 
 /*
  * There's no standard for TIME_T_MAX/TIME_T_MIN.  So we compute them
@@ -399,41 +397,41 @@ bid_keycmp(const char *p, const char *key, ssize_t len)
 static int
 bid_keyword(const char *p,  ssize_t len)
 {
-	static const char *keys_c[] = {
+	static const char * const keys_c[] = {
 		"content", "contents", "cksum", NULL
 	};
-	static const char *keys_df[] = {
+	static const char * const keys_df[] = {
 		"device", "flags", NULL
 	};
-	static const char *keys_g[] = {
+	static const char * const keys_g[] = {
 		"gid", "gname", NULL
 	};
-	static const char *keys_il[] = {
+	static const char * const keys_il[] = {
 		"ignore", "inode", "link", NULL
 	};
-	static const char *keys_m[] = {
+	static const char * const keys_m[] = {
 		"md5", "md5digest", "mode", NULL
 	};
-	static const char *keys_no[] = {
+	static const char * const keys_no[] = {
 		"nlink", "nochange", "optional", NULL
 	};
-	static const char *keys_r[] = {
+	static const char * const keys_r[] = {
 		"resdevice", "rmd160", "rmd160digest", NULL
 	};
-	static const char *keys_s[] = {
+	static const char * const keys_s[] = {
 		"sha1", "sha1digest",
 		"sha256", "sha256digest",
 		"sha384", "sha384digest",
 		"sha512", "sha512digest",
 		"size", NULL
 	};
-	static const char *keys_t[] = {
+	static const char * const keys_t[] = {
 		"tags", "time", "type", NULL
 	};
-	static const char *keys_u[] = {
+	static const char * const keys_u[] = {
 		"uid", "uname",	NULL
 	};
-	const char **keys;
+	const char * const *keys;
 	int i;
 
 	switch (*p) {
@@ -1418,7 +1416,7 @@ parse_device(dev_t *pdev, struct archive *a, char *val)
 				    "Too many arguments");
 				return ARCHIVE_WARN;
 			}
-			numbers[argc++] = (unsigned long)mtree_atol(&p);
+			numbers[argc++] = (unsigned long)mtree_atol(&p, 0);
 		}
 		if (argc < 2) {
 			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
@@ -1433,7 +1431,7 @@ parse_device(dev_t *pdev, struct archive *a, char *val)
 		}
 	} else {
 		/* file system raw value. */
-		result = (dev_t)mtree_atol(&val);
+		result = (dev_t)mtree_atol(&val, 0);
 	}
 	*pdev = result;
 	return ARCHIVE_OK;
@@ -1513,7 +1511,7 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 	case 'g':
 		if (strcmp(key, "gid") == 0) {
 			*parsed_kws |= MTREE_HAS_GID;
-			archive_entry_set_gid(entry, mtree_atol10(&val));
+			archive_entry_set_gid(entry, mtree_atol(&val, 10));
 			break;
 		}
 		if (strcmp(key, "gname") == 0) {
@@ -1523,7 +1521,7 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 		}
 	case 'i':
 		if (strcmp(key, "inode") == 0) {
-			archive_entry_set_ino(entry, mtree_atol10(&val));
+			archive_entry_set_ino(entry, mtree_atol(&val, 10));
 			break;
 		}
 	case 'l':
@@ -1535,14 +1533,14 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 		if (strcmp(key, "md5") == 0 || strcmp(key, "md5digest") == 0)
 			break;
 		if (strcmp(key, "mode") == 0) {
-			if (val[0] >= '0' && val[0] <= '9') {
+			if (val[0] >= '0' && val[0] <= '7') {
 				*parsed_kws |= MTREE_HAS_PERM;
 				archive_entry_set_perm(entry,
-				    (mode_t)mtree_atol8(&val));
+				    (mode_t)mtree_atol(&val, 8));
 			} else {
 				archive_set_error(&a->archive,
 				    ARCHIVE_ERRNO_FILE_FORMAT,
-				    "Symbolic mode \"%s\" unsupported", val);
+				    "Symbolic or non-octal mode \"%s\" unsupported", val);
 				return ARCHIVE_WARN;
 			}
 			break;
@@ -1551,7 +1549,7 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 		if (strcmp(key, "nlink") == 0) {
 			*parsed_kws |= MTREE_HAS_NLINK;
 			archive_entry_set_nlink(entry,
-				(unsigned int)mtree_atol10(&val));
+				(unsigned int)mtree_atol(&val, 10));
 			break;
 		}
 	case 'r':
@@ -1582,7 +1580,7 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 		    strcmp(key, "sha512digest") == 0)
 			break;
 		if (strcmp(key, "size") == 0) {
-			archive_entry_set_size(entry, mtree_atol10(&val));
+			archive_entry_set_size(entry, mtree_atol(&val, 10));
 			break;
 		}
 	case 't':
@@ -1601,13 +1599,13 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 			long ns = 0;
 
 			*parsed_kws |= MTREE_HAS_MTIME;
-			m = mtree_atol10(&val);
+			m = mtree_atol(&val, 10);
 			/* Replicate an old mtree bug:
 			 * 123456789.1 represents 123456789
 			 * seconds and 1 nanosecond. */
 			if (*val == '.') {
 				++val;
-				ns = (long)mtree_atol10(&val);
+				ns = (long)mtree_atol(&val, 10);
 				if (ns < 0)
 					ns = 0;
 				else if (ns > 999999999)
@@ -1670,7 +1668,7 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 	case 'u':
 		if (strcmp(key, "uid") == 0) {
 			*parsed_kws |= MTREE_HAS_UID;
-			archive_entry_set_uid(entry, mtree_atol10(&val));
+			archive_entry_set_uid(entry, mtree_atol(&val, 10));
 			break;
 		}
 		if (strcmp(key, "uname") == 0) {
@@ -1825,72 +1823,9 @@ parse_escapes(char *src, struct mtree_entry *mentry)
 	*dest = '\0';
 }
 
-/*
- * Note that this implementation does not (and should not!) obey
- * locale settings; you cannot simply substitute strtol here, since
- * it does obey locale.
- */
-static int64_t
-mtree_atol8(char **p)
-{
-	int64_t	l, limit, last_digit_limit;
-	int digit, base;
-
-	base = 8;
-	limit = INT64_MAX / base;
-	last_digit_limit = INT64_MAX % base;
-
-	l = 0;
-	digit = **p - '0';
-	while (digit >= 0 && digit < base) {
-		if (l>limit || (l == limit && digit > last_digit_limit)) {
-			l = INT64_MAX; /* Truncate on overflow. */
-			break;
-		}
-		l = (l * base) + digit;
-		digit = *++(*p) - '0';
-	}
-	return (l);
-}
-
-/*
- * Note that this implementation does not (and should not!) obey
- * locale settings; you cannot simply substitute strtol here, since
- * it does obey locale.
- */
-static int64_t
-mtree_atol10(char **p)
-{
-	int64_t l, limit, last_digit_limit;
-	int base, digit, sign;
-
-	base = 10;
-
-	if (**p == '-') {
-		sign = -1;
-		limit = ((uint64_t)(INT64_MAX) + 1) / base;
-		last_digit_limit = ((uint64_t)(INT64_MAX) + 1) % base;
-		++(*p);
-	} else {
-		sign = 1;
-		limit = INT64_MAX / base;
-		last_digit_limit = INT64_MAX % base;
-	}
-
-	l = 0;
-	digit = **p - '0';
-	while (digit >= 0 && digit < base) {
-		if (l > limit || (l == limit && digit > last_digit_limit))
-			return (sign < 0) ? INT64_MIN : INT64_MAX;
-		l = (l * base) + digit;
-		digit = *++(*p) - '0';
-	}
-	return (sign < 0) ? -l : l;
-}
-
 /* Parse a hex digit. */
 static int
-parsehex(char c)
+parsedigit(char c)
 {
 	if (c >= '0' && c <= '9')
 		return c - '0';
@@ -1908,45 +1843,50 @@ parsehex(char c)
  * it does obey locale.
  */
 static int64_t
-mtree_atol16(char **p)
+mtree_atol(char **p, int base)
 {
-	int64_t l, limit, last_digit_limit;
-	int base, digit, sign;
-
-	base = 16;
+	int64_t l, limit;
+	int digit, last_digit_limit;
+
+	if (base == 0) {
+		if (**p != '0')
+			base = 10;
+		else if ((*p)[1] == 'x' || (*p)[1] == 'X') {
+			*p += 2;
+			base = 16;
+		} else {
+			base = 8;
+		}
+	}
 
 	if (**p == '-') {
-		sign = -1;
-		limit = ((uint64_t)(INT64_MAX) + 1) / base;
-		last_digit_limit = ((uint64_t)(INT64_MAX) + 1) % base;
+		limit = INT64_MIN / base;
+		last_digit_limit = INT64_MIN % base;
 		++(*p);
+
+		l = 0;
+		digit = parsedigit(**p);
+		while (digit >= 0 && digit < base) {
+			if (l < limit || (l == limit && digit > last_digit_limit))
+				return INT64_MIN;
+			l = (l * base) - digit;
+			digit = parsedigit(*++(*p));
+		}
+		return l;
 	} else {
-		sign = 1;
 		limit = INT64_MAX / base;
 		last_digit_limit = INT64_MAX % base;
-	}
 
-	l = 0;
-	digit = parsehex(**p);
-	while (digit >= 0 && digit < base) {
-		if (l > limit || (l == limit && digit > last_digit_limit))
-			return (sign < 0) ? INT64_MIN : INT64_MAX;
-		l = (l * base) + digit;
-		digit = parsehex(*++(*p));
-	}
-	return (sign < 0) ? -l : l;
-}
-
-static int64_t
-mtree_atol(char **p)
-{
-	if (**p != '0')
-		return mtree_atol10(p);
-	if ((*p)[1] == 'x' || (*p)[1] == 'X') {
-		*p += 2;
-		return mtree_atol16(p);
+		l = 0;
+		digit = parsedigit(**p);
+		while (digit >= 0 && digit < base) {
+			if (l > limit || (l == limit && digit > last_digit_limit))
+				return INT64_MAX;
+			l = (l * base) + digit;
+			digit = parsedigit(*++(*p));
+		}
+		return l;
 	}
-	return mtree_atol8(p);
 }
 
 /*