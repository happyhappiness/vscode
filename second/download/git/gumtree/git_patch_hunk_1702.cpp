 	bol += strlen(needle);
 	eol = strchrnul(bol, '\n');
 	*eol = '\0';
 	return bol;
 }
 
+static void *anonymize_ref_component(const void *old, size_t *len)
+{
+	static int counter;
+	struct strbuf out = STRBUF_INIT;
+	strbuf_addf(&out, "ref%d", counter++);
+	return strbuf_detach(&out, len);
+}
+
+static const char *anonymize_refname(const char *refname)
+{
+	/*
+	 * If any of these prefixes is found, we will leave it intact
+	 * so that tags remain tags and so forth.
+	 */
+	static const char *prefixes[] = {
+		"refs/heads/",
+		"refs/tags/",
+		"refs/remotes/",
+		"refs/"
+	};
+	static struct hashmap refs;
+	static struct strbuf anon = STRBUF_INIT;
+	int i;
+
+	/*
+	 * We also leave "master" as a special case, since it does not reveal
+	 * anything interesting.
+	 */
+	if (!strcmp(refname, "refs/heads/master"))
+		return refname;
+
+	strbuf_reset(&anon);
+	for (i = 0; i < ARRAY_SIZE(prefixes); i++) {
+		if (skip_prefix(refname, prefixes[i], &refname)) {
+			strbuf_addstr(&anon, prefixes[i]);
+			break;
+		}
+	}
+
+	anonymize_path(&anon, refname, &refs, anonymize_ref_component);
+	return anon.buf;
+}
+
+/*
+ * We do not even bother to cache commit messages, as they are unlikely
+ * to be repeated verbatim, and it is not that interesting when they are.
+ */
+static char *anonymize_commit_message(const char *old)
+{
+	static int counter;
+	return xstrfmt("subject %d\n\nbody\n", counter++);
+}
+
+static struct hashmap idents;
+static void *anonymize_ident(const void *old, size_t *len)
+{
+	static int counter;
+	struct strbuf out = STRBUF_INIT;
+	strbuf_addf(&out, "User %d <user%d@example.com>", counter, counter);
+	counter++;
+	return strbuf_detach(&out, len);
+}
+
+/*
+ * Our strategy here is to anonymize the names and email addresses,
+ * but keep timestamps intact, as they influence things like traversal
+ * order (and by themselves should not be too revealing).
+ */
+static void anonymize_ident_line(const char **beg, const char **end)
+{
+	static struct strbuf buffers[] = { STRBUF_INIT, STRBUF_INIT };
+	static unsigned which_buffer;
+
+	struct strbuf *out;
+	struct ident_split split;
+	const char *end_of_header;
+
+	out = &buffers[which_buffer++];
+	which_buffer %= ARRAY_SIZE(buffers);
+	strbuf_reset(out);
+
+	/* skip "committer", "author", "tagger", etc */
+	end_of_header = strchr(*beg, ' ');
+	if (!end_of_header)
+		die("BUG: malformed line fed to anonymize_ident_line: %.*s",
+		    (int)(*end - *beg), *beg);
+	end_of_header++;
+	strbuf_add(out, *beg, end_of_header - *beg);
+
+	if (!split_ident_line(&split, end_of_header, *end - end_of_header) &&
+	    split.date_begin) {
+		const char *ident;
+		size_t len;
+
+		len = split.mail_end - split.name_begin;
+		ident = anonymize_mem(&idents, anonymize_ident,
+				      split.name_begin, &len);
+		strbuf_add(out, ident, len);
+		strbuf_addch(out, ' ');
+		strbuf_add(out, split.date_begin, split.tz_end - split.date_begin);
+	} else {
+		strbuf_addstr(out, "Malformed Ident <malformed@example.com> 0 -0000");
+	}
+
+	*beg = out->buf;
+	*end = out->buf + out->len;
+}
+
 static void handle_commit(struct commit *commit, struct rev_info *rev)
 {
 	int saved_output_format = rev->diffopt.output_format;
 	const char *commit_buffer;
 	const char *author, *author_end, *committer, *committer_end;
 	const char *encoding, *message;
 	char *reencoded = NULL;
 	struct commit_list *p;
+	const char *refname;
 	int i;
 
 	rev->diffopt.output_format = DIFF_FORMAT_CALLBACK;
 
 	parse_commit_or_die(commit);
 	commit_buffer = get_commit_buffer(commit, NULL);
