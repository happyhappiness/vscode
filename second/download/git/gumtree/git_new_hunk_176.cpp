
static int parse_from(struct branch *b)
{
	const char *from;
	struct branch *s;

	if (!skip_prefix(command_buf.buf, "from ", &from))
		return 0;

	if (b->branch_tree.tree) {
		release_tree_content_recursive(b->branch_tree.tree);
		b->branch_tree.tree = NULL;
	}

	s = lookup_branch(from);
	if (b == s)
		die("Can't create a branch from itself: %s", b->name);
	else if (s) {
		unsigned char *t = s->branch_tree.versions[1].sha1;
		hashcpy(b->sha1, s->sha1);
