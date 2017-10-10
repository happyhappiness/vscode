 		}
 	}
 
 	free(cl_separators);
 }
 
-static struct strbuf **read_input_file(const char *file)
+static void read_input_file(struct strbuf *sb, const char *file)
 {
-	struct strbuf **lines;
-	struct strbuf sb = STRBUF_INIT;
-
 	if (file) {
-		if (strbuf_read_file(&sb, file, 0) < 0)
+		if (strbuf_read_file(sb, file, 0) < 0)
 			die_errno(_("could not read input file '%s'"), file);
 	} else {
-		if (strbuf_read(&sb, fileno(stdin), 0) < 0)
+		if (strbuf_read(sb, fileno(stdin), 0) < 0)
 			die_errno(_("could not read from stdin"));
 	}
+}
 
-	lines = strbuf_split(&sb, '\n');
+static const char *next_line(const char *str)
+{
+	const char *nl = strchrnul(str, '\n');
+	return nl + !!*nl;
+}
 
-	strbuf_release(&sb);
+/*
+ * Return the position of the start of the last line. If len is 0, return -1.
+ */
+static int last_line(const char *buf, size_t len)
+{
+	int i;
+	if (len == 0)
+		return -1;
+	if (len == 1)
+		return 0;
+	/*
+	 * Skip the last character (in addition to the null terminator),
+	 * because if the last character is a newline, it is considered as part
+	 * of the last line anyway.
+	 */
+	i = len - 2;
 
-	return lines;
+	for (; i >= 0; i--) {
+		if (buf[i] == '\n')
+			return i + 1;
+	}
+	return 0;
 }
 
 /*
- * Return the (0 based) index of the start of the patch or the line
- * count if there is no patch in the message.
+ * Return the position of the start of the patch or the length of str if there
+ * is no patch in the message.
  */
