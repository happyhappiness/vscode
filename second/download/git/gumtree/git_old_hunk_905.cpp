}

int fmt_merge_msg(struct strbuf *in, struct strbuf *out,
		  struct fmt_merge_msg_opts *opts)
{
	int i = 0, pos = 0;
	unsigned char head_sha1[20];
	const char *current_branch;
	void *current_branch_to_free;
	struct merge_parents merge_parents;

	memset(&merge_parents, 0, sizeof(merge_parents));

	/* get current branch */
	current_branch = current_branch_to_free =
		resolve_refdup("HEAD", RESOLVE_REF_READING, head_sha1, NULL);
	if (!current_branch)
		die("No current branch");
	if (starts_with(current_branch, "refs/heads/"))
		current_branch += 11;

	find_merge_parents(&merge_parents, in, head_sha1);

	/* get a line */
	while (pos < in->len) {
		int len;
		char *newline, *p = in->buf + pos;

