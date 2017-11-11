static size_t format_and_pad_commit(struct strbuf *sb, /* in UTF-8 */
				    const char *placeholder,
				    struct format_commit_context *c)
{
	struct strbuf local_sb = STRBUF_INIT;
	int total_consumed = 0, len, padding = c->padding;
	if (padding < 0) {
		const char *start = strrchr(sb->buf, '\n');
		int occupied;
		if (!start)
			start = sb->buf;
		occupied = utf8_strnwidth(start, -1, 1);
		occupied += c->pretty_ctx->graph_width;
		padding = (-padding) - occupied;
	}
	while (1) {
		int modifier = *placeholder == 'C';
		int consumed = format_commit_one(&local_sb, placeholder, c);
		total_consumed += consumed;

		if (!modifier)
			break;

		placeholder += consumed;
		if (*placeholder != '%')
			break;
		placeholder++;
		total_consumed++;
	}
	len = utf8_strnwidth(local_sb.buf, -1, 1);

	if (c->flush_type == flush_left_and_steal) {
		const char *ch = sb->buf + sb->len - 1;
		while (len > padding && ch > sb->buf) {
			const char *p;
			if (*ch == ' ') {
				ch--;
				padding++;
				continue;
			}
			/* check for trailing ansi sequences */
			if (*ch != 'm')
				break;
			p = ch - 1;
			while (ch - p < 10 && *p != '\033')
				p--;
			if (*p != '\033' ||
			    ch + 1 - p != display_mode_esc_sequence_len(p))
				break;
			/*
			 * got a good ansi sequence, put it back to
			 * local_sb as we're cutting sb
			 */
			strbuf_insert(&local_sb, 0, p, ch + 1 - p);
			ch = p - 1;
		}
		strbuf_setlen(sb, ch + 1 - sb->buf);
		c->flush_type = flush_left;
	}

	if (len > padding) {
		switch (c->truncate) {
		case trunc_left:
			strbuf_utf8_replace(&local_sb,
					    0, len - (padding - 2),
					    "..");
			break;
		case trunc_middle:
			strbuf_utf8_replace(&local_sb,
					    padding / 2 - 1,
					    len - (padding - 2),
					    "..");
			break;
		case trunc_right:
			strbuf_utf8_replace(&local_sb,
					    padding - 2, len - (padding - 2),
					    "..");
			break;
		case trunc_none:
			break;
		}
		strbuf_addbuf(sb, &local_sb);
	} else {
		int sb_len = sb->len, offset = 0;
		if (c->flush_type == flush_left)
			offset = padding - len;
		else if (c->flush_type == flush_both)
			offset = (padding - len) / 2;
		/*
		 * we calculate padding in columns, now
		 * convert it back to chars
		 */
		padding = padding - len + local_sb.len;
		strbuf_addchars(sb, ' ', padding);
		memcpy(sb->buf + sb_len + offset, local_sb.buf,
		       local_sb.len);
	}
	strbuf_release(&local_sb);
	c->flush_type = no_flush;
	return total_consumed;
}