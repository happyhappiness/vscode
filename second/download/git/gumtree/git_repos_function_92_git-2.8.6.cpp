void pp_user_info(struct pretty_print_context *pp,
		  const char *what, struct strbuf *sb,
		  const char *line, const char *encoding)
{
	struct ident_split ident;
	char *line_end;
	const char *mailbuf, *namebuf;
	size_t namelen, maillen;
	int max_length = 78; /* per rfc2822 */

	if (pp->fmt == CMIT_FMT_ONELINE)
		return;

	line_end = strchrnul(line, '\n');
	if (split_ident_line(&ident, line, line_end - line))
		return;

	mailbuf = ident.mail_begin;
	maillen = ident.mail_end - ident.mail_begin;
	namebuf = ident.name_begin;
	namelen = ident.name_end - ident.name_begin;

	if (pp->mailmap)
		map_user(pp->mailmap, &mailbuf, &maillen, &namebuf, &namelen);

	if (pp->fmt == CMIT_FMT_EMAIL) {
		if (pp->from_ident && ident_cmp(pp->from_ident, &ident)) {
			struct strbuf buf = STRBUF_INIT;

			strbuf_addstr(&buf, "From: ");
			strbuf_add(&buf, namebuf, namelen);
			strbuf_addstr(&buf, " <");
			strbuf_add(&buf, mailbuf, maillen);
			strbuf_addstr(&buf, ">\n");
			string_list_append(&pp->in_body_headers,
					   strbuf_detach(&buf, NULL));

			mailbuf = pp->from_ident->mail_begin;
			maillen = pp->from_ident->mail_end - mailbuf;
			namebuf = pp->from_ident->name_begin;
			namelen = pp->from_ident->name_end - namebuf;
		}

		strbuf_addstr(sb, "From: ");
		if (needs_rfc2047_encoding(namebuf, namelen, RFC2047_ADDRESS)) {
			add_rfc2047(sb, namebuf, namelen,
				    encoding, RFC2047_ADDRESS);
			max_length = 76; /* per rfc2047 */
		} else if (needs_rfc822_quoting(namebuf, namelen)) {
			struct strbuf quoted = STRBUF_INIT;
			add_rfc822_quoted(&quoted, namebuf, namelen);
			strbuf_add_wrapped_bytes(sb, quoted.buf, quoted.len,
							-6, 1, max_length);
			strbuf_release(&quoted);
		} else {
			strbuf_add_wrapped_bytes(sb, namebuf, namelen,
						 -6, 1, max_length);
		}

		if (max_length <
		    last_line_length(sb) + strlen(" <") + maillen + strlen(">"))
			strbuf_addch(sb, '\n');
		strbuf_addf(sb, " <%.*s>\n", (int)maillen, mailbuf);
	} else {
		strbuf_addf(sb, "%s: %.*s%.*s <%.*s>\n", what,
			    (pp->fmt == CMIT_FMT_FULLER) ? 4 : 0, "    ",
			    (int)namelen, namebuf, (int)maillen, mailbuf);
	}

	switch (pp->fmt) {
	case CMIT_FMT_MEDIUM:
		strbuf_addf(sb, "Date:   %s\n",
			    show_ident_date(&ident, &pp->date_mode));
		break;
	case CMIT_FMT_EMAIL:
		strbuf_addf(sb, "Date: %s\n",
			    show_ident_date(&ident, DATE_MODE(RFC2822)));
		break;
	case CMIT_FMT_FULLER:
		strbuf_addf(sb, "%sDate: %s\n", what,
			    show_ident_date(&ident, &pp->date_mode));
		break;
	default:
		/* notin' */
		break;
	}
}