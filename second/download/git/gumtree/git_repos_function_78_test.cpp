int ignore_non_trailer(struct strbuf *sb)
{
	int boc = 0;
	int bol = 0;
	int in_old_conflicts_block = 0;

	while (bol < sb->len) {
		char *next_line;

		if (!(next_line = memchr(sb->buf + bol, '\n', sb->len - bol)))
			next_line = sb->buf + sb->len;
		else
			next_line++;

		if (sb->buf[bol] == comment_line_char || sb->buf[bol] == '\n') {
			/* is this the first of the run of comments? */
			if (!boc)
				boc = bol;
			/* otherwise, it is just continuing */
		} else if (starts_with(sb->buf + bol, "Conflicts:\n")) {
			in_old_conflicts_block = 1;
			if (!boc)
				boc = bol;
		} else if (in_old_conflicts_block && sb->buf[bol] == '\t') {
			; /* a pathname in the conflicts block */
		} else if (boc) {
			/* the previous was not trailing comment */
			boc = 0;
			in_old_conflicts_block = 0;
		}
		bol = next_line - sb->buf;
	}
	return boc ? sb->len - boc : 0;
}