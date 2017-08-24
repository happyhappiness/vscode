@@ -1,7 +1,7 @@
 /*-
  * Copyright (c) 2003-2007 Tim Kientzle
  * Copyright (c) 2008 Joerg Sonnenberger
- * Copyright (c) 2011 Michihiro NAKAJIMA
+ * Copyright (c) 2011-2012 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -55,6 +55,9 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_support_format_mtree.c 2011
 #ifndef O_BINARY
 #define	O_BINARY 0
 #endif
+#ifndef O_CLOEXEC
+#define O_CLOEXEC	0
+#endif
 
 #define	MTREE_HAS_DEVICE	0x0001
 #define	MTREE_HAS_FFLAGS	0x0002
@@ -69,6 +72,7 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_support_format_mtree.c 2011
 #define	MTREE_HAS_UNAME		0x0400
 
 #define	MTREE_HAS_OPTIONAL	0x0800
+#define	MTREE_HAS_NOCHANGE	0x1000 /* FreeBSD specific */
 
 struct mtree_option {
 	struct mtree_option *next;
@@ -101,7 +105,9 @@ struct mtree {
 	int64_t			 cur_size;
 };
 
+static int	bid_keycmp(const char *, const char *, ssize_t);
 static int	cleanup(struct archive_read *);
+static int	detect_form(struct archive_read *, int *);
 static int	mtree_bid(struct archive_read *, int);
 static int	parse_file(struct archive_read *, struct archive_entry *,
 		    struct mtree *, struct mtree_entry *, int *);
@@ -199,7 +205,7 @@ archive_read_support_format_mtree(struct archive *_a)
 	mtree->fd = -1;
 
 	r = __archive_read_register_format(a, mtree, "mtree",
-	    mtree_bid, NULL, read_header, read_data, skip, cleanup);
+	    mtree_bid, NULL, read_header, read_data, skip, NULL, cleanup);
 
 	if (r != ARCHIVE_OK)
 		free(mtree);
