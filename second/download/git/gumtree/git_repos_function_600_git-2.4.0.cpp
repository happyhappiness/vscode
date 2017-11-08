struct commit *lookup_commit_reference_by_name(const char *name)
{
	unsigned char sha1[20];
	struct commit *commit;

	if (get_sha1_committish(name, sha1))
		return NULL;
	commit = lookup_commit_reference(sha1);
	if (parse_commit(commit))
		return NULL;
	return commit;
}