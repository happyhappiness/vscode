static int get_parent(const char *name, int len,
		      unsigned char *result, int idx)
{
	struct object_id oid;
	int ret = get_sha1_1(name, len, oid.hash, GET_SHA1_COMMITTISH);
	struct commit *commit;
	struct commit_list *p;

	if (ret)
		return ret;
	commit = lookup_commit_reference(&oid);
	if (parse_commit(commit))
		return -1;
	if (!idx) {
		hashcpy(result, commit->object.oid.hash);
		return 0;
	}
	p = commit->parents;
	while (p) {
		if (!--idx) {
			hashcpy(result, p->item->object.oid.hash);
			return 0;
		}
		p = p->next;
	}
	return -1;
}