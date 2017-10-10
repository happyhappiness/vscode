 	out->subject = q;
 	q = mempcpy(q, subject, subject_len);
 	*q = '\0';
 	return 0;
 }
 
-static void free_message(struct commit_message *msg)
+static void free_message(struct commit *commit, struct commit_message *msg)
 {
 	free(msg->parent_label);
-	free(msg->reencoded_message);
-}
-
-static char *get_encoding(const char *message)
-{
-	const char *p = message, *eol;
-
-	while (*p && *p != '\n') {
-		for (eol = p + 1; *eol && *eol != '\n'; eol++)
-			; /* do nothing */
-		if (starts_with(p, "encoding ")) {
-			char *result = xmalloc(eol - 8 - p);
-			strlcpy(result, p + 9, eol - 8 - p);
-			return result;
-		}
-		p = eol;
-		if (*p == '\n')
-			p++;
-	}
-	return NULL;
+	unuse_commit_buffer(commit, msg->message);
 }
 
 static void write_cherry_pick_head(struct commit *commit, const char *pseudoref)
 {
 	const char *filename;
 	int fd;
