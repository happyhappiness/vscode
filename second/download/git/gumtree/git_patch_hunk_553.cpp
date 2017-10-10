 
 	if (!has_blank_line_before(lines, trailer_start - 1))
 		fprintf(outfile, "\n");
 
 	/* Parse trailer lines */
 	for (i = trailer_start; i < trailer_end; i++) {
-		if (lines[i]->buf[0] != comment_line_char) {
-			struct trailer_item *new = create_trailer_item(lines[i]->buf);
-			add_trailer_item(in_tok_first, in_tok_last, new);
+		int separator_pos;
+		if (lines[i]->buf[0] == comment_line_char)
+			continue;
+		if (last && isspace(lines[i]->buf[0])) {
+			struct strbuf sb = STRBUF_INIT;
+			strbuf_addf(&sb, "%s\n%s", last->value, lines[i]->buf);
+			strbuf_strip_suffix(&sb, "\n");
+			free(last->value);
+			last->value = strbuf_detach(&sb, NULL);
+			continue;
+		}
+		separator_pos = find_separator(lines[i]->buf, separators);
+		if (separator_pos >= 1) {
+			parse_trailer(&tok, &val, NULL, lines[i]->buf,
+				      separator_pos);
+			last = add_trailer_item(head,
+						strbuf_detach(&tok, NULL),
+						strbuf_detach(&val, NULL));
+		} else {
+			strbuf_addbuf(&val, lines[i]);
+			strbuf_strip_suffix(&val, "\n");
+			add_trailer_item(head,
+					 NULL,
+					 strbuf_detach(&val, NULL));
+			last = NULL;
 		}
 	}
 
 	return trailer_end;
 }
 
-static void free_all(struct trailer_item **first)
+static void free_all(struct list_head *head)
 {
-	while (*first) {
-		struct trailer_item *item = remove_first(first);
-		free_trailer_item(item);
+	struct list_head *pos, *p;
+	list_for_each_safe(pos, p, head) {
+		list_del(pos);
+		free_trailer_item(list_entry(pos, struct trailer_item, list));
 	}
 }
 
 static struct tempfile trailers_tempfile;
 
 static FILE *create_in_place_tempfile(const char *file)
