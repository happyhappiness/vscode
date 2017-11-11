static int try_difference(const char *arg)
{
	char *dotdot;
	unsigned char sha1[20];
	unsigned char end[20];
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

	if (!get_sha1_committish(this, sha1) && !get_sha1_committish(next, end)) {
		show_rev(NORMAL, end, next);
		show_rev(symmetric ? NORMAL : REVERSED, sha1, this);
		if (symmetric) {
			struct commit_list *exclude;
			struct commit *a, *b;
			a = lookup_commit_reference(sha1);
			b = lookup_commit_reference(end);
			exclude = get_merge_bases(a, b);
			while (exclude) {
				struct commit_list *n = exclude->next;
				show_rev(REVERSED,
					 exclude->item->object.sha1,NULL);
				free(exclude);
				exclude = n;
			}
		}
		*dotdot = '.';
		return 1;
	}
	*dotdot = '.';
	return 0;
}