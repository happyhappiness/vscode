int register_shallow(const unsigned char *sha1)
{
	struct commit_graft *graft =
		xmalloc(sizeof(struct commit_graft));
	struct commit *commit = lookup_commit(sha1);

	hashcpy(graft->sha1, sha1);
	graft->nr_parent = -1;
	if (commit && commit->object.parsed)
		commit->parents = NULL;
	return register_commit_graft(graft, 0);
}