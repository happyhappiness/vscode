static int try_difference(const char *arg)
{
	char *dotdot;
	struct object_id oid;
	struct object_id end;
	const char *next;
	const char *this;
	int symmetric;
	static const char head_by_default[] = "HEAD";

	if (!(dotdot = strstr(arg, "..")))
		return 0;
	next = dotdot + 2;
	this = arg;
	symmetric = (*next == '.');

	*dotdot = 0;
	next += symmetric;

	if (!*next)
		next = head_by_default;
	if (dotdot == arg)
		this = head_by_default;

	if (this == head_by_default && next == head_by_default &&
	    !symmetric) {
		/*
		 * Just ".."?  That is not a range but the
		 * pathspec for the parent directory.
		 */
		*dotdot = '.';
		return 0;
	}

	if (!get_sha1_committish(this, oid.hash) && !get_sha1_committish(next, end.hash)) {
		show_rev(NORMAL, &end, next);
		show_rev(symmetric ? NORMAL : REVERSED, &oid, this);
		if (symmetric) {
			struct commit_list *exclude;
			struct commit *a, *b;
			a = lookup_commit_reference(&oid);
			b = lookup_commit_reference(&end);
			exclude = get_merge_bases(a, b);
			while (exclude) {
				struct commit *commit = pop_commit(&exclude);
				show_rev(REVERSED, &commit->object.oid, NULL);
			}
		}
		*dotdot = '.';
		return 1;
	}
	*dotdot = '.';
	return 0;
}