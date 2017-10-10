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

static void read_from_stdin(struct shortlog *log)
{
	struct strbuf author = STRBUF_INIT;
	struct strbuf oneline = STRBUF_INIT;

	while (strbuf_getline_lf(&author, stdin) != EOF) {
		const char *v;
		if (!skip_prefix(author.buf, "Author: ", &v) &&
		    !skip_prefix(author.buf, "author ", &v))
			continue;
		while (strbuf_getline_lf(&oneline, stdin) != EOF &&
		       oneline.len)
			; /* discard headers */
		while (strbuf_getline_lf(&oneline, stdin) != EOF &&
		       !oneline.len)
			; /* discard blanks */
		insert_one_record(log, v, oneline.buf);
	}
	strbuf_release(&author);
	strbuf_release(&oneline);
}

void shortlog_add_commit(struct shortlog *log, struct commit *commit)
{
	struct strbuf author = STRBUF_INIT;
	struct strbuf oneline = STRBUF_INIT;
	struct pretty_print_context ctx = {0};

	ctx.fmt = CMIT_FMT_USERFORMAT;
	ctx.abbrev = log->abbrev;
	ctx.subject = "";
	ctx.after_subject = "";
	ctx.date_mode.type = DATE_NORMAL;
	ctx.output_encoding = get_log_output_encoding();

	format_commit_message(commit, "%an <%ae>", &author, &ctx);
	if (!log->summary) {
		if (log->user_format)
			pretty_print_commit(&ctx, commit, &oneline);
		else
			format_commit_message(commit, "%s", &oneline, &ctx);
	}

	insert_one_record(log, author.buf, oneline.len ? oneline.buf : "<none>");

	strbuf_release(&author);
	strbuf_release(&oneline);
}

static void get_from_rev(struct rev_info *rev, struct shortlog *log)
{
	struct commit *commit;

