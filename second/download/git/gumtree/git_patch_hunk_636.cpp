 	read_info_alternates(pathbuf.buf, depth + 1);
 
 	strbuf_release(&pathbuf);
 	return 0;
 }
 
+static const char *parse_alt_odb_entry(const char *string,
+				       int sep,
+				       struct strbuf *out)
+{
+	const char *end;
+
+	strbuf_reset(out);
+
+	if (*string == '#') {
+		/* comment; consume up to next separator */
+		end = strchrnul(string, sep);
+	} else if (*string == '"' && !unquote_c_style(out, string, &end)) {
+		/*
+		 * quoted path; unquote_c_style has copied the
+		 * data for us and set "end". Broken quoting (e.g.,
+		 * an entry that doesn't end with a quote) falls
+		 * back to the unquoted case below.
+		 */
+	} else {
+		/* normal, unquoted path */
+		end = strchrnul(string, sep);
+		strbuf_add(out, string, end - string);
+	}
+
+	if (*end)
+		end++;
+	return end;
+}
+
 static void link_alt_odb_entries(const char *alt, int len, int sep,
 				 const char *relative_base, int depth)
 {
-	struct string_list entries = STRING_LIST_INIT_NODUP;
-	char *alt_copy;
-	int i;
 	struct strbuf objdirbuf = STRBUF_INIT;
+	struct strbuf entry = STRBUF_INIT;
 
 	if (depth > 5) {
 		error("%s: ignoring alternate object stores, nesting too deep.",
 				relative_base);
 		return;
 	}
 
 	strbuf_add_absolute_path(&objdirbuf, get_object_directory());
 	if (strbuf_normalize_path(&objdirbuf) < 0)
 		die("unable to normalize object directory: %s",
 		    objdirbuf.buf);
 
-	alt_copy = xmemdupz(alt, len);
-	string_list_split_in_place(&entries, alt_copy, sep, -1);
-	for (i = 0; i < entries.nr; i++) {
-		const char *entry = entries.items[i].string;
-		if (entry[0] == '\0' || entry[0] == '#')
+	while (*alt) {
+		alt = parse_alt_odb_entry(alt, sep, &entry);
+		if (!entry.len)
 			continue;
-		link_alt_odb_entry(entry, relative_base, depth, objdirbuf.buf);
+		link_alt_odb_entry(entry.buf, relative_base, depth, objdirbuf.buf);
 	}
-	string_list_clear(&entries, 0);
-	free(alt_copy);
+	strbuf_release(&entry);
 	strbuf_release(&objdirbuf);
 }
 
 void read_info_alternates(const char * relative_base, int depth)
 {
 	char *map;
