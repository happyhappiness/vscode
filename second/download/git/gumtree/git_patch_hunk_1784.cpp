 {
 	for ( ; list; list = list->next) {
 		const char *format = list->next ? format_cur : format_last;
 		printf(format, sha1_to_hex(list->item->object.sha1));
 	}
 }
+
+const char *find_commit_header(const char *msg, const char *key, size_t *out_len)
+{
+	int key_len = strlen(key);
+	const char *line = msg;
+
+	while (line) {
+		const char *eol = strchrnul(line, '\n');
+
+		if (line == eol)
+			return NULL;
+
+		if (eol - line > key_len &&
+		    !strncmp(line, key, key_len) &&
+		    line[key_len] == ' ') {
+			*out_len = eol - line - key_len - 1;
+			return line + key_len + 1;
+		}
+		line = *eol ? eol + 1 : NULL;
+	}
+	return NULL;
+}
