	return 0;
}

static void print_new_head_line(struct commit *commit)
{
	const char *hex, *body;
	char *msg;

	hex = find_unique_abbrev(commit->object.sha1, DEFAULT_ABBREV);
	printf(_("HEAD is now at %s"), hex);
	msg = logmsg_reencode(commit, NULL, get_log_output_encoding());
	body = strstr(msg, "\n\n");
	if (body) {
