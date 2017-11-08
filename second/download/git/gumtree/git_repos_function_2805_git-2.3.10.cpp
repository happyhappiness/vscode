static struct commit **get_bad_and_good_commits(int *rev_nr)
{
	int len = 1 + good_revs.nr;
	struct commit **rev = xmalloc(len * sizeof(*rev));
	int i, n = 0;

	rev[n++] = get_commit_reference(current_bad_sha1);
	for (i = 0; i < good_revs.nr; i++)
		rev[n++] = get_commit_reference(good_revs.sha1[i]);
	*rev_nr = n;

	return rev;
}