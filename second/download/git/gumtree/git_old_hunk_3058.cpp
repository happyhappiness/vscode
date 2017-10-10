		die("Not a valid commit name %s", sha1_to_hex(sha1));
	return r;
}

static struct commit **get_bad_and_good_commits(int *rev_nr)
{
	int len = 1 + good_revs.nr;
	struct commit **rev = xmalloc(len * sizeof(*rev));
	int i, n = 0;

	rev[n++] = get_commit_reference(current_bad_oid->hash);
	for (i = 0; i < good_revs.nr; i++)
		rev[n++] = get_commit_reference(good_revs.sha1[i]);
	*rev_nr = n;

	return rev;
