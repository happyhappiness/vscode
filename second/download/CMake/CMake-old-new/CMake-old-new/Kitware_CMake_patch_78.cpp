@@ -1,6 +1,7 @@
 /*-
  * Copyright (c) 2003-2007 Tim Kientzle
  * Copyright (c) 2010-2012 Michihiro NAKAJIMA
+ * Copyright (c) 2016 Martin Matuska
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -61,15 +62,24 @@ struct pax {
 	struct sparse_block	*sparse_tail;
 	struct archive_string_conv *sconv_utf8;
 	int			 opt_binary;
+
+	unsigned flags;
+#define WRITE_SCHILY_XATTR       (1 << 0)
+#define WRITE_LIBARCHIVE_XATTR   (1 << 1)
 };
 
 static void		 add_pax_attr(struct archive_string *, const char *key,
 			     const char *value);
+static void		 add_pax_attr_binary(struct archive_string *,
+			     const char *key,
+			     const char *value, size_t value_len);
 static void		 add_pax_attr_int(struct archive_string *,
 			     const char *key, int64_t value);
 static void		 add_pax_attr_time(struct archive_string *,
 			     const char *key, int64_t sec,
 			     unsigned long nanos);
+static int		 add_pax_acl(struct archive_write *,
+			    struct archive_entry *, struct pax *, int);
 static ssize_t		 archive_write_pax_data(struct archive_write *,
 			     const void *, size_t);
 static int		 archive_write_pax_close(struct archive_write *);
@@ -127,13 +137,14 @@ archive_write_set_format_pax(struct archive *_a)
 	if (a->format_free != NULL)
 		(a->format_free)(a);
 
-	pax = (struct pax *)malloc(sizeof(*pax));
+	pax = (struct pax *)calloc(1, sizeof(*pax));
 	if (pax == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate pax data");
 		return (ARCHIVE_FATAL);
 	}
-	memset(pax, 0, sizeof(*pax));
+	pax->flags = WRITE_LIBARCHIVE_XATTR | WRITE_SCHILY_XATTR;
+
 	a->format_data = pax;
 	a->format_name = "pax";
 	a->format_options = archive_write_pax_options;
@@ -273,14 +284,25 @@ add_pax_attr_int(struct archive_string *as, const char *key, int64_t value)
 static void
 add_pax_attr(struct archive_string *as, const char *key, const char *value)
 {
+	add_pax_attr_binary(as, key, value, strlen(value));
+}
+
+/*
+ * Add a key/value attribute to the pax header.  This function handles
+ * binary values.
+ */
+static void
+add_pax_attr_binary(struct archive_string *as, const char *key,
+		    const char *value, size_t value_len)
+{
 	int digits, i, len, next_ten;
 	char tmp[1 + 3 * sizeof(int)];	/* < 3 base-10 digits per byte */
 
 	/*-
 	 * PAX attributes have the following layout:
 	 *     <len> <space> <key> <=> <value> <nl>
 	 */
-	len = 1 + (int)strlen(key) + 1 + (int)strlen(value) + 1;
+	len = 1 + (int)strlen(key) + 1 + (int)value_len + 1;
 
 	/*
 	 * The <len> field includes the length of the <len> field, so
@@ -311,21 +333,47 @@ add_pax_attr(struct archive_string *as, const char *key, const char *value)
 	archive_strappend_char(as, ' ');
 	archive_strcat(as, key);
 	archive_strappend_char(as, '=');
-	archive_strcat(as, value);
+	archive_array_append(as, value, value_len);
 	archive_strappend_char(as, '\n');
 }
 
+static void
+archive_write_pax_header_xattr(struct pax *pax, const char *encoded_name,
+    const void *value, size_t value_len)
+{
+	struct archive_string s;
+	char *encoded_value;
+
+	if (pax->flags & WRITE_LIBARCHIVE_XATTR) {
+		encoded_value = base64_encode((const char *)value, value_len);
+
+		if (encoded_name != NULL && encoded_value != NULL) {
+			archive_string_init(&s);
+			archive_strcpy(&s, "LIBARCHIVE.xattr.");
+			archive_strcat(&s, encoded_name);
+			add_pax_attr(&(pax->pax_header), s.s, encoded_value);
+			archive_string_free(&s);
+		}
+		free(encoded_value);
+	}
+	if (pax->flags & WRITE_SCHILY_XATTR) {
+		archive_string_init(&s);
+		archive_strcpy(&s, "SCHILY.xattr.");
+		archive_strcat(&s, encoded_name);
+		add_pax_attr_binary(&(pax->pax_header), s.s, value, value_len);
+		archive_string_free(&s);
+	}
+}
+
 static int
 archive_write_pax_header_xattrs(struct archive_write *a,
     struct pax *pax, struct archive_entry *entry)
 {
-	struct archive_string s;
 	int i = archive_entry_xattr_reset(entry);
 
 	while (i--) {
 		const char *name;
 		const void *value;
-		char *encoded_value;
 		char *url_encoded_name = NULL, *encoded_name = NULL;
 		size_t size;
 		int r;
@@ -346,16 +394,9 @@ archive_write_pax_header_xattrs(struct archive_write *a,
 			}
 		}
 
-		encoded_value = base64_encode((const char *)value, size);
+		archive_write_pax_header_xattr(pax, encoded_name,
+		    value, size);
 
-		if (encoded_name != NULL && encoded_value != NULL) {
-			archive_string_init(&s);
-			archive_strcpy(&s, "LIBARCHIVE.xattr.");
-			archive_strcat(&s, encoded_name);
-			add_pax_attr(&(pax->pax_header), s.s, encoded_value);
-			archive_string_free(&s);
-		}
-		free(encoded_value);
 	}
 	return (ARCHIVE_OK);
 }
@@ -450,6 +491,45 @@ get_entry_symlink(struct archive_write *a, struct archive_entry *entry,
 	return (ARCHIVE_OK);
 }
 
+/* Add ACL to pax header */
+static int
+add_pax_acl(struct archive_write *a,
+    struct archive_entry *entry, struct pax *pax, int flags)
+{
+	char *p;
+	const char *attr;
+	int acl_types;
+
+	acl_types = archive_entry_acl_types(entry);
+
+	if ((acl_types & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0)
+		attr = "SCHILY.acl.ace";
+	else if ((flags & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0)
+		attr = "SCHILY.acl.access";
+	else if ((flags & ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) != 0)
+		attr = "SCHILY.acl.default";
+	else
+		return (ARCHIVE_FATAL);
+
+	p = archive_entry_acl_to_text_l(entry, NULL, flags, pax->sconv_utf8);
+	if (p == NULL) {
+		if (errno == ENOMEM) {
+			archive_set_error(&a->archive, ENOMEM, "%s %s",
+			    "Can't allocate memory for ", attr);
+			return (ARCHIVE_FATAL);
+		}
+		archive_set_error(&a->archive,
+		    ARCHIVE_ERRNO_FILE_FORMAT, "%s %s %s",
+		    "Can't translate ", attr, " to UTF-8");
+		return(ARCHIVE_WARN);
+	} else if (*p != '\0') {
+		add_pax_attr(&(pax->pax_header),
+		    attr, p);
+		free(p);
+	}
+	return(ARCHIVE_OK);
+}
+
 /*
  * TODO: Consider adding 'comment' and 'charset' fields to
  * archive_entry so that clients can specify them.  Also, consider
@@ -466,6 +546,7 @@ archive_write_pax_header(struct archive_write *a,
 	const char *p;
 	const char *suffix;
 	int need_extension, r, ret;
+	int acl_types;
 	int sparse_count;
 	uint64_t sparse_total, real_size;
 	struct pax *pax;
@@ -709,7 +790,7 @@ archive_write_pax_header(struct archive_write *a,
 
 	/* Copy entry so we can modify it as needed. */
 #if defined(_WIN32) && !defined(__CYGWIN__)
-	/* Make sure the path separators in pahtname, hardlink and symlink
+	/* Make sure the path separators in pathname, hardlink and symlink
 	 * are all slash '/', not the Windows path separator '\'. */
 	entry_main = __la_win_entry_in_posix_pathseparator(entry_original);
 	if (entry_main == entry_original)
@@ -1017,16 +1098,6 @@ archive_write_pax_header(struct archive_write *a,
 	if (!need_extension && p != NULL  &&  *p != '\0')
 		need_extension = 1;
 
-	/* If there are non-trivial ACL entries, we need an extension. */
-	if (!need_extension && archive_entry_acl_count(entry_original,
-		ARCHIVE_ENTRY_ACL_TYPE_ACCESS) > 0)
-		need_extension = 1;
-
-	/* If there are non-trivial ACL entries, we need an extension. */
-	if (!need_extension && archive_entry_acl_count(entry_original,
-		ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) > 0)
-		need_extension = 1;
-
 	/* If there are extended attributes, we need an extension */
 	if (!need_extension && archive_entry_xattr_count(entry_original) > 0)
 		need_extension = 1;
@@ -1035,6 +1106,12 @@ archive_write_pax_header(struct archive_write *a,
 	if (!need_extension && sparse_count > 0)
 		need_extension = 1;
 
+	acl_types = archive_entry_acl_types(entry_original);
+
+	/* If there are any ACL entries, we need an extension */
+	if (!need_extension && acl_types != 0)
+		need_extension = 1;
+
 	/*
 	 * Libarchive used to include these in extended headers for
 	 * restricted pax format, but that confused people who
@@ -1086,43 +1163,29 @@ archive_write_pax_header(struct archive_write *a,
 			add_pax_attr(&(pax->pax_header), "SCHILY.fflags", p);
 
 		/* I use star-compatible ACL attributes. */
-		r = archive_entry_acl_text_l(entry_original,
-		    ARCHIVE_ENTRY_ACL_TYPE_ACCESS |
-		    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID,
-		    &p, NULL, pax->sconv_utf8);
-		if (r != 0) {
-			if (errno == ENOMEM) {
-				archive_set_error(&a->archive, ENOMEM,
-				    "Can't allocate memory for "
-				    "ACL.access");
+		if ((acl_types & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0) {
+			ret = add_pax_acl(a, entry_original, pax,
+			    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID |
+			    ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA |
+			    ARCHIVE_ENTRY_ACL_STYLE_COMPACT);
+			if (ret == ARCHIVE_FATAL)
 				return (ARCHIVE_FATAL);
-			}
-			archive_set_error(&a->archive,
-			    ARCHIVE_ERRNO_FILE_FORMAT,
-			    "Can't translate ACL.access to UTF-8");
-			ret = ARCHIVE_WARN;
-		} else if (p != NULL && *p != '\0') {
-			add_pax_attr(&(pax->pax_header),
-			    "SCHILY.acl.access", p);
 		}
-		r = archive_entry_acl_text_l(entry_original,
-		    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT |
-		    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID,
-		    &p, NULL, pax->sconv_utf8);
-		if (r != 0) {
-			if (errno == ENOMEM) {
-				archive_set_error(&a->archive, ENOMEM,
-				    "Can't allocate memory for "
-				    "ACL.default");
+		if (acl_types & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) {
+			ret = add_pax_acl(a, entry_original, pax,
+			    ARCHIVE_ENTRY_ACL_TYPE_ACCESS |
+			    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID |
+			    ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA);
+			if (ret == ARCHIVE_FATAL)
+				return (ARCHIVE_FATAL);
+		}
+		if (acl_types & ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) {
+			ret = add_pax_acl(a, entry_original, pax,
+			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT |
+			    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID |
+			    ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA);
+			if (ret == ARCHIVE_FATAL)
 				return (ARCHIVE_FATAL);
-			}
-			archive_set_error(&a->archive,
-			    ARCHIVE_ERRNO_FILE_FORMAT,
-			    "Can't translate ACL.default to UTF-8");
-			ret = ARCHIVE_WARN;
-		} else if (p != NULL && *p != '\0') {
-			add_pax_attr(&(pax->pax_header),
-			    "SCHILY.acl.default", p);
 		}
 
 		/* We use GNU-tar-compatible sparse attributes. */