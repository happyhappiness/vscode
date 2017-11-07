static int get_nth_ancestor(const char *name, int len,
			    unsigned char *result, int generation)
{
	unsigned char sha1[20];
	struct commit *commit;
	int ret;

	ret = get_sha1_1(name, len, sha1, GET_SHA1_COMMITTISH);
	if (ret)
		return ret;
	commit = lookup_commit_reference(sha1);
	if (!commit)
		return -1;

	while (generation--) {
		if (parse_commit(commit) || !commit->parents)
			return -1;
		commit = commit->parents->item;
	}
	hashcpy(result, commit->object.sha1);
	return 0;
}