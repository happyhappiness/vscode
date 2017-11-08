static void insert_one_record(struct shortlog *log,
			      const char *author,
			      const char *oneline)
{
	struct string_list_item *item;
	const char *mailbuf, *namebuf;
	size_t namelen, maillen;
	struct strbuf namemailbuf = STRBUF_INIT;
	struct ident_split ident;

	if (split_ident_line(&ident, author, strlen(author)))
		return;

	namebuf = ident.name_begin;
	mailbuf = ident.mail_begin;
	namelen = ident.name_end - ident.name_begin;
	maillen = ident.mail_end - ident.mail_begin;

	map_user(&log->mailmap, &mailbuf, &maillen, &namebuf, &namelen);
	strbuf_add(&namemailbuf, namebuf, namelen);

	if (log->email)
		strbuf_addf(&namemailbuf, " <%.*s>", (int)maillen, mailbuf);

	item = string_list_insert(&log->list, namemailbuf.buf);

	if (log->summary)
		item->util = (void *)(UTIL_TO_INT(item) + 1);
	else {
		const char *dot3 = log->common_repo_prefix;
		char *buffer, *p;
		struct strbuf subject = STRBUF_INIT;
		const char *eol;

		/* Skip any leading whitespace, including any blank lines. */
		while (*oneline && isspace(*oneline))
			oneline++;
		eol = strchr(oneline, '\n');
		if (!eol)
			eol = oneline + strlen(oneline);
		if (starts_with(oneline, "[PATCH")) {
			char *eob = strchr(oneline, ']');
			if (eob && (!eol || eob < eol))
				oneline = eob + 1;
		}
		while (*oneline && isspace(*oneline) && *oneline != '\n')
			oneline++;
		format_subject(&subject, oneline, " ");
		buffer = strbuf_detach(&subject, NULL);

		if (dot3) {
			int dot3len = strlen(dot3);
			if (dot3len > 5) {
				while ((p = strstr(buffer, dot3)) != NULL) {
					int taillen = strlen(p) - dot3len;
					memcpy(p, "/.../", 5);
					memmove(p + 5, p + dot3len, taillen + 1);
				}
			}
		}

		if (item->util == NULL)
			item->util = xcalloc(1, sizeof(struct string_list));
		string_list_append(item->util, buffer);
	}
}