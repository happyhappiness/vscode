@@ -75,6 +75,8 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_support_format_mtree.c 2011
 #define	MTREE_HAS_OPTIONAL	0x0800
 #define	MTREE_HAS_NOCHANGE	0x1000 /* FreeBSD specific */
 
+#define	MTREE_HASHTABLE_SIZE 1024
+
 struct mtree_option {
 	struct mtree_option *next;
 	char *value;
@@ -86,6 +88,8 @@ struct mtree_entry {
 	char *name;
 	char full;
 	char used;
+	unsigned int name_hash;
+	struct mtree_entry *hashtable_next;
 };
 
 struct mtree {
@@ -98,6 +102,7 @@ struct mtree {
 	const char		*archive_format_name;
 	struct mtree_entry	*entries;
 	struct mtree_entry	*this_entry;
+	struct mtree_entry	*entry_hashtable[MTREE_HASHTABLE_SIZE];
 	struct archive_string	 current_dir;
 	struct archive_string	 contents_name;
 
@@ -110,6 +115,7 @@ struct mtree {
 static int	bid_keycmp(const char *, const char *, ssize_t);
 static int	cleanup(struct archive_read *);
 static int	detect_form(struct archive_read *, int *);
+static unsigned int	hash(const char *);
 static int	mtree_bid(struct archive_read *, int);
 static int	parse_file(struct archive_read *, struct archive_entry *,
 		    struct mtree *, struct mtree_entry *, int *);
@@ -223,13 +229,12 @@ archive_read_support_format_mtree(struct archive *_a)
 	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
 	    ARCHIVE_STATE_NEW, "archive_read_support_format_mtree");
 
-	mtree = (struct mtree *)malloc(sizeof(*mtree));
+	mtree = (struct mtree *)calloc(1, sizeof(*mtree));
 	if (mtree == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate mtree data");
 		return (ARCHIVE_FATAL);
 	}
-	memset(mtree, 0, sizeof(*mtree));
 	mtree->fd = -1;
 
 	r = __archive_read_register_format(a, mtree, "mtree",
@@ -301,6 +306,15 @@ get_line_size(const char *b, ssize_t avail, ssize_t *nlsize)
 	return (avail);
 }
 
+/*
+ *  <---------------- ravail --------------------->
+ *  <-- diff ------> <---  avail ----------------->
+ *                   <---- len ----------->
+ * | Previous lines | line being parsed  nl extra |
+ *                  ^
+ *                  b
+ *
+ */
 static ssize_t
 next_line(struct archive_read *a,
     const char **b, ssize_t *avail, ssize_t *ravail, ssize_t *nl)
@@ -339,7 +353,7 @@ next_line(struct archive_read *a,
 		*b += diff;
 		*avail -= diff;
 		tested = len;/* Skip some bytes we already determinated. */
-		len = get_line_size(*b, *avail, nl);
+		len = get_line_size(*b + len, *avail - len, nl);
 		if (len >= 0)
 			len += tested;
 	}
@@ -701,13 +715,13 @@ detect_form(struct archive_read *a, int *is_form_d)
 				}
 			} else
 				break;
-		} else if (strncmp(p, "/set", 4) == 0) {
+		} else if (len > 4 && strncmp(p, "/set", 4) == 0) {
 			if (bid_keyword_list(p+4, len-4, 0, 0) <= 0)
 				break;
 			/* This line continues. */
 			if (p[len-nl-1] == '\\')
 				multiline = 2;
-		} else if (strncmp(p, "/unset", 6) == 0) {
+		} else if (len > 6 && strncmp(p, "/unset", 6) == 0) {
 			if (bid_keyword_list(p+6, len-6, 1, 0) <= 0)
 				break;
 			/* This line continues. */
@@ -853,11 +867,12 @@ process_add_entry(struct archive_read *a, struct mtree *mtree,
     struct mtree_option **global, const char *line, ssize_t line_len,
     struct mtree_entry **last_entry, int is_form_d)
 {
-	struct mtree_entry *entry;
+	struct mtree_entry *entry, *ht_iter;
 	struct mtree_option *iter;
 	const char *next, *eq, *name, *end;
 	size_t name_len, len;
 	int r, i;
+	unsigned int ht_idx;
 
 	if ((entry = malloc(sizeof(*entry))) == NULL) {
 		archive_set_error(&a->archive, errno, "Can't allocate memory");
@@ -868,6 +883,8 @@ process_add_entry(struct archive_read *a, struct mtree *mtree,
 	entry->name = NULL;
 	entry->used = 0;
 	entry->full = 0;
+	entry->name_hash = 0;
+	entry->hashtable_next = NULL;
 
 	/* Add this entry to list. */
 	if (*last_entry == NULL)
@@ -920,6 +937,16 @@ process_add_entry(struct archive_read *a, struct mtree *mtree,
 	memcpy(entry->name, name, name_len);
 	entry->name[name_len] = '\0';
 	parse_escapes(entry->name, entry);
+	entry->name_hash = hash(entry->name);
+
+	ht_idx = entry->name_hash % MTREE_HASHTABLE_SIZE;
+	if ((ht_iter = mtree->entry_hashtable[ht_idx]) != NULL) {
+		while (ht_iter->hashtable_next)
+			ht_iter = ht_iter->hashtable_next;
+		ht_iter->hashtable_next = entry;
+	} else {
+		mtree->entry_hashtable[ht_idx] = entry;
+	}
 
 	for (iter = *global; iter != NULL; iter = iter->next) {
 		r = add_option(a, &entry->options, iter->value,
@@ -992,11 +1019,11 @@ read_mtree(struct archive_read *a, struct mtree *mtree)
 		if (*p != '/') {
 			r = process_add_entry(a, mtree, &global, p, len,
 			    &last_entry, is_form_d);
-		} else if (strncmp(p, "/set", 4) == 0) {
+		} else if (len > 4 && strncmp(p, "/set", 4) == 0) {
 			if (p[4] != ' ' && p[4] != '\t')
 				break;
 			r = process_global_set(a, &global, p);
-		} else if (strncmp(p, "/unset", 6) == 0) {
+		} else if (len > 6 && strncmp(p, "/unset", 6) == 0) {
 			if (p[6] != ' ' && p[6] != '\t')
 				break;
 			r = process_global_unset(a, &global, p);
@@ -1113,9 +1140,10 @@ parse_file(struct archive_read *a, struct archive_entry *entry,
 		 * with pathname canonicalization, which is a very
 		 * tricky subject.)
 		 */
-		for (mp = mentry->next; mp != NULL; mp = mp->next) {
+		for (mp = mentry->hashtable_next; mp != NULL; mp = mp->hashtable_next) {
 			if (mp->full && !mp->used
-			    && strcmp(mentry->name, mp->name) == 0) {
+					&& mentry->name_hash == mp->name_hash
+					&& strcmp(mentry->name, mp->name) == 0) {
 				/* Later lines override earlier ones. */
 				mp->used = 1;
 				r1 = parse_line(a, entry, mtree, mp,
@@ -1580,8 +1608,11 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 			if (*val == '.') {
 				++val;
 				ns = (long)mtree_atol10(&val);
-			} else
-				ns = 0;
+				if (ns < 0)
+					ns = 0;
+				else if (ns > 999999999)
+					ns = 999999999;
+			}
 			if (m > my_time_t_max)
 				m = my_time_t_max;
 			else if (m < my_time_t_min)
@@ -1991,3 +2022,19 @@ readline(struct archive_read *a, struct mtree *mtree, char **start,
 		find_off = u - mtree->line.s;
 	}
 }
+
+static unsigned int
+hash(const char *p)
+{
+	/* A 32-bit version of Peter Weinberger's (PJW) hash algorithm,
+	   as used by ELF for hashing function names. */
+	unsigned g, h = 0;
+	while (*p != '\0') {
+		h = (h << 4) + *p++;
+		if ((g = h & 0xF0000000) != 0) {
+			h ^= g >> 24;
+			h &= 0x0FFFFFFF;
+		}
+	}
+	return h;
+}