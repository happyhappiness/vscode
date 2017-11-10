void pretty_print_commit(struct pretty_print_context *pp,
			 const struct commit *commit,
			 struct strbuf *sb)
{
	unsigned long beginning_of_body;
	int indent = 4;
	const char *msg;
	const char *reencoded;
	const char *encoding;
	int need_8bit_cte = pp->need_8bit_cte;

	if (pp->fmt == CMIT_FMT_USERFORMAT) {
		format_commit_message(commit, user_format, sb, pp);
		return;
	}

	encoding = get_log_output_encoding();
	msg = reencoded = logmsg_reencode(commit, NULL, encoding);

	if (pp->fmt == CMIT_FMT_ONELINE || cmit_fmt_is_mail(pp->fmt))
		indent = 0;

	/*
	 * We need to check and emit Content-type: to mark it
	 * as 8-bit if we haven't done so.
	 */
	if (cmit_fmt_is_mail(pp->fmt) && need_8bit_cte == 0) {
		int i, ch, in_body;

		for (in_body = i = 0; (ch = msg[i]); i++) {
			if (!in_body) {
				/* author could be non 7-bit ASCII but
				 * the log may be so; skip over the
				 * header part first.
				 */
				if (ch == '\n' && msg[i+1] == '\n')
					in_body = 1;
			}
			else if (non_ascii(ch)) {
				need_8bit_cte = 1;
				break;
			}
		}
	}

	pp_header(pp, encoding, commit, &msg, sb);
	if (pp->fmt != CMIT_FMT_ONELINE && !pp->subject) {
		strbuf_addch(sb, '\n');
	}

	/* Skip excess blank lines at the beginning of body, if any... */
	msg = skip_blank_lines(msg);

	/* These formats treat the title line specially. */
	if (pp->fmt == CMIT_FMT_ONELINE || cmit_fmt_is_mail(pp->fmt))
		pp_title_line(pp, &msg, sb, encoding, need_8bit_cte);

	beginning_of_body = sb->len;
	if (pp->fmt != CMIT_FMT_ONELINE)
		pp_remainder(pp, &msg, sb, indent);
	strbuf_rtrim(sb);

	/* Make sure there is an EOLN for the non-oneline case */
	if (pp->fmt != CMIT_FMT_ONELINE)
		strbuf_addch(sb, '\n');

	/*
	 * The caller may append additional body text in e-mail
	 * format.  Make sure we did not strip the blank line
	 * between the header and the body.
	 */
	if (cmit_fmt_is_mail(pp->fmt) && sb->len <= beginning_of_body)
		strbuf_addch(sb, '\n');

	unuse_commit_buffer(commit, reencoded);
}