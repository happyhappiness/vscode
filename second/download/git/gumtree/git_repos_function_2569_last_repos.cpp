static void handle_from(struct mailinfo *mi, const struct strbuf *from)
{
	char *at;
	size_t el;
	struct strbuf f;

	strbuf_init(&f, from->len);
	strbuf_addbuf(&f, from);

	unquote_quoted_pair(&f);

	at = strchr(f.buf, '@');
	if (!at) {
		parse_bogus_from(mi, from);
		return;
	}

	/*
	 * If we already have one email, don't take any confusing lines
	 */
	if (mi->email.len && strchr(at + 1, '@')) {
		strbuf_release(&f);
		return;
	}

	/* Pick up the string around '@', possibly delimited with <>
	 * pair; that is the email part.
	 */
	while (at > f.buf) {
		char c = at[-1];
		if (isspace(c))
			break;
		if (c == '<') {
			at[-1] = ' ';
			break;
		}
		at--;
	}
	el = strcspn(at, " \n\t\r\v\f>");
	strbuf_reset(&mi->email);
	strbuf_add(&mi->email, at, el);
	strbuf_remove(&f, at - f.buf, el + (at[el] ? 1 : 0));

	/* The remainder is name.  It could be
	 *
	 * - "John Doe <john.doe@xz>"			(a), or
	 * - "john.doe@xz (John Doe)"			(b), or
	 * - "John (zzz) Doe <john.doe@xz> (Comment)"	(c)
	 *
	 * but we have removed the email part, so
	 *
	 * - remove extra spaces which could stay after email (case 'c'), and
	 * - trim from both ends, possibly removing the () pair at the end
	 *   (cases 'a' and 'b').
	 */
	cleanup_space(&f);
	strbuf_trim(&f);
	if (f.buf[0] == '(' && f.len && f.buf[f.len - 1] == ')') {
		strbuf_remove(&f, 0, 1);
		strbuf_setlen(&f, f.len - 1);
	}

	get_sane_name(&mi->name, &f, &mi->email);
	strbuf_release(&f);
}