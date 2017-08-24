@@ -148,9 +148,12 @@ get_time_t_max(void)
 		return (~(time_t)0);
 	} else {
 		/* Time_t is signed. */
-		const uintmax_t max_unsigned_time_t = (uintmax_t)(~(time_t)0);
-		const uintmax_t max_signed_time_t = max_unsigned_time_t >> 1;
-		return (time_t)max_signed_time_t;
+		/* Assume it's the same as int64_t or int32_t */
+		if (sizeof(time_t) == sizeof(int64_t)) {
+			return (time_t)INT64_MAX;
+		} else {
+			return (time_t)INT32_MAX;
+		}
 	}
 #endif
 }
@@ -166,10 +169,11 @@ get_time_t_min(void)
 		return (time_t)0;
 	} else {
 		/* Time_t is signed. */
-		const uintmax_t max_unsigned_time_t = (uintmax_t)(~(time_t)0);
-		const uintmax_t max_signed_time_t = max_unsigned_time_t >> 1;
-		const intmax_t min_signed_time_t = (intmax_t)~max_signed_time_t;
-		return (time_t)min_signed_time_t;
+		if (sizeof(time_t) == sizeof(int64_t)) {
+			return (time_t)INT64_MIN;
+		} else {
+			return (time_t)INT32_MIN;
+		}
 	}
 #endif
 }
@@ -852,8 +856,8 @@ process_add_entry(struct archive_read *a, struct mtree *mtree,
 	struct mtree_entry *entry;
 	struct mtree_option *iter;
 	const char *next, *eq, *name, *end;
-	size_t len;
-	int r;
+	size_t name_len, len;
+	int r, i;
 
 	if ((entry = malloc(sizeof(*entry))) == NULL) {
 		archive_set_error(&a->archive, errno, "Can't allocate memory");
@@ -873,43 +877,48 @@ process_add_entry(struct archive_read *a, struct mtree *mtree,
 	*last_entry = entry;
 
 	if (is_form_d) {
-		/*
-		 * This form places the file name as last parameter.
-		 */
-		name = line + line_len -1;
+		/* Filename is last item on line. */
+		/* Adjust line_len to trim trailing whitespace */
 		while (line_len > 0) {
-			if (*name != '\r' && *name != '\n' &&
-			    *name != '\t' && *name != ' ')
+			char last_character = line[line_len - 1];
+			if (last_character == '\r'
+			    || last_character == '\n'
+			    || last_character == '\t'
+			    || last_character == ' ') {
+				line_len--;
+			} else {
 				break;
-			name--;
-			line_len--;
+			}
 		}
-		len = 0;
-		while (line_len > 0) {
-			if (*name == '\r' || *name == '\n' ||
-			    *name == '\t' || *name == ' ') {
-				name++;
-				break;
+		/* Name starts after the last whitespace separator */
+		name = line;
+		for (i = 0; i < line_len; i++) {
+			if (line[i] == '\r'
+			    || line[i] == '\n'
+			    || line[i] == '\t'
+			    || line[i] == ' ') {
+				name = line + i + 1;
 			}
-			name--;
-			line_len--;
-			len++;
 		}
+		name_len = line + line_len - name;
 		end = name;
 	} else {
-		len = strcspn(line, " \t\r\n");
+		/* Filename is first item on line */
+		name_len = strcspn(line, " \t\r\n");
 		name = line;
-		line += len;
+		line += name_len;
 		end = line + line_len;
 	}
+	/* name/name_len is the name within the line. */
+	/* line..end brackets the entire line except the name */
 
-	if ((entry->name = malloc(len + 1)) == NULL) {
+	if ((entry->name = malloc(name_len + 1)) == NULL) {
 		archive_set_error(&a->archive, errno, "Can't allocate memory");
 		return (ARCHIVE_FATAL);
 	}
 
-	memcpy(entry->name, name, len);
-	entry->name[len] = '\0';
+	memcpy(entry->name, name, name_len);
+	entry->name[name_len] = '\0';
 	parse_escapes(entry->name, entry);
 
 	for (iter = *global; iter != NULL; iter = iter->next) {
@@ -1561,7 +1570,7 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 			int64_t m;
 			int64_t my_time_t_max = get_time_t_max();
 			int64_t my_time_t_min = get_time_t_min();
-			long ns;
+			long ns = 0;
 
 			*parsed_kws |= MTREE_HAS_MTIME;
 			m = mtree_atol10(&val);