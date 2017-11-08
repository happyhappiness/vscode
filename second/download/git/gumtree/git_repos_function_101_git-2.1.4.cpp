static void parse_commit_header(struct format_commit_context *context)
{
	const char *msg = context->message;
	int i;

	for (i = 0; msg[i]; i++) {
		int eol;
		for (eol = i; msg[eol] && msg[eol] != '\n'; eol++)
			; /* do nothing */

		if (i == eol) {
			break;
		} else if (starts_with(msg + i, "author ")) {
			context->author.off = i + 7;
			context->author.len = eol - i - 7;
		} else if (starts_with(msg + i, "committer ")) {
			context->committer.off = i + 10;
			context->committer.len = eol - i - 10;
		}
		i = eol;
	}
	context->message_off = i;
	context->commit_header_parsed = 1;
}