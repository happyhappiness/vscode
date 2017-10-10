 	if (!person->date_begin || !person->date_end ||
 	    !person->tz_begin || !person->tz_end)
 		return 0;
 	return 1;
 }
 
-static int parse_force_date(const char *in, char *out, int len)
+static int parse_force_date(const char *in, struct strbuf *out)
 {
-	if (len < 1)
-		return -1;
-	*out++ = '@';
-	len--;
+	strbuf_addch(out, '@');
 
-	if (parse_date(in, out, len) < 0) {
+	if (parse_date(in, out) < 0) {
 		int errors = 0;
 		unsigned long t = approxidate_careful(in, &errors);
 		if (errors)
 			return -1;
-		snprintf(out, len, "%lu", t);
+		strbuf_addf(out, "%lu", t);
 	}
 
 	return 0;
 }
 
+static void set_ident_var(char **buf, char *val)
+{
+	free(*buf);
+	*buf = val;
+}
+
+static char *envdup(const char *var)
+{
+	const char *val = getenv(var);
+	return val ? xstrdup(val) : NULL;
+}
+
 static void determine_author_info(struct strbuf *author_ident)
 {
 	char *name, *email, *date;
 	struct ident_split author;
-	char date_buf[64];
 
-	name = getenv("GIT_AUTHOR_NAME");
-	email = getenv("GIT_AUTHOR_EMAIL");
-	date = getenv("GIT_AUTHOR_DATE");
+	name = envdup("GIT_AUTHOR_NAME");
+	email = envdup("GIT_AUTHOR_EMAIL");
+	date = envdup("GIT_AUTHOR_DATE");
 
 	if (author_message) {
-		const char *a, *lb, *rb, *eol;
+		struct ident_split ident;
 		size_t len;
+		const char *a;
 
-		a = strstr(author_message_buffer, "\nauthor ");
+		a = find_commit_header(author_message_buffer, "author", &len);
 		if (!a)
-			die(_("invalid commit: %s"), author_message);
-
-		lb = strchrnul(a + strlen("\nauthor "), '<');
-		rb = strchrnul(lb, '>');
-		eol = strchrnul(rb, '\n');
-		if (!*lb || !*rb || !*eol)
-			die(_("invalid commit: %s"), author_message);
-
-		if (lb == a + strlen("\nauthor "))
-			/* \nauthor <foo@example.com> */
-			name = xcalloc(1, 1);
-		else
-			name = xmemdupz(a + strlen("\nauthor "),
-					(lb - strlen(" ") -
-					 (a + strlen("\nauthor "))));
-		email = xmemdupz(lb + strlen("<"), rb - (lb + strlen("<")));
-		len = eol - (rb + strlen("> "));
-		date = xmalloc(len + 2);
-		*date = '@';
-		memcpy(date + 1, rb + strlen("> "), len);
-		date[len + 1] = '\0';
+			die(_("commit '%s' lacks author header"), author_message);
+		if (split_ident_line(&ident, a, len) < 0)
+			die(_("commit '%s' has malformed author line"), author_message);
+
+		set_ident_var(&name, xmemdupz(ident.name_begin, ident.name_end - ident.name_begin));
+		set_ident_var(&email, xmemdupz(ident.mail_begin, ident.mail_end - ident.mail_begin));
+
+		if (ident.date_begin) {
+			struct strbuf date_buf = STRBUF_INIT;
+			strbuf_addch(&date_buf, '@');
+			strbuf_add(&date_buf, ident.date_begin, ident.date_end - ident.date_begin);
+			strbuf_addch(&date_buf, ' ');
+			strbuf_add(&date_buf, ident.tz_begin, ident.tz_end - ident.tz_begin);
+			set_ident_var(&date, strbuf_detach(&date_buf, NULL));
+		}
 	}
 
 	if (force_author) {
-		const char *lb = strstr(force_author, " <");
-		const char *rb = strchr(force_author, '>');
+		struct ident_split ident;
 
-		if (!lb || !rb)
+		if (split_ident_line(&ident, force_author, strlen(force_author)) < 0)
 			die(_("malformed --author parameter"));
-		name = xstrndup(force_author, lb - force_author);
-		email = xstrndup(lb + 2, rb - (lb + 2));
+		set_ident_var(&name, xmemdupz(ident.name_begin, ident.name_end - ident.name_begin));
+		set_ident_var(&email, xmemdupz(ident.mail_begin, ident.mail_end - ident.mail_begin));
 	}
 
 	if (force_date) {
-		if (parse_force_date(force_date, date_buf, sizeof(date_buf)))
+		struct strbuf date_buf = STRBUF_INIT;
+		if (parse_force_date(force_date, &date_buf))
 			die(_("invalid date format: %s"), force_date);
-		date = date_buf;
+		set_ident_var(&date, strbuf_detach(&date_buf, NULL));
 	}
 
 	strbuf_addstr(author_ident, fmt_ident(name, email, date, IDENT_STRICT));
 	if (!split_ident_line(&author, author_ident->buf, author_ident->len) &&
 	    sane_ident_split(&author)) {
 		export_one("GIT_AUTHOR_NAME", author.name_begin, author.name_end, 0);
 		export_one("GIT_AUTHOR_EMAIL", author.mail_begin, author.mail_end, 0);
 		export_one("GIT_AUTHOR_DATE", author.date_begin, author.tz_end, '@');
 	}
+
+	free(name);
+	free(email);
+	free(date);
 }
 
 static void split_ident_or_die(struct ident_split *id, const struct strbuf *buf)
 {
 	if (split_ident_line(id, buf->buf, buf->len) ||
 	    !sane_ident_split(id))
