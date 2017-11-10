void pp_title_line(struct pretty_print_context *pp,
		   const char **msg_p,
		   struct strbuf *sb,
		   const char *encoding,
		   int need_8bit_cte)
{
	static const int max_length = 78; /* per rfc2047 */
	struct strbuf title;

	strbuf_init(&title, 80);
	*msg_p = format_subject(&title, *msg_p,
				pp->preserve_subject ? "\n" : " ");

	strbuf_grow(sb, title.len + 1024);
	if (pp->print_email_subject) {
		if (pp->rev)
			fmt_output_email_subject(sb, pp->rev);
		if (needs_rfc2047_encoding(title.buf, title.len, RFC2047_SUBJECT))
			add_rfc2047(sb, title.buf, title.len,
						encoding, RFC2047_SUBJECT);
		else
			strbuf_add_wrapped_bytes(sb, title.buf, title.len,
					 -last_line_length(sb), 1, max_length);
	} else {
		strbuf_addbuf(sb, &title);
	}
	strbuf_addch(sb, '\n');

	if (need_8bit_cte == 0) {
		int i;
		for (i = 0; i < pp->in_body_headers.nr; i++) {
			if (has_non_ascii(pp->in_body_headers.items[i].string)) {
				need_8bit_cte = 1;
				break;
			}
		}
	}

	if (need_8bit_cte > 0) {
		const char *header_fmt =
			"MIME-Version: 1.0\n"
			"Content-Type: text/plain; charset=%s\n"
			"Content-Transfer-Encoding: 8bit\n";
		strbuf_addf(sb, header_fmt, encoding);
	}
	if (pp->after_subject) {
		strbuf_addstr(sb, pp->after_subject);
	}
	if (cmit_fmt_is_mail(pp->fmt)) {
		strbuf_addch(sb, '\n');
	}

	if (pp->in_body_headers.nr) {
		int i;
		for (i = 0; i < pp->in_body_headers.nr; i++) {
			strbuf_addstr(sb, pp->in_body_headers.items[i].string);
			free(pp->in_body_headers.items[i].string);
		}
		string_list_clear(&pp->in_body_headers, 0);
		strbuf_addch(sb, '\n');
	}

	strbuf_release(&title);
}