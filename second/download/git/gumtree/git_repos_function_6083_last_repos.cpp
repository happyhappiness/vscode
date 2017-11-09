static void print_new_head_line(struct commit *commit)
{
	const char *hex, *body;
	const char *msg;

	hex = find_unique_abbrev(commit->object.oid.hash, DEFAULT_ABBREV);
	printf(_("HEAD is now at %s"), hex);
	msg = logmsg_reencode(commit, NULL, get_log_output_encoding());
	body = strstr(msg, "\n\n");
	if (body) {
		const char *eol;
		size_t len;
		body = skip_blank_lines(body + 2);
		eol = strchr(body, '\n');
		len = eol ? eol - body : strlen(body);
		printf(" %.*s\n", (int) len, body);
	}
	else
		printf("\n");
	unuse_commit_buffer(commit, msg);
}