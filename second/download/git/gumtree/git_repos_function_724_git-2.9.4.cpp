struct commit *lookup_commit_reference_by_name(const char *name)
{
	struct object_id oid;
	struct commit *commit;

	if (get_sha1_committish(name, oid.hash))
		return NULL;
	commit = lookup_commit_reference(oid.hash);
	if (parse_commit(commit))
		return NULL;
	return commit;
}