-static int find_patch_start(struct strbuf **lines, int count)
+static int find_patch_start(const char *str)
 {
-	int i;
+	const char *s;
 
-	/* Get the start of the patch part if any */
-	for (i = 0; i < count; i++) {
-		if (starts_with(lines[i]->buf, "---"))
-			return i;
+	for (s = str; *s; s = next_line(s)) {
+		if (starts_with(s, "---"))
+			return s - str;
 	}
 
-	return count;
+	return s - str;
 }
 
 /*
- * Return the (0 based) index of the first trailer line or count if
- * there are no trailers. Trailers are searched only in the lines from
- * index (count - 1) down to index 0.
+ * Return the position of the first trailer line or len if there are no
+ * trailers.
  */
-static int find_trailer_start(struct strbuf **lines, int count)
+static int find_trailer_start(const char *buf, size_t len)
 {
-	int start, end_of_title, only_spaces = 1;
+	const char *s;
+	int end_of_title, l, only_spaces = 1;
 	int recognized_prefix = 0, trailer_lines = 0, non_trailer_lines = 0;
 	/*
 	 * Number of possible continuation lines encountered. This will be
 	 * reset to 0 if we encounter a trailer (since those lines are to be
 	 * considered continuations of that trailer), and added to
 	 * non_trailer_lines if we encounter a non-trailer (since those lines
 	 * are to be considered non-trailers).
 	 */
 	int possible_continuation_lines = 0;
 
 	/* The first paragraph is the title and cannot be trailers */
-	for (start = 0; start < count; start++) {
-		if (lines[start]->buf[0] == comment_line_char)
+	for (s = buf; s < buf + len; s = next_line(s)) {
+		if (s[0] == comment_line_char)
 			continue;
-		if (contains_only_spaces(lines[start]->buf))
+		if (is_blank_line(s))
 			break;
 	}
-	end_of_title = start;
+	end_of_title = s - buf;
 
 	/*
 	 * Get the start of the trailers by looking starting from the end for a
 	 * blank line before a set of non-blank lines that (i) are all
 	 * trailers, or (ii) contains at least one Git-generated trailer and
 	 * consists of at least 25% trailers.
 	 */
-	for (start = count - 1; start >= end_of_title; start--) {
+	for (l = last_line(buf, len);
+	     l >= end_of_title;
+	     l = last_line(buf, l)) {
+		const char *bol = buf + l;
 		const char **p;
 		int separator_pos;
 
-		if (lines[start]->buf[0] == comment_line_char) {
+		if (bol[0] == comment_line_char) {
 			non_trailer_lines += possible_continuation_lines;
 			possible_continuation_lines = 0;
 			continue;
 		}
-		if (contains_only_spaces(lines[start]->buf)) {
+		if (is_blank_line(bol)) {
 			if (only_spaces)
 				continue;
 			non_trailer_lines += possible_continuation_lines;
 			if (recognized_prefix &&
 			    trailer_lines * 3 >= non_trailer_lines)
-				return start + 1;
-			if (trailer_lines && !non_trailer_lines)
-				return start + 1;
-			return count;
+				return next_line(bol) - buf;
+			else if (trailer_lines && !non_trailer_lines)
+				return next_line(bol) - buf;
+			return len;
 		}
 		only_spaces = 0;
 
 		for (p = git_generated_prefixes; *p; p++) {
-			if (starts_with(lines[start]->buf, *p)) {
+			if (starts_with(bol, *p)) {
 				trailer_lines++;
 				possible_continuation_lines = 0;
 				recognized_prefix = 1;
 				goto continue_outer_loop;
 			}
 		}
 
-		separator_pos = find_separator(lines[start]->buf, separators);
-		if (separator_pos >= 1 && !isspace(lines[start]->buf[0])) {
+		separator_pos = find_separator(bol, separators);
+		if (separator_pos >= 1 && !isspace(bol[0])) {
 			struct list_head *pos;
 
 			trailer_lines++;
 			possible_continuation_lines = 0;
 			if (recognized_prefix)
 				continue;
 			list_for_each(pos, &conf_head) {
 				struct arg_item *item;
 				item = list_entry(pos, struct arg_item, list);
-				if (token_matches_item(lines[start]->buf, item,
+				if (token_matches_item(bol, item,
 						       separator_pos)) {
 					recognized_prefix = 1;
 					break;
 				}
 			}
-		} else if (isspace(lines[start]->buf[0]))
+		} else if (isspace(bol[0]))
 			possible_continuation_lines++;
 		else {
 			non_trailer_lines++;
 			non_trailer_lines += possible_continuation_lines;
 			possible_continuation_lines = 0;
 		}
 continue_outer_loop:
 		;
 	}
 
-	return count;
-}
-
-/* Get the index of the end of the trailers */
-static int find_trailer_end(struct strbuf **lines, int patch_start)
-{
-	struct strbuf sb = STRBUF_INIT;
-	int i, ignore_bytes;
-
-	for (i = 0; i < patch_start; i++)
-		strbuf_addbuf(&sb, lines[i]);
-	ignore_bytes = ignore_non_trailer(&sb);
-	strbuf_release(&sb);
-	for (i = patch_start - 1; i >= 0 && ignore_bytes > 0; i--)
-		ignore_bytes -= lines[i]->len;
-
-	return i + 1;
+	return len;
 }
 
-static int has_blank_line_before(struct strbuf **lines, int start)
+/* Return the position of the end of the trailers. */
+static int find_trailer_end(const char *buf, size_t len)
 {
-	for (;start >= 0; start--) {
-		if (lines[start]->buf[0] == comment_line_char)
-			continue;
-		return contains_only_spaces(lines[start]->buf);
-	}
-	return 0;
+	return len - ignore_non_trailer(buf, len);
 }
 
-static void print_lines(FILE *outfile, struct strbuf **lines, int start, int end)
+static int ends_with_blank_line(const char *buf, size_t len)
 {
-	int i;
-	for (i = start; lines[i] && i < end; i++)
-		fprintf(outfile, "%s", lines[i]->buf);
+	int ll = last_line(buf, len);
+	if (ll < 0)
+		return 0;
+	return is_blank_line(buf + ll);
 }
 
 static int process_input_file(FILE *outfile,
-			      struct strbuf **lines,
+			      const char *str,
 			      struct list_head *head)
 {
-	int count = 0;
-	int patch_start, trailer_start, trailer_end, i;
+	struct trailer_info info;
 	struct strbuf tok = STRBUF_INIT;
 	struct strbuf val = STRBUF_INIT;
-	struct trailer_item *last = NULL;
+	int i;
 
-	/* Get the line count */
-	while (lines[count])
-		count++;
-
-	patch_start = find_patch_start(lines, count);
-	trailer_end = find_trailer_end(lines, patch_start);
-	trailer_start = find_trailer_start(lines, trailer_end);
+	trailer_info_get(&info, str);
 
 	/* Print lines before the trailers as is */
-	print_lines(outfile, lines, 0, trailer_start);
+	fwrite(str, 1, info.trailer_start - str, outfile);
 
-	if (!has_blank_line_before(lines, trailer_start - 1))
+	if (!info.blank_line_before_trailer)
 		fprintf(outfile, "\n");
 
-	/* Parse trailer lines */
-	for (i = trailer_start; i < trailer_end; i++) {
+	for (i = 0; i < info.trailer_nr; i++) {
 		int separator_pos;
-		if (lines[i]->buf[0] == comment_line_char)
+		char *trailer = info.trailers[i];
+		if (trailer[0] == comment_line_char)
 			continue;
-		if (last && isspace(lines[i]->buf[0])) {
-			struct strbuf sb = STRBUF_INIT;
-			strbuf_addf(&sb, "%s\n%s", last->value, lines[i]->buf);
-			strbuf_strip_suffix(&sb, "\n");
-			free(last->value);
-			last->value = strbuf_detach(&sb, NULL);
-			continue;
-		}
-		separator_pos = find_separator(lines[i]->buf, separators);
+		separator_pos = find_separator(trailer, separators);
 		if (separator_pos >= 1) {
-			parse_trailer(&tok, &val, NULL, lines[i]->buf,
+			parse_trailer(&tok, &val, NULL, trailer,
 				      separator_pos);
-			last = add_trailer_item(head,
-						strbuf_detach(&tok, NULL),
-						strbuf_detach(&val, NULL));
+			add_trailer_item(head,
+					 strbuf_detach(&tok, NULL),
+					 strbuf_detach(&val, NULL));
 		} else {
-			strbuf_addbuf(&val, lines[i]);
+			strbuf_addstr(&val, trailer);
 			strbuf_strip_suffix(&val, "\n");
 			add_trailer_item(head,
 					 NULL,
 					 strbuf_detach(&val, NULL));
-			last = NULL;
 		}
 	}
 
-	return trailer_end;
+	trailer_info_release(&info);
+
+	return info.trailer_end - str;
 }
 
 static void free_all(struct list_head *head)
 {
 	struct list_head *pos, *p;
 	list_for_each_safe(pos, p, head) {
