static const char *short_commit_name(struct commit *commit)
{
	return find_unique_abbrev(commit->object.oid.hash, DEFAULT_ABBREV);
}