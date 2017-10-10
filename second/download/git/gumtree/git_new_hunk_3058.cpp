		die("Not a valid commit name %s", sha1_to_hex(sha1));
	return r;
}

static struct commit **get_bad_and_good_commits(int *rev_nr)
{
	struct commit **rev;
	int i, n = 0;

	ALLOC_ARRAY(rev, 1 + good_revs.nr);
	rev[n++] = get_commit_reference(current_bad_oid->hash);
	for (i = 0; i < good_revs.nr; i++)
		rev[n++] = get_commit_reference(good_revs.sha1[i]);
	*rev_nr = n;

	return rev;
