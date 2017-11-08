static int get_parent(const char *name, int len,
		      unsigned char *result, int idx)
{
	unsigned char sha1[20];
	int ret = get_sha1_1(name, len, sha1, GET_SHA1_COMMITTISH);
	struct commit *commit;
	struct commit_list *p;

	if (ret)
		return ret;
	commit = lookup_commit_reference(sha1);
	if (parse_commit(commit))
		return -1;
	if (!idx) {
		hashcpy(result, commit->object.sha1);
		return 0;
	}
	p = commit->parents;
	while (p) {
		if (!--idx) {
			hashcpy(result, p->item->object.sha1);
			return 0;
		}
		p = p->next;
	}
	return -1;
}