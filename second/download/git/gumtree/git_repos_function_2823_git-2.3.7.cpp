static size_t expand_path(struct strbuf *sb, const char *placeholder, void *ctx)
{
	struct expand_path_context *context = ctx;

	switch (placeholder[0]) {
	case 'H':
		strbuf_addstr_or_null(sb, hostname);
		return 1;
	case 'C':
		if (placeholder[1] == 'H') {
			strbuf_addstr_or_null(sb, get_canon_hostname());
			return 2;
		}
		break;
	case 'I':
		if (placeholder[1] == 'P') {
			strbuf_addstr_or_null(sb, get_ip_address());
			return 2;
		}
		break;
	case 'P':
		strbuf_addstr_or_null(sb, tcp_port);
		return 1;
	case 'D':
		strbuf_addstr(sb, context->directory);
		return 1;
	}
	return 0;
}