@@ -317,7 +323,7 @@ next_line(struct archive_read *a,
  * Returns the length of a mtree keyword if matched.
  * Returns 0 if not matched.
  */
-int
+static int
 bid_keycmp(const char *p, const char *key, ssize_t len)
 {
 	int match_len = 0;
@@ -348,7 +354,7 @@ bid_keycmp(const char *p, const char *key, ssize_t len)
  * Returns the length of a detected keyword.
  * Returns 0 if any keywords were not found.
  */
-static ssize_t
+static int
 bid_keyword(const char *p,  ssize_t len)
 {
 	static const char *keys_c[] = {
@@ -367,7 +373,7 @@ bid_keyword(const char *p,  ssize_t len)
 		"md5", "md5digest", "mode", NULL
 	};
 	static const char *keys_no[] = {
-		"nlink", "optional", NULL
+		"nlink", "nochange", "optional", NULL
 	};
 	static const char *keys_r[] = {
 		"rmd160", "rmd160digest", NULL
@@ -418,7 +424,7 @@ bid_keyword(const char *p,  ssize_t len)
  * When "unset" is specified, expects a set of "<space characters>keyword".
  */
 static int
-bid_keyword_list(const char *p,  ssize_t len, int unset)
+bid_keyword_list(const char *p,  ssize_t len, int unset, int last_is_path)
 {
 	int l;
 	int keycnt = 0;
@@ -436,8 +442,10 @@ bid_keyword_list(const char *p,  ssize_t len, int unset)
 			break;
 		if (p[0] == '\\' && (p[1] == '\n' || p[1] == '\r'))
 			break;
-		if (!blank) /* No blank character. */
+		if (!blank && !last_is_path) /* No blank character. */
 			return (-1);
+		if (last_is_path && len == 0)
+				return (keycnt);
 
 		if (unset) {
 			l = bid_keycmp(p, "all", len);
@@ -472,7 +480,7 @@ bid_keyword_list(const char *p,  ssize_t len, int unset)
 }
 
 static int
-bid_entry(const char *p, ssize_t len)
+bid_entry(const char *p, ssize_t len, ssize_t nl, int *last_is_path)
 {
 	int f = 0;
 	static const unsigned char safe_char[256] = {
@@ -499,22 +507,60 @@ bid_entry(const char *p, ssize_t len)
 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* E0 - EF */
 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* F0 - FF */
 	};
+	ssize_t ll = len;
+	const char *pp = p;
 
+	*last_is_path = 0;
 	/*
 	 * Skip the path-name which is quoted.
 	 */
-	while (len > 0 && *p != ' ' && *p != '\t') {
-		if (!safe_char[*(const unsigned char *)p])
-			return (-1);
-		++p;
-		--len;
+	while (ll > 0 && *pp != ' ' &&*pp != '\t' && *pp != '\r' &&
+	    *pp != '\n') {
+		if (!safe_char[*(const unsigned char *)pp]) {
+			f = 0;
+			break;
+		}
+		++pp;
+		--ll;
 		++f;
 	}
-	/* If a path-name was not found, returns error. */
-	if (f == 0)
-		return (-1);
+	/* If a path-name was not found at the first, try to check
+	 * a mtree format ``NetBSD's mtree -D'' creates, which
+	 * places the path-name at the last. */
+	if (f == 0) {
+		const char *pb = p + len - nl;
+		int name_len = 0;
+		int slash;
+
+		/* Do not accept multi lines for form D. */
+		if (pb-2 >= p &&
+		    pb[-1] == '\\' && (pb[-2] == ' ' || pb[-2] == '\t'))
+			return (-1);
+		if (pb-1 >= p && pb[-1] == '\\')
+			return (-1);
+
+		slash = 0;
+		while (p <= --pb && *pb != ' ' && *pb != '\t') {
+			if (!safe_char[*(const unsigned char *)pb])
+				return (-1);
+			name_len++;
+			/* The pathname should have a slash in this
+			 * format. */
+			if (*pb == '/')
+				slash = 1;
+		}
+		if (name_len == 0 || slash == 0)
+			return (-1);
+		/* If '/' is placed at the first in this field, this is not
+		 * a valid filename. */
+		if (pb[1] == '/')
+			return (-1);
+		ll = len - nl - name_len;
+		pp = p;
+		*last_is_path = 1;
+	}
 
-	return (bid_keyword_list(p, len, 0));
+	return (bid_keyword_list(pp, ll, 0, *last_is_path));
 }
 
 #define MAX_BID_ENTRY	3
@@ -524,14 +570,11 @@ mtree_bid(struct archive_read *a, int best_bid)
 {
 	const char *signature = "#mtree";
 	const char *p;
-	ssize_t avail, ravail;
-	ssize_t len, nl;
-	int detected_bytes = 0, entry_cnt = 0, multiline = 0;
 
 	(void)best_bid; /* UNUSED */
 
 	/* Now let's look at the actual header and see if it matches. */
-	p = __archive_read_ahead(a, strlen(signature), &avail);
+	p = __archive_read_ahead(a, strlen(signature), NULL);
 	if (p == NULL)
 		return (-1);
 
@@ -541,6 +584,24 @@ mtree_bid(struct archive_read *a, int best_bid)
 	/*
 	 * There is not a mtree signature. Let's try to detect mtree format.
 	 */
+	return (detect_form(a, NULL));
+}
+
+static int
+detect_form(struct archive_read *a, int *is_form_d)
+{
+	const char *p;
+	ssize_t avail, ravail;
+	ssize_t detected_bytes = 0, len, nl;
+	int entry_cnt = 0, multiline = 0;
+	int form_D = 0;/* The archive is generated by `NetBSD mtree -D'
+			* (In this source we call it `form D') . */
+
+	if (is_form_d != NULL)
+		*is_form_d = 0;
+	p = __archive_read_ahead(a, 1, &avail);
+	if (p == NULL)
+		return (-1);
 	ravail = avail;
 	for (;;) {
 		len = next_line(a, &p, &avail, &ravail, &nl);
@@ -565,7 +626,7 @@ mtree_bid(struct archive_read *a, int best_bid)
 		} else {
 			/* A continuance line; the terminal
 			 * character of previous line was '\' character. */
-			if (bid_keyword_list(p, len, 0) <= 0)
+			if (bid_keyword_list(p, len, 0, 0) <= 0)
 				break;
 			if (multiline == 1)
 				detected_bytes += len;
@@ -580,9 +641,25 @@ mtree_bid(struct archive_read *a, int best_bid)
 			continue;
 		}
 		if (p[0] != '/') {
-			if (bid_entry(p, len) >= 0) {
+			int last_is_path, keywords;
+
+			keywords = bid_entry(p, len, nl, &last_is_path);
+			if (keywords >= 0) {
 				detected_bytes += len;
-				if (p[len-nl-1] == '\\')
+				if (form_D == 0) {
+					if (last_is_path)
+						form_D = 1;
+					else if (keywords > 0)
+						/* This line is not `form D'. */
+						form_D = -1;
+				} else if (form_D == 1) {
+					if (!last_is_path && keywords > 0)
+						/* This this is not `form D'
+						 * and We cannot accept mixed
+						 * format. */
+						break;
+				}
+				if (!last_is_path && p[len-nl-1] == '\\')
 					/* This line continues. */
 					multiline = 1;
 				else {
@@ -595,13 +672,13 @@ mtree_bid(struct archive_read *a, int best_bid)
 			} else
 				break;
 		} else if (strncmp(p, "/set", 4) == 0) {
-			if (bid_keyword_list(p+4, len-4, 0) <= 0)
+			if (bid_keyword_list(p+4, len-4, 0, 0) <= 0)
 				break;
 			/* This line continues. */
 			if (p[len-nl-1] == '\\')
 				multiline = 2;
 		} else if (strncmp(p, "/unset", 6) == 0) {
-			if (bid_keyword_list(p+6, len-6, 1) <= 0)
+			if (bid_keyword_list(p+6, len-6, 1, 0) <= 0)
 				break;
 			/* This line continues. */
 			if (p[len-nl-1] == '\\')
@@ -613,8 +690,13 @@ mtree_bid(struct archive_read *a, int best_bid)
 		p += len;
 		avail -= len;
 	}
-	if (entry_cnt >= MAX_BID_ENTRY || (entry_cnt > 0 && len == 0))
+	if (entry_cnt >= MAX_BID_ENTRY || (entry_cnt > 0 && len == 0)) {
+		if (is_form_d != NULL) {
+			if (form_D == 1)
+				*is_form_d = 1;
+		}
 		return (32);
+	}
 
 	return (0);
 }
@@ -738,12 +820,12 @@ process_global_unset(struct archive_read *a,
 
 static int
 process_add_entry(struct archive_read *a, struct mtree *mtree,
-    struct mtree_option **global, const char *line,
-    struct mtree_entry **last_entry)
+    struct mtree_option **global, const char *line, ssize_t line_len,
+    struct mtree_entry **last_entry, int is_form_d)
 {
 	struct mtree_entry *entry;
 	struct mtree_option *iter;
-	const char *next, *eq;
+	const char *next, *eq, *name, *end;
 	size_t len;
 	int r;
 
@@ -764,17 +846,46 @@ process_add_entry(struct archive_read *a, struct mtree *mtree,
 		(*last_entry)->next = entry;
 	*last_entry = entry;
 
-	len = strcspn(line, " \t\r\n");
+	if (is_form_d) {
+		/*
+		 * This form places the file name as last parameter.
+		 */
+		name = line + line_len -1;
+		while (line_len > 0) {
+			if (*name != '\r' && *name != '\n' &&
+			    *name != '\t' && *name != ' ')
+				break;
+			name--;
+			line_len--;
+		}
+		len = 0;
+		while (line_len > 0) {
+			if (*name == '\r' || *name == '\n' ||
+			    *name == '\t' || *name == ' ') {
+				name++;
+				break;
+			}
+			name--;
+			line_len--;
+			len++;
+		}
+		end = name;
+	} else {
+		len = strcspn(line, " \t\r\n");
+		name = line;
+		line += len;
+		end = line + line_len;
+	}
+
 	if ((entry->name = malloc(len + 1)) == NULL) {
 		archive_set_error(&a->archive, errno, "Can't allocate memory");
 		return (ARCHIVE_FATAL);
 	}
 
-	memcpy(entry->name, line, len);
+	memcpy(entry->name, name, len);
 	entry->name[len] = '\0';
 	parse_escapes(entry->name, entry);
 
-	line += len;
 	for (iter = *global; iter != NULL; iter = iter->next) {
 		r = add_option(a, &entry->options, iter->value,
 		    strlen(iter->value));
@@ -786,6 +897,8 @@ process_add_entry(struct archive_read *a, struct mtree *mtree,
 		next = line + strspn(line, " \t\r\n");
 		if (*next == '\0')
 			return (ARCHIVE_OK);
+		if (next >= end)
+			return (ARCHIVE_OK);
 		line = next;
 		next = line + strcspn(line, " \t\r\n");
 		eq = strchr(line, '=');
@@ -810,14 +923,16 @@ read_mtree(struct archive_read *a, struct mtree *mtree)
 	char *p;
 	struct mtree_option *global;
 	struct mtree_entry *last_entry;
-	int r;
+	int r, is_form_d;
 
 	mtree->archive_format = ARCHIVE_FORMAT_MTREE;
 	mtree->archive_format_name = "mtree";
 
 	global = NULL;
 	last_entry = NULL;
 
+	(void)detect_form(a, &is_form_d);
+
 	for (counter = 1; ; ++counter) {
 		len = readline(a, mtree, &p, 65536);
 		if (len == 0) {
@@ -827,7 +942,7 @@ read_mtree(struct archive_read *a, struct mtree *mtree)
 		}
 		if (len < 0) {
 			free_options(global);
-			return (len);
+			return ((int)len);
 		}
 		/* Leading whitespace is never significant, ignore it. */
 		while (*p == ' ' || *p == '\t') {
@@ -840,8 +955,8 @@ read_mtree(struct archive_read *a, struct mtree *mtree)
 		if (*p == '\r' || *p == '\n' || *p == '\0')
 			continue;
 		if (*p != '/') {
-			r = process_add_entry(a, mtree, &global, p,
-			    &last_entry);
+			r = process_add_entry(a, mtree, &global, p, len,
+			    &last_entry, is_form_d);
 		} else if (strncmp(p, "/set", 4) == 0) {
 			if (p[4] != ' ' && p[4] != '\t')
 				break;
@@ -1007,7 +1122,8 @@ parse_file(struct archive_read *a, struct archive_entry *entry,
 
 	if (archive_entry_filetype(entry) == AE_IFREG ||
 	    archive_entry_filetype(entry) == AE_IFDIR) {
-		mtree->fd = open(path, O_RDONLY | O_BINARY);
+		mtree->fd = open(path, O_RDONLY | O_BINARY | O_CLOEXEC);
+		__archive_ensure_cloexec_flag(mtree->fd);
 		if (mtree->fd == -1 &&
 		    (errno != ENOENT ||
 		     archive_strlen(&mtree->contents_name) > 0)) {
@@ -1090,15 +1206,19 @@ parse_file(struct archive_read *a, struct archive_entry *entry,
 	 * if it wasn't already parsed from the specification.
 	 */
 	if (st != NULL) {
-		if ((parsed_kws & MTREE_HAS_DEVICE) == 0 &&
+		if (((parsed_kws & MTREE_HAS_DEVICE) == 0 ||
+		     (parsed_kws & MTREE_HAS_NOCHANGE) != 0) &&
 		    (archive_entry_filetype(entry) == AE_IFCHR ||
 		     archive_entry_filetype(entry) == AE_IFBLK))
 			archive_entry_set_rdev(entry, st->st_rdev);
-		if ((parsed_kws & (MTREE_HAS_GID | MTREE_HAS_GNAME)) == 0)
+		if ((parsed_kws & (MTREE_HAS_GID | MTREE_HAS_GNAME)) == 0 ||
+		    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
 			archive_entry_set_gid(entry, st->st_gid);
-		if ((parsed_kws & (MTREE_HAS_UID | MTREE_HAS_UNAME)) == 0)
+		if ((parsed_kws & (MTREE_HAS_UID | MTREE_HAS_UNAME)) == 0 ||
+		    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
 			archive_entry_set_uid(entry, st->st_uid);
-		if ((parsed_kws & MTREE_HAS_MTIME) == 0) {
+		if ((parsed_kws & MTREE_HAS_MTIME) == 0 ||
+		    (parsed_kws & MTREE_HAS_NOCHANGE) != 0) {
 #if HAVE_STRUCT_STAT_ST_MTIMESPEC_TV_NSEC
 			archive_entry_set_mtime(entry, st->st_mtime,
 			    st->st_mtimespec.tv_nsec);
@@ -1118,11 +1238,14 @@ parse_file(struct archive_read *a, struct archive_entry *entry,
 			archive_entry_set_mtime(entry, st->st_mtime, 0);
 #endif
 		}
-		if ((parsed_kws & MTREE_HAS_NLINK) == 0)
+		if ((parsed_kws & MTREE_HAS_NLINK) == 0 ||
+		    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
 			archive_entry_set_nlink(entry, st->st_nlink);
-		if ((parsed_kws & MTREE_HAS_PERM) == 0)
+		if ((parsed_kws & MTREE_HAS_PERM) == 0 ||
+		    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
 			archive_entry_set_perm(entry, st->st_mode);
-		if ((parsed_kws & MTREE_HAS_SIZE) == 0)
+		if ((parsed_kws & MTREE_HAS_SIZE) == 0 ||
+		    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
 			archive_entry_set_size(entry, st->st_size);
 		archive_entry_set_ino(entry, st->st_ino);
 		archive_entry_set_dev(entry, st->st_dev);
@@ -1182,7 +1305,7 @@ parse_device(struct archive *a, struct archive_entry *entry, char *val)
 
 	comma1 = strchr(val, ',');
 	if (comma1 == NULL) {
-		archive_entry_set_dev(entry, mtree_atol10(&val));
+		archive_entry_set_dev(entry, (dev_t)mtree_atol10(&val));
 		return (ARCHIVE_OK);
 	}
 	++comma1;
@@ -1193,8 +1316,8 @@ parse_device(struct archive *a, struct archive_entry *entry, char *val)
 		return (ARCHIVE_WARN);
 	}
 	++comma2;
-	archive_entry_set_rdevmajor(entry, mtree_atol(&comma1));
-	archive_entry_set_rdevminor(entry, mtree_atol(&comma2));
+	archive_entry_set_rdevmajor(entry, (dev_t)mtree_atol(&comma1));
+	archive_entry_set_rdevminor(entry, (dev_t)mtree_atol(&comma2));
 	return (ARCHIVE_OK);
 }
 
@@ -1212,6 +1335,10 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 	if (*key == '\0')
 		return (ARCHIVE_OK);
 
+	if (strcmp(key, "nochange") == 0) {
+		*parsed_kws |= MTREE_HAS_NOCHANGE;
+		return (ARCHIVE_OK);
+	}
 	if (strcmp(key, "optional") == 0) {
 		*parsed_kws |= MTREE_HAS_OPTIONAL;
 		return (ARCHIVE_OK);
@@ -1279,7 +1406,7 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 			if (val[0] >= '0' && val[0] <= '9') {
 				*parsed_kws |= MTREE_HAS_PERM;
 				archive_entry_set_perm(entry,
-				    mtree_atol8(&val));
+				    (mode_t)mtree_atol8(&val));
 			} else {
 				archive_set_error(&a->archive,
 				    ARCHIVE_ERRNO_FILE_FORMAT,
@@ -1291,7 +1418,8 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 	case 'n':
 		if (strcmp(key, "nlink") == 0) {
 			*parsed_kws |= MTREE_HAS_NLINK;
-			archive_entry_set_nlink(entry, mtree_atol10(&val));
+			archive_entry_set_nlink(entry,
+				(unsigned int)mtree_atol10(&val));
 			break;
 		}
 	case 'r':
@@ -1433,7 +1561,7 @@ read_data(struct archive_read *a, const void **buff, size_t *size, int64_t *offs
 	*buff = mtree->buff;
 	*offset = mtree->offset;
 	if ((int64_t)mtree->buffsize > mtree->cur_size - mtree->offset)
-		bytes_to_read = mtree->cur_size - mtree->offset;
+		bytes_to_read = (size_t)(mtree->cur_size - mtree->offset);
 	else
 		bytes_to_read = mtree->buffsize;
 	bytes_read = read(mtree->fd, mtree->buff, bytes_to_